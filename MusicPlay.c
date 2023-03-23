#include "MIDI.h"
#include "MusicHeader.h"



UINT wDeviceID = 0;


/**
DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave)
{

    DWORD Result;


    mciOpenParms.lpstrDeviceType = L"WaveAudio";

    //WaveAudio 대신 MPEGVideo를 사용하면 mp3 형식을 재생합니다.


    mciOpenParms.lpstrElementName = lpszWave;

    Result = mciSendCommand(wDeviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpenParms);

    if (Result)
        return Result;

    wDeviceID = mciOpenParms.wDeviceID;

    mciPlayParms.dwCallback = (DWORD)hWnd;

    if (Result)
        return Result;


    return 0;
}*/

void MusicPlay()
{
    int  i;
    BYTE szMusKey[18] = { 0x41,0x57,0x53,0x45,0x44,
                        0x46,0x54,0x47,0x59,0x48,
                        0x55,0x4A,0x4B,0x4F,0x4C,
                        0x50,0xBA,0xDE };
    BYTE szMusKeyOnOff[18] = { 0 };


    gotoxy(0, 0);
    printf("[ESC] : 종료\n");
    puts("┃ ┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃ ┃ ┃ ");
    puts("┃ ┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃ ┃ ┃ ");
    puts("┃ ┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃ ┃ ┃ ");
    puts("┃ ┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃ ┃ ┃ ");
    puts("┃ ┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃ ┃ ┃ ");
    puts("┃ ┗W┛┗E┛ ┃ ┗T┛┗Y┛┗U┛ ┃ ┗O┛┗P┛ ┃ ┗━");
    puts("┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃");
    puts("┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃");
    puts("┃ A┃ S┃ D┃ F┃ G┃ H┃ J┃ K┃ L┃ ;┃ \"┃");
    puts("┗━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┻");
    

    Midi_AllChannelSoundOff(m_DevHandle);
    Midi_SendShortMsg(m_DevHandle, 0xB0, 7, 127);
    char c = 0;
    while (1)
    {
        if (_kbhit())
        {
            c = _getch();
            if (c == ESC) goto A; //ESC
            else {
                for (i = 0; i < 18; i++){
                    if (GetKeyState(szMusKey[i]) & 0xFF00){
                        if (szMusKeyOnOff[i] == 0){
                            szMusKeyOnOff[i] = 1;
                            Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + i), 120);
                        }
                    }
                }
            }
        }

        for (i = 0; i < 18; i++){
            if (!(GetKeyState(szMusKey[i]) & 0xFF00)){
                if (szMusKeyOnOff[i] != 0){
                    szMusKeyOnOff[i] = 0;
                    Midi_SendShortMsg(m_DevHandle, 0x80, (BYTE)(0x30 + i), 120);
                }
            }
        }
    }
A:

    for (i = 0; i < 18; i++){
        if (szMusKeyOnOff[i] != 0){
            Midi_SendShortMsg(m_DevHandle, 0x80, (BYTE)(0x30 + i), 120);
        }
    }
    

    Midi_AllChannelSoundOff(m_DevHandle);

    system("cls");
    //로딩중... (이거 테트리스에서 쓴거 맞음)
    printf("\n\n\n                                 NOW LOADING...                                       \n\n\n      ");
    for (int i = 0; i < 22; i++) {
        printf("■ ");
        Sleep(50);
    }
    Sleep(400);
    system("cls");

    Hub();
}

/*
void MusicOpen() 
{
    DWORD Sound1, Sound2;

    Sound1 = LoadWav(hWnd, L"Sound1.wav");

    Sound2 = LoadWav(hWnd, L"Sound2.wav");
}
*/