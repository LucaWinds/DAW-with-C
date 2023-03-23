#pragma once

// 컴파일이 끝난 뒤에 링크할 때 winmm.lib파일을 추가함
#pragma comment(lib, "winmm.lib")

#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>
#include <process.h> // 쓰레드 이용

#define CHANGE_INST 0xC0 // 악기 변주 정의



MCI_OPEN_PARMS      mciOpen; //파일을 로드

MCI_PLAY_PARMS       mciPlay; //파일을 재생

MCI_STATUS_PARMS   mciStatus; //파일의 상태


// 이후부터 선언되는 구조체의 정렬 방식을 1바이트 단위로 함
// 원래의 정렬 방식을 저장해 놓음
#pragma pack(push,1)


// 짧은 미디메시지의 구조체
typedef struct
{
    BYTE byteState;    // 미디 메시지
    BYTE byteNote;     // 메시지에 대한 값
    BYTE byteVelocity; // 키보드를 누르거나 뗄때의 속도
    BYTE byteNULL;
}MJGRShortMidiMSG_ST;

// MJGRShortMidiMSG_ST 구조체의 값을
// DWORD형으로 바꿀때 시용할 공용체
// DWORD는 unsigned long입니다.

typedef union
{
    DWORD                dwMidi_Data;
    MJGRShortMidiMSG_ST  stMidi_Data;
}MJGRShortMidiMSG;

// 원래의 구조체 정렬 방식으로 바꿈
#pragma pack(pop)

// 미디 출력 핸들
// 이 핸들 변수를 이용해 지정된 미디장치를 컨트롤 합니다.
HMIDIOUT     m_DevHandle;

// 에러가 났을경우 에러코드를 저장하는 변수
MMRESULT     m_MMErrCode;

// 현재 미디 출력에 관한 장치 속성을 저장할 구조체 변수
MIDIOUTCAPS  m_NowMidiOutCaps;

// MIDI 함수 정의 | MIDI.c
void CALLBACK MidiOutProc(HMIDIOUT MidiOut, UINT Msg, DWORD Instance, DWORD Param1, DWORD Param2);
void Midi_OutputError(MMRESULT mmrErrCode);
long Midi_GetDevID(HMIDIOUT m_DevOutHandle);
void Midi_GetDevCaps(HMIDIOUT m_DevOutHandle, MIDIOUTCAPS* Caps);
HMIDIOUT Midi_Open(WORD wDevsNum);
LRESULT Midi_Close(HMIDIOUT m_DevOutHandle);
void Midi_SendShortMsg(HMIDIOUT m_DevOutHandle, BYTE byteState, BYTE byteNote, BYTE byteValo);
void Midi_SendLongMsg(HMIDIOUT m_DevOutHandle, BYTE* lpMsg, DWORD dwMsgLength);
void Midi_AllChannelSoundOff(HMIDIOUT m_DevOutHandle);