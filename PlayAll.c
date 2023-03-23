#include "PlayAll.h"
#include "MIDI.h"
#include "MusicHeader.h"

/* 노트 선언 */
static int Pianonote[10000] = { 0 };
static int Synthnote[10000] = { 0 };
static int Bassnote[10000] = { 0 };
/* 전역변수 선언 */
static int MusicTime1= 0;
static int MusicTime2 = 0;
static int MusicTime3 = 0;
static int MusicTime4 = 0;

static int Speed = 150; // Speed * 8 => 한 마디 당 시간 (ms)
static int Volume = 127;

int stop = 0;
int Thread = 1;

/*함수 선언*/
unsigned __stdcall ThreadPiano(void* arg);
unsigned __stdcall ThreadSynth(void* arg);
unsigned __stdcall ThreadBass(void* arg);


void PlayAll(int note1[], int note2[], int note3[], int Drum[][4])
{
    Thread = 1;
    //노트 복사
    memcpy(Pianonote, note1, sizeof(int) * 10000);
    memcpy(Synthnote, note2, sizeof(int) * 10000);
    memcpy(Bassnote, note3, sizeof(int) * 10000);
    
    if (Thread == 1)
    {
        _beginthreadex(NULL, 0, ThreadPiano, 0, 0, NULL);////////////////////////스레드 시작
        _beginthreadex(NULL, 0, ThreadSynth, 0, 0, NULL);////////////////////////스레드 시작  
        _beginthreadex(NULL, 0, ThreadBass, 0, 0, NULL);////////////////////////스레드 시작  
        Thread = 0; // 노래끝난후 또 스레드 발동될수도 있어서(발동시 잡음발생)
    }
    
    system("cls");

    printf("NOW PLAYING!\n");

    printf("[ESC] 로 음악을 중지합니다.\n");
    stop = 0;

    //드럼 루프 구현!!__
    while (!stop) {
        if (_kbhit() == 1)if (_getch() == 27) {
            stop = 1;
        }

        if (_kbhit() == 1) if (_getch() == UP) {
            Speed++;
        }

        if (_kbhit() == 1) if (_getch() == DOWN) {
            Speed--;
        }

        MusicTime4++;
        if (MusicTime4 >= 64) MusicTime4 = 0;


        gotoxy(0, 5); printf("현재 마디 : %d/8", (MusicTime4/8)+1);
        gotoxy(0, 6); printf("현재 박자 : %d/8", (MusicTime4%8)+1);

        gotoxy(0, 8); MusicTime4 % 2 == 0 ? printf("*") : printf("-");

        gotoxy(0, 10); printf("현재 속도 : %d\n도움말 : 속도는 노트의 연주 길이를 뜻합니다. 클 수록 느리고, 작을수록 빠릅니다.\n[위쪽 화살표] : 증가, [아래쪽 화살표] : 감소", Speed);

        Sleep(Speed);
    }

    MusicProduct();
}

unsigned __stdcall ThreadPiano(void* arg)
{
    if (Pianonote[MusicTime1] == 100) {
        MusicTime1 = 0;

    }

    while (!stop) {
        if (Pianonote[MusicTime1] == 0) // 쉼표 표현
        {
            Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Pianonote[MusicTime1] + 100), Volume);//30+i
            Sleep(Speed * 2);
            MusicTime1++;
        }
        else if (Pianonote[MusicTime1] >= 200 && Pianonote[MusicTime1] <= 300) // 동시에 쳐야될때
        {
            Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Pianonote[MusicTime1] - 200 + 10), Volume);
            MusicTime1++;
        }
        else if (Pianonote[MusicTime1] > 300 && Pianonote[MusicTime1] <= 400) // 이어서 바로 쳐야될때1 (박자무관)
        {
            Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Pianonote[MusicTime1] - 300 + 22), Volume);
            Sleep(30);
            MusicTime1++;
        }
        else if (Pianonote[MusicTime1] > 3300 && Pianonote[MusicTime1] <= 3400) // 이어서 바로 쳐야될때2 (박자무관)
        {
            Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Pianonote[MusicTime1] - 3300 + 22), Volume);
            Sleep(Speed * 2 - 30);
            MusicTime1++;
        }
        else if (Pianonote[MusicTime1] > 400 && Pianonote[MusicTime1] <= 500) // 1/2박자 짜리 나올때 
        { //500은 반박 쉼표
            Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Pianonote[MusicTime1] - 400 + 10), Volume);
            Sleep(Speed);
            MusicTime1++;
        }
        else
        {
            Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Pianonote[MusicTime1] + 10), Volume); // 연주
            Sleep(Speed * 2);
            MusicTime1++;
        }
    }
}
unsigned __stdcall ThreadSynth(void* arg)
{
    if (Synthnote[MusicTime2] == 100) {
        MusicTime2 = 0;
        Midi_AllChannelSoundOff(m_DevHandle); // 잔류하던 음을 모두 종료
    }
    
    while (!stop) {
        
        
        if (Synthnote[MusicTime2] == 100) {
            MusicTime2 = 0;
        }

        if (Synthnote[MusicTime2] == 0) // 쉼표 표현
        {
            Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Synthnote[MusicTime2] + 100), Volume);//30+i
            Sleep(Speed * 2);

            MusicTime2++;
        }
        else if (Synthnote[MusicTime2] >= 200 && Synthnote[MusicTime2] <= 300) // 동시에 쳐야될때
        {
            Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Synthnote[MusicTime2] - 200 + 10), Volume);
            MusicTime2++;
        }
        else if (Synthnote[MusicTime2] > 300 && Synthnote[MusicTime2] <= 400) // 이어서 바로 쳐야될때1 (박자무관)
        {
            Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Synthnote[MusicTime2] - 300 + 22), Volume);
            MusicTime2++;
            Sleep(30);
        }
        else if (Synthnote[MusicTime2] > 3300 && Synthnote[MusicTime2] <= 3400) // 이어서 바로 쳐야될때2 (박자무관)
        {
            Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Synthnote[MusicTime2] - 3300 + 22), Volume);
            Sleep(Speed * 2 - 30);
            MusicTime2++;
        }
        else if (Synthnote[MusicTime2] > 400 && Synthnote[MusicTime2] <= 500) // 1/2박자 짜리 나올때 
        { //500은 반박 쉼표
            Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Synthnote[MusicTime2] - 400 + 10), Volume);
            MusicTime2++;
            Sleep(Speed);
        }
        else
        {
            Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Synthnote[MusicTime2] + 10), Volume); // 연주
            MusicTime2++;
            Sleep(Speed * 2);
        }
    }
}
unsigned __stdcall ThreadBass(void* arg)
{
    if (Bassnote[MusicTime3] == 100) {
        MusicTime3 = 0;
        Midi_AllChannelSoundOff(m_DevHandle); // 잔류하던 음을 모두 종료
    }
    
    while (!stop) {

        if (Bassnote[MusicTime3] == 0) // 쉼표 표현
        {
            Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Bassnote[MusicTime3] + 100), Volume);//30+i
            Sleep(Speed * 2);

            MusicTime3++;
        }
        else if (Bassnote[MusicTime3] >= 200 && Bassnote[MusicTime3] <= 300) // 동시에 쳐야될때
        {
            Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Bassnote[MusicTime3] - 200 - 2), Volume);
            MusicTime3++;
        }
        else if (Bassnote[MusicTime3] > 300 && Bassnote[MusicTime3] <= 400) // 이어서 바로 쳐야될때1 (박자무관)
        {
            Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Bassnote[MusicTime3] - 300 + 22), Volume);
            MusicTime3++;
            Sleep(30);
        }
        else if (Bassnote[MusicTime3] > 3300 && Bassnote[MusicTime3] <= 3400) // 이어서 바로 쳐야될때2 (박자무관)
        {
            Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Bassnote[MusicTime3] - 3300 + 22), Volume);
            MusicTime3++;
            Sleep(Speed * 2 - 30);
        }
        else if (Bassnote[MusicTime3] > 400 && Bassnote[MusicTime3] <= 500) // 1/2박자 짜리 나올때 
        { //500은 반박 쉼표
            Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Bassnote[MusicTime3] - 400 - 2), Volume);
            MusicTime3++;
            Sleep(Speed);
        }
        else
        {
            Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Bassnote[MusicTime3] - 2), Volume); // 연주
            Sleep(Speed * 2);
            MusicTime3++;
        }
	}
}
