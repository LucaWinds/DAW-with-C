#include "MIDI.h"

// 미디 출력 중에 발생하는 메시지를 받을 콜백 함수
void CALLBACK MidiOutProc(HMIDIOUT MidiOut, UINT Msg, DWORD Instance, DWORD Param1, DWORD Param2)
{
}

// 미디 에러 코드를 문자열로 바꿔서 출력해주는 함수
void Midi_OutputError(MMRESULT mmrErrCode)
{
    // 에러 문자열을 저장할 배열
    char m_szErrMsg[128];

    // 에러 코드를 문자열로 변환
    midiInGetErrorText(mmrErrCode, (char*)m_szErrMsg, sizeof(m_szErrMsg));

    // 변환된 문자열을 메시지 박스로 출력
    MessageBox(0, m_szErrMsg, "Midi Error!!!", MB_OK);
}

// 미디 장치 번호를 알아 내는 함수
// 미디장치의 속성을 알아낼때 이 함수가 필요
long Midi_GetDevID(HMIDIOUT m_DevOutHandle)
{
    // 장치 번호를 저장할 변수
    UINT     uDeviceID;

    // 미디 출력 핸들에 대응하는 장치 번호를 조사해서 uDeviceID변수에 저장
    MMRESULT Result = midiOutGetID(m_DevOutHandle, &uDeviceID);

    // 장치를 조사하던 중에 에러가 나서 실패하면...
    if (Result != MMSYSERR_NOERROR) {
        // 에러 출력 및 에러난 사실을 리턴값으로 알림
        Midi_OutputError(Result);
        return -1;
    }

    // 장치 번호를 리턴
    return (long)uDeviceID;
}


// 미디 핸들을 이용해 미디 장치 속성을
// MIDIOUTCAPS구조체 변수에 저장해주는 함수
void Midi_GetDevCaps(HMIDIOUT m_DevOutHandle, MIDIOUTCAPS* Caps)
{
    // 장치 번호를 저장할 변수
    long lDeviceID;

    // 에러 코드를 저장할 변수
    MMRESULT Result;

    // 미디 핸들을 이용해 장치 번호를 조사해서
    // lDeviceID변수에 저장
    lDeviceID = Midi_GetDevID(m_DevOutHandle);

    // lDeviceID가 음수면 에러가 난 경우이므로
    // 이 함수의 처리를 더이상 진행하지 않는다.
    if (lDeviceID < 0) return;

    // 미디 장치의 속성을 MIDIOUTCAPS구조체 변수에 저장한다.
    Result = midiOutGetDevCaps((UINT)lDeviceID, Caps, sizeof(MIDIOUTCAPS));

    // 에러가 났다면 에러문자열을 출력한다.
    if (Result != MMSYSERR_NOERROR) Midi_OutputError(Result);
}

// 장치번호에 해당하는 미디장치를 연다.
HMIDIOUT Midi_Open(WORD wDevsNum)
{
    WORD      wMaxDevNum = 0;
    MMRESULT  uiMidiOpen = 0;
    HMIDIOUT  m_DevHandle = NULL;

    // 사용가능한 장치의 총 갯수를 wMaxDevNum변수에 저장
    wMaxDevNum = midiInGetNumDevs();

    // 입력한 번호가 총 갯수보다 같거나 큰 값이면
    // 오픈할 장치번호를 0으로 조정한다.
    if (wDevsNum >= wMaxDevNum) wDevsNum = 0;

    // wDevsNum변수에 저장된 값에 해당하는 미디장치를
    // 열고 그 장치핸들값을 m_DevHandle에 저장
    // 연주중에 발생하는 메시지는 콜백함수 MidiOutProc로 보냄

    uiMidiOpen = midiOutOpen(&m_DevHandle, wDevsNum, (DWORD)(MidiOutProc), (DWORD)NULL, CALLBACK_FUNCTION);

    // 열기 도중 에러가 발생하면
    if (uiMidiOpen != MMSYSERR_NOERROR) {
        //에러문자열을 출력한다.
        Midi_OutputError(uiMidiOpen);

        // NULL값을 리턴
        return NULL;
    }

    // 장치 핸들을 리턴
    return m_DevHandle;
}



// 핸들값에 해당하는 미디장치를 닫습니다.
LRESULT Midi_Close(HMIDIOUT m_DevOutHandle)
{
    MMRESULT Result;
    // 미디 핸들값을 이용해 장치를 닫습니다.
    Result = midiOutClose(m_DevOutHandle);
    
    // 닫는 도중에 에러가 생기면
    if (Result != MMSYSERR_NOERROR){
        // 에러 출력
        Midi_OutputError(Result);
        // 닫기 실패를 리턴값으로 알림
        return FALSE;
    }

    // 닫기 성공을 리턴값으로 알림
    return TRUE;
}



// 짧은 미디 메시지를 미디 장치로 보내는 함수
void Midi_SendShortMsg(HMIDIOUT m_DevOutHandle, BYTE byteState, BYTE byteNote, BYTE byteValo)
{
    MJGRShortMidiMSG  sMsg;

    // MJGRShortMidiMSG구조체안에 있는
    // MJGRShortMidiMSG_ST구조체 변수의 각 멤버 변수에
    // 값을 채워넣는다.
    sMsg.stMidi_Data.byteVelocity = byteValo;
    sMsg.stMidi_Data.byteNote = byteNote;
    sMsg.stMidi_Data.byteState = byteState;
    sMsg.stMidi_Data.byteNULL = 0;

    // 출력 장치로 값을 채워넣은 구조체의 데이터를 보낸다.
    midiOutShortMsg(m_DevOutHandle, sMsg.dwMidi_Data);
}



// 긴 미디 메시지를 미디 장치로 보내는 함수
void Midi_SendLongMsg(HMIDIOUT m_DevOutHandle, BYTE* lpMsg, DWORD dwMsgLength)
{
    MIDIHDR  m_MIDIHdr;
    MMRESULT Result;

    ZeroMemory(&m_MIDIHdr, sizeof(MIDIHDR));

    m_MIDIHdr.lpData = (char*)lpMsg;
    m_MIDIHdr.dwBufferLength = dwMsgLength;
    m_MIDIHdr.dwFlags = 0;

    // 긴 미디데이터를 장치로 보내기 위한 준비작업을 함
    Result = midiOutPrepareHeader(m_DevOutHandle, &m_MIDIHdr, sizeof(MIDIHDR));

    if (Result != MMSYSERR_NOERROR){
        Midi_OutputError(Result);
        return;
    }

    // 긴 미디데이터를 장치로 보냄
    Result = midiOutLongMsg(m_DevOutHandle, &m_MIDIHdr, sizeof(MIDIHDR));

    if (Result != MMSYSERR_NOERROR){
        Midi_OutputError(Result);
        return;
    }



    // 긴 미디데이터를 장치로 보내기 위한 작업을 끝냄
    midiOutUnprepareHeader(m_DevOutHandle, &m_MIDIHdr, sizeof(MIDIHDR));
}

// 모든 채널의 연주중인 음을 종료하게 만드는 함수...
void Midi_AllChannelSoundOff(HMIDIOUT m_DevOutHandle)
{
    BYTE channel;

    for (channel = 0; channel < 16; channel++){
        Midi_SendShortMsg(m_DevOutHandle, (BYTE)(0xB0 + channel), 0x78, 0);
    }

}