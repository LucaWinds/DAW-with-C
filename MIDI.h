#pragma once

// �������� ���� �ڿ� ��ũ�� �� winmm.lib������ �߰���
#pragma comment(lib, "winmm.lib")

#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>
#include <process.h> // ������ �̿�

#define CHANGE_INST 0xC0 // �Ǳ� ���� ����



MCI_OPEN_PARMS      mciOpen; //������ �ε�

MCI_PLAY_PARMS       mciPlay; //������ ���

MCI_STATUS_PARMS   mciStatus; //������ ����


// ���ĺ��� ����Ǵ� ����ü�� ���� ����� 1����Ʈ ������ ��
// ������ ���� ����� ������ ����
#pragma pack(push,1)


// ª�� �̵�޽����� ����ü
typedef struct
{
    BYTE byteState;    // �̵� �޽���
    BYTE byteNote;     // �޽����� ���� ��
    BYTE byteVelocity; // Ű���带 �����ų� ������ �ӵ�
    BYTE byteNULL;
}MJGRShortMidiMSG_ST;

// MJGRShortMidiMSG_ST ����ü�� ����
// DWORD������ �ٲܶ� �ÿ��� ����ü
// DWORD�� unsigned long�Դϴ�.

typedef union
{
    DWORD                dwMidi_Data;
    MJGRShortMidiMSG_ST  stMidi_Data;
}MJGRShortMidiMSG;

// ������ ����ü ���� ������� �ٲ�
#pragma pack(pop)

// �̵� ��� �ڵ�
// �� �ڵ� ������ �̿��� ������ �̵���ġ�� ��Ʈ�� �մϴ�.
HMIDIOUT     m_DevHandle;

// ������ ������� �����ڵ带 �����ϴ� ����
MMRESULT     m_MMErrCode;

// ���� �̵� ��¿� ���� ��ġ �Ӽ��� ������ ����ü ����
MIDIOUTCAPS  m_NowMidiOutCaps;

// MIDI �Լ� ���� | MIDI.c
void CALLBACK MidiOutProc(HMIDIOUT MidiOut, UINT Msg, DWORD Instance, DWORD Param1, DWORD Param2);
void Midi_OutputError(MMRESULT mmrErrCode);
long Midi_GetDevID(HMIDIOUT m_DevOutHandle);
void Midi_GetDevCaps(HMIDIOUT m_DevOutHandle, MIDIOUTCAPS* Caps);
HMIDIOUT Midi_Open(WORD wDevsNum);
LRESULT Midi_Close(HMIDIOUT m_DevOutHandle);
void Midi_SendShortMsg(HMIDIOUT m_DevOutHandle, BYTE byteState, BYTE byteNote, BYTE byteValo);
void Midi_SendLongMsg(HMIDIOUT m_DevOutHandle, BYTE* lpMsg, DWORD dwMsgLength);
void Midi_AllChannelSoundOff(HMIDIOUT m_DevOutHandle);