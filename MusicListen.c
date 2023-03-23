#include "MIDI.h"
#include "MusicHeader.h"



void print_map()
{
    int i;
    system("cls");
    setcolor(white, black);//흰배경으로 만들어주기
    for (i = 0; i < 24; i++)
    {

        printf("                                                                                                                                               ");

    }
    
    gotoxy(0, 0);
    printf("[ESC] : 종료\n");
    puts("┃ ┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃┃ ┃ ┃");
    puts("┃ ┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃┃ ┃ ┃");
    puts("┃ ┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃┃ ┃ ┃");
    puts("┃ ┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃┃ ┃ ┃");
    puts("┃ ┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃ ┃ ┃ ┃┃ ┃┃ ┃ ┃");
    puts("┃ ┗━┛┗━┛ ┃ ┗━┛┗━┛┗━┛ ┃ ┗━┛┗━┛ ┃ ┗━┛┗━┛┗━┛ ┃ ┗━┛┗━┛ ┃ ┗━┛┗━┛┗━┛ ┃");
    puts("┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃");
    puts("┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃");
    puts("┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃");
    puts("┗━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┻");
   

    gotoxy(0, 20); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
    gotoxy(0, 21); printf("┃악기 변경 : ←키 →키 : 1칸씩 이동 ┃ 화음 ON / OFF : F1키            ┃");
    gotoxy(0, 22); printf("┃연주 도중 종료 : Esc키             ┃ 음량 조절 : ↑키 ↓키           ┃");
    gotoxy(0, 23); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
    gotoxy(0, 0);
}


void find_inst(int check)
{ //    int inst[12] = {0, 1, 4, 5, 6, 7, 8, 14, 12, 108,0}; 

    if (check == 0) printf("Acoustic Grand                ");
    else if (check == 1) printf("Electric Piano 1         ");
    else if (check == 2) printf("Electric Piano 2         ");
    else if (check == 3) printf("Music Box                ");
    else if (check == 4) printf("Harpsichord              ");
    else if (check == 5) printf("Clav                     ");
    else if (check == 6) printf("Celesta                  ");
    else if (check == 7) printf("Tubular Bells            ");
    else if (check == 8) printf("Marimba                  ");
    else if (check == 9) printf("Kalimba                  ");
}

int note1[10000] = {
    
    0,0,-1,6,15,0,1,1,0,0,      -6,1,10,0,3,-2,3,6,
                    -1,6,15,0,1,8,0,0,            3,-2,3,6,6,0,3,0,

                    211,-1,6,15,0,1,8,0,0,      6,13,17,0,3,15,18,0,
                    -1,11,15,0,1,13,17,0,       3,10,15,0,

                    0,0,0,0,1,8,17,0,-11,3,0,0,  -4,3,12,0,-7,-1,5,8,
                    1,8,17,0,3,10,0,0,           -7,-1,5,8,0,0,-7,0,

                    201,-10,8,17,0,3,12,0,0,    -4,3,8,0,-7,5,8,0,
                    -11,1,5,0,-9,3,6,0,               -7,-1,5,0,8,10,12,0,

                    100
};
//   printf("   [W]   [E]       [T]   [Y]   [U]       [O]   [P]\n\n");
//    printf("[A]   [S]   [D] [F]   [G]   [H]   [J] [K]   [L]   [;] [\"]\n");
            // 1  2  3  4  5  6  7   8  9 10  11 12  13  14 15 16 17    
            //도    레     미 파     솔    라    시  도     레    미


int note2[10000] = {

    
                    0,18,30,29,0,27,220,27,25,13,20,         320,3322,0,0,420,422,18,0,0,18,
                    30,29,0,27,220,27,25,13,20,              20,22,0,0,18,20,22,25,

                    30,29,0,27,220,27,25,13,20,              320,3322,0,0,420,422,18,0,15,18,
                    20,0,22,0,15,18,20,22,                   20,0,0,18,

                    0,0,0,8,20,19,0,17,210,17,15,3,10,       310,3312,0,0,410,412,8,0,0,8,
                    20,19,0,17,210,17,15,3,10,10,            310,12,0,0,8,10,12,15,

                    20,19,0,17,210,17,15,3,10,               310,3312,0,0,410,412,8,0,5,8,
                    201,10,0,12,0,5,8,10,12,                    203,10,0,0,8,0,0,0,8,
                    100
                    
};
// 1  2  3  4  5  6  7   8  9 10  11 12 13 14 15 16 17    
//도    레     미 파     솔    라    시  도     레    미
//////////////    전역변수 저장소    /////////////////////////
int j_1 = 0;  // 악보1 전역변수
int j_2 = 0;  // 악보2 전역변수
int inst[12] = { 0,  4, 5,10, 6, 7, 8, 14, 12, 108,0 };
int check = 0;
int hwaum = 1;
static int volume = 127;
int thread_on = 1;
static int speed = 180; // 크면 클수록 느림!
//////////////////////////////////////////////////////////////
void Finish() //종료
{
    
    system("cls");
    //로딩중... (이거 테트리스에서 쓴거 맞음)
    printf("\n\n\n                                 NOW LOADING...                                       \n\n\n      ");
    for (int i = 0; i < 22; i++) {
        printf("■ ");
        Sleep(50);
    }
    Sleep(400);
    system("cls");
    Midi_AllChannelSoundOff(m_DevHandle);

    Hub();

    return;
}
unsigned __stdcall Thread_inst(void* arg)//스레드 악기 및 키조작
{
    gotoxy(0, 15); printf("음 량 : %d  ", volume);
    gotoxy(0, 11); printf("현재 악기 : %d. ", check + 1); find_inst(check);

    while (note2[j_2] != 100)
    {
        if (_kbhit() == 1)if (_getch() == 27) Finish(); // esc 눌렀을때 종료
        else if (GetKeyState(VK_RIGHT) < 0)
        { // 악기 바꾸기, 1++
            check = check + 1;
            inst[10] = inst[check];
            if (9 < check) check = 0, inst[10] = 0;
            gotoxy(0, 11); printf("현재 악기 : %d. ", check + 1); find_inst(check);
            Midi_SendShortMsg(m_DevHandle, CHANGE_INST, inst[10], 0);
            Sleep(200);


        }
        else if (GetKeyState(VK_LEFT) < 0)
        { // 악기 바꾸기, 1--
            check = check - 1;
            inst[10] = inst[check];
            if (check < 0) check = 9, inst[10] = 9;
            gotoxy(0, 11); printf("현재 악기 : %d. ", check + 1); find_inst(check);
            Midi_SendShortMsg(m_DevHandle, CHANGE_INST, inst[10], 0);
            Sleep(200);
        }
        else if (GetKeyState(VK_F1) < 0)
        {

            hwaum++;
            Sleep(200);
        }
        else if (GetKeyState(VK_DOWN) < 0)
        {
            volume--;
            if (volume < 0)
            {
                volume = 0;
            }
            gotoxy(0, 15); printf("음 량 : %d  ", volume);
            Sleep(60);

        }
        else if (GetKeyState(VK_UP) < 0)
        {
            volume++;
            if (volume > 127)
            {
                volume = 127;
            }
            gotoxy(0, 15); printf("음 량 : %d  ", volume);
            Sleep(60);
        }

        if (hwaum % 2 == 1)
        {

            gotoxy(0, 13); printf("화 음 : 켜짐 ");
            Sleep(100);


        }

        else if (hwaum % 2 == 0)
        {

            gotoxy(0, 13); printf("화 음 : 꺼짐 ");
            Sleep(100);

        }


    } // while(note2[j_2] != 100) 끝나는 부분

    return 0; // 스레드 종료
}

unsigned __stdcall Thread_note1(void* arg)//스레드 화음
{
    while (note2[j_2] != 100)
    {

        if (hwaum % 2 == 1)
        {

            if (note1[j_1] == 0)
            {
                Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + note1[j_1] + 100 + 11), volume);//30+i
                Sleep(speed*2);
                j_1++;
            }
            else if (note1[j_1] >= 200 && note1[j_1] <= 300) // 동시에 같이 칠때
            {
                Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + note1[j_1] - 200 - 1 + 11), volume);//30+i
                j_1++;
            }


            else
            {
                Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + note1[j_1] - 1 + 11), volume);//30+i
                Sleep(speed*2);
                j_1++;
            }


        }

        // 화음 껏을때 계속 작업
        if (hwaum % 2 == 0)
        {

            if (note1[j_1] == 0) { Sleep(speed * 2); j_1++; }
            else if (note1[j_1] >= 200 && note1[j_1] <= 300) { j_1++; }
            else { Sleep(speed * 2); j_1++; }


        }

    }
    return 0; // 스레드 종료

}

void MusicListen()
{
    system("mode con: cols=143 lines=24"); // 피아노 건반위해 화면 크기 조절
    system("cls");

    print_map(); // 건반표시
    gotoxy(0, 0);

    Midi_AllChannelSoundOff(m_DevHandle);
    Midi_SendShortMsg(m_DevHandle, 0xB0, 7, 127);



    while (1)
    {
        if (thread_on == 1)
        {
            _beginthreadex(NULL, 0, Thread_inst, 0, 0, NULL);////////////////////////스레드 시작
            _beginthreadex(NULL, 0, Thread_note1, 0, 0, NULL);////////////////////////스레드 시작  
            thread_on = 0; // 노래끝난후 또 스레드 발동될수도 있어서(발동시 잡음발생)
        }


        while (note2[j_2] != 100)
        {

            if (note2[j_2] == 0) // 쉼표 표현
            {
                Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + note2[j_2] + 100), volume);//30+i
                Sleep(speed * 2);
                j_2++;
            }
            else if (note2[j_2] >= 200 && note2[j_2] <= 300) // 동시에 쳐야될때
            {
                Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + note2[j_2] - 200 + 22), volume);
                j_2++;
            }
            else if (note2[j_2] > 300 && note2[j_2] <= 400) // 이어서 바로 쳐야될때1 (박자무관)
            {
                Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + note2[j_2] - 300 + 22), volume);
                Sleep(30);
                j_2++;

            }
            else if (note2[j_2] > 3300 && note2[j_2] <= 3400) // 이어서 바로 쳐야될때2 (박자무관)
            {
                Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + note2[j_2] - 3300 + 22), volume);
                Sleep(speed * 2 - 30);
                j_2++;

            }
            else if (note2[j_2] > 400 && note2[j_2] <= 500) // 1/2박자 짜리 나올때 
            { //500은 반박 쉼표
                Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + note2[j_2] - 400 + 22), volume);
                Sleep(speed);
                j_2++;

            }
            else
            {
                Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + note2[j_2] + 22), volume); // 연주
                Sleep(speed * 2);
                j_2++;
            }

        }

        Sleep(speed * 2);
        Midi_AllChannelSoundOff(m_DevHandle); // 잔류하던 음을 모두 종료

        gotoxy(0, 19); printf("다시 들으시겠습니까? (y / n)");

        if (_getch() == 'y' || _getch() == 'Y')
        {
            j_1 = 0;
            j_2 = 0;
            thread_on = 1;

            gotoxy(0, 19); printf("                            "); // 다시 들으시겠습니까 지우기

            continue;
        }
        else if (_getch() == 'n' || _getch() == 'N')
        {
            break;
        }

    } // while(1) 닫히는 곳

    Finish();
}

