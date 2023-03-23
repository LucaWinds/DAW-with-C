#include "MIDI.h"

// �̵� ��� �߿� �߻��ϴ� �޽����� ���� �ݹ� �Լ�
void CALLBACK MidiOutProc(HMIDIOUT MidiOut, UINT Msg, DWORD Instance, DWORD Param1, DWORD Param2)
{
}

// �̵� ���� �ڵ带 ���ڿ��� �ٲ㼭 ������ִ� �Լ�
void Midi_OutputError(MMRESULT mmrErrCode)
{
    // ���� ���ڿ��� ������ �迭
    char m_szErrMsg[128];

    // ���� �ڵ带 ���ڿ��� ��ȯ
    midiInGetErrorText(mmrErrCode, (char*)m_szErrMsg, sizeof(m_szErrMsg));

    // ��ȯ�� ���ڿ��� �޽��� �ڽ��� ���
    MessageBox(0, m_szErrMsg, "Midi Error!!!", MB_OK);
}

// �̵� ��ġ ��ȣ�� �˾� ���� �Լ�
// �̵���ġ�� �Ӽ��� �˾Ƴ��� �� �Լ��� �ʿ�
long Midi_GetDevID(HMIDIOUT m_DevOutHandle)
{
    // ��ġ ��ȣ�� ������ ����
    UINT     uDeviceID;

    // �̵� ��� �ڵ鿡 �����ϴ� ��ġ ��ȣ�� �����ؼ� uDeviceID������ ����
    MMRESULT Result = midiOutGetID(m_DevOutHandle, &uDeviceID);

    // ��ġ�� �����ϴ� �߿� ������ ���� �����ϸ�...
    if (Result != MMSYSERR_NOERROR) {
        // ���� ��� �� ������ ����� ���ϰ����� �˸�
        Midi_OutputError(Result);
        return -1;
    }

    // ��ġ ��ȣ�� ����
    return (long)uDeviceID;
}


// �̵� �ڵ��� �̿��� �̵� ��ġ �Ӽ���
// MIDIOUTCAPS����ü ������ �������ִ� �Լ�
void Midi_GetDevCaps(HMIDIOUT m_DevOutHandle, MIDIOUTCAPS* Caps)
{
    // ��ġ ��ȣ�� ������ ����
    long lDeviceID;

    // ���� �ڵ带 ������ ����
    MMRESULT Result;

    // �̵� �ڵ��� �̿��� ��ġ ��ȣ�� �����ؼ�
    // lDeviceID������ ����
    lDeviceID = Midi_GetDevID(m_DevOutHandle);

    // lDeviceID�� ������ ������ �� ����̹Ƿ�
    // �� �Լ��� ó���� ���̻� �������� �ʴ´�.
    if (lDeviceID < 0) return;

    // �̵� ��ġ�� �Ӽ��� MIDIOUTCAPS����ü ������ �����Ѵ�.
    Result = midiOutGetDevCaps((UINT)lDeviceID, Caps, sizeof(MIDIOUTCAPS));

    // ������ ���ٸ� �������ڿ��� ����Ѵ�.
    if (Result != MMSYSERR_NOERROR) Midi_OutputError(Result);
}

// ��ġ��ȣ�� �ش��ϴ� �̵���ġ�� ����.
HMIDIOUT Midi_Open(WORD wDevsNum)
{
    WORD      wMaxDevNum = 0;
    MMRESULT  uiMidiOpen = 0;
    HMIDIOUT  m_DevHandle = NULL;

    // ��밡���� ��ġ�� �� ������ wMaxDevNum������ ����
    wMaxDevNum = midiInGetNumDevs();

    // �Է��� ��ȣ�� �� �������� ���ų� ū ���̸�
    // ������ ��ġ��ȣ�� 0���� �����Ѵ�.
    if (wDevsNum >= wMaxDevNum) wDevsNum = 0;

    // wDevsNum������ ����� ���� �ش��ϴ� �̵���ġ��
    // ���� �� ��ġ�ڵ鰪�� m_DevHandle�� ����
    // �����߿� �߻��ϴ� �޽����� �ݹ��Լ� MidiOutProc�� ����

    uiMidiOpen = midiOutOpen(&m_DevHandle, wDevsNum, (DWORD)(MidiOutProc), (DWORD)NULL, CALLBACK_FUNCTION);

    // ���� ���� ������ �߻��ϸ�
    if (uiMidiOpen != MMSYSERR_NOERROR) {
        //�������ڿ��� ����Ѵ�.
        Midi_OutputError(uiMidiOpen);

        // NULL���� ����
        return NULL;
    }

    // ��ġ �ڵ��� ����
    return m_DevHandle;
}



// �ڵ鰪�� �ش��ϴ� �̵���ġ�� �ݽ��ϴ�.
LRESULT Midi_Close(HMIDIOUT m_DevOutHandle)
{
    MMRESULT Result;
    // �̵� �ڵ鰪�� �̿��� ��ġ�� �ݽ��ϴ�.
    Result = midiOutClose(m_DevOutHandle);
    
    // �ݴ� ���߿� ������ �����
    if (Result != MMSYSERR_NOERROR){
        // ���� ���
        Midi_OutputError(Result);
        // �ݱ� ���и� ���ϰ����� �˸�
        return FALSE;
    }

    // �ݱ� ������ ���ϰ����� �˸�
    return TRUE;
}



// ª�� �̵� �޽����� �̵� ��ġ�� ������ �Լ�
void Midi_SendShortMsg(HMIDIOUT m_DevOutHandle, BYTE byteState, BYTE byteNote, BYTE byteValo)
{
    MJGRShortMidiMSG  sMsg;

    // MJGRShortMidiMSG����ü�ȿ� �ִ�
    // MJGRShortMidiMSG_ST����ü ������ �� ��� ������
    // ���� ä���ִ´�.
    sMsg.stMidi_Data.byteVelocity = byteValo;
    sMsg.stMidi_Data.byteNote = byteNote;
    sMsg.stMidi_Data.byteState = byteState;
    sMsg.stMidi_Data.byteNULL = 0;

    // ��� ��ġ�� ���� ä������ ����ü�� �����͸� ������.
    midiOutShortMsg(m_DevOutHandle, sMsg.dwMidi_Data);
}



// �� �̵� �޽����� �̵� ��ġ�� ������ �Լ�
void Midi_SendLongMsg(HMIDIOUT m_DevOutHandle, BYTE* lpMsg, DWORD dwMsgLength)
{
    MIDIHDR  m_MIDIHdr;
    MMRESULT Result;

    ZeroMemory(&m_MIDIHdr, sizeof(MIDIHDR));

    m_MIDIHdr.lpData = (char*)lpMsg;
    m_MIDIHdr.dwBufferLength = dwMsgLength;
    m_MIDIHdr.dwFlags = 0;

    // �� �̵����͸� ��ġ�� ������ ���� �غ��۾��� ��
    Result = midiOutPrepareHeader(m_DevOutHandle, &m_MIDIHdr, sizeof(MIDIHDR));

    if (Result != MMSYSERR_NOERROR){
        Midi_OutputError(Result);
        return;
    }

    // �� �̵����͸� ��ġ�� ����
    Result = midiOutLongMsg(m_DevOutHandle, &m_MIDIHdr, sizeof(MIDIHDR));

    if (Result != MMSYSERR_NOERROR){
        Midi_OutputError(Result);
        return;
    }



    // �� �̵����͸� ��ġ�� ������ ���� �۾��� ����
    midiOutUnprepareHeader(m_DevOutHandle, &m_MIDIHdr, sizeof(MIDIHDR));
}

// ��� ä���� �������� ���� �����ϰ� ����� �Լ�...
void Midi_AllChannelSoundOff(HMIDIOUT m_DevOutHandle)
{
    BYTE channel;

    for (channel = 0; channel < 16; channel++){
        Midi_SendShortMsg(m_DevOutHandle, (BYTE)(0xB0 + channel), 0x78, 0);
    }

}