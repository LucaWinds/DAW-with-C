#include "MIDI.h"
#include "MusicHeader.h"



void print_map()
{
    int i;
    system("cls");
    setcolor(white, black);//�������� ������ֱ�
    for (i = 0; i < 24; i++)
    {

        printf("                                                                                                                                               ");

    }
    
    gotoxy(0, 0);
    printf("[ESC] : ����\n");
    puts("�� �� ���� �� �� �� ���� ���� �� �� �� ���� �� �� �� ���� ���� �� �� �� ���� �� �� �� ���� ���� �� ��");
    puts("�� �� ���� �� �� �� ���� ���� �� �� �� ���� �� �� �� ���� ���� �� �� �� ���� �� �� �� ���� ���� �� ��");
    puts("�� �� ���� �� �� �� ���� ���� �� �� �� ���� �� �� �� ���� ���� �� �� �� ���� �� �� �� ���� ���� �� ��");
    puts("�� �� ���� �� �� �� ���� ���� �� �� �� ���� �� �� �� ���� ���� �� �� �� ���� �� �� �� ���� ���� �� ��");
    puts("�� �� ���� �� �� �� ���� ���� �� �� �� ���� �� �� �� ���� ���� �� �� �� ���� �� �� �� ���� ���� �� ��");
    puts("�� ������������ �� ������������������ �� ������������ �� ������������������ �� ������������ �� ������������������ ��");
    puts("��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��");
    puts("��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��");
    puts("��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��");
    puts("��������������������������������������������������������������������������������������������������������������������������������");
   

    gotoxy(0, 20); printf("����������������������������������������������������������������������������������������������������������������������������������������������");
    gotoxy(0, 21); printf("���Ǳ� ���� : ��Ű ��Ű : 1ĭ�� �̵� �� ȭ�� ON / OFF : F1Ű            ��");
    gotoxy(0, 22); printf("������ ���� ���� : EscŰ             �� ���� ���� : ��Ű ��Ű           ��");
    gotoxy(0, 23); printf("����������������������������������������������������������������������������������������������������������������������������������������������");
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
            //��    ��     �� ��     ��    ��    ��  ��     ��    ��


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
//��    ��     �� ��     ��    ��    ��  ��     ��    ��
//////////////    �������� �����    /////////////////////////
int j_1 = 0;  // �Ǻ�1 ��������
int j_2 = 0;  // �Ǻ�2 ��������
int inst[12] = { 0,  4, 5,10, 6, 7, 8, 14, 12, 108,0 };
int check = 0;
int hwaum = 1;
static int volume = 127;
int thread_on = 1;
static int speed = 180; // ũ�� Ŭ���� ����!
//////////////////////////////////////////////////////////////
void Finish() //����
{
    
    system("cls");
    //�ε���... (�̰� ��Ʈ�������� ���� ����)
    printf("\n\n\n                                 NOW LOADING...                                       \n\n\n      ");
    for (int i = 0; i < 22; i++) {
        printf("�� ");
        Sleep(50);
    }
    Sleep(400);
    system("cls");
    Midi_AllChannelSoundOff(m_DevHandle);

    Hub();

    return;
}
unsigned __stdcall Thread_inst(void* arg)//������ �Ǳ� �� Ű����
{
    gotoxy(0, 15); printf("�� �� : %d  ", volume);
    gotoxy(0, 11); printf("���� �Ǳ� : %d. ", check + 1); find_inst(check);

    while (note2[j_2] != 100)
    {
        if (_kbhit() == 1)if (_getch() == 27) Finish(); // esc �������� ����
        else if (GetKeyState(VK_RIGHT) < 0)
        { // �Ǳ� �ٲٱ�, 1++
            check = check + 1;
            inst[10] = inst[check];
            if (9 < check) check = 0, inst[10] = 0;
            gotoxy(0, 11); printf("���� �Ǳ� : %d. ", check + 1); find_inst(check);
            Midi_SendShortMsg(m_DevHandle, CHANGE_INST, inst[10], 0);
            Sleep(200);


        }
        else if (GetKeyState(VK_LEFT) < 0)
        { // �Ǳ� �ٲٱ�, 1--
            check = check - 1;
            inst[10] = inst[check];
            if (check < 0) check = 9, inst[10] = 9;
            gotoxy(0, 11); printf("���� �Ǳ� : %d. ", check + 1); find_inst(check);
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
            gotoxy(0, 15); printf("�� �� : %d  ", volume);
            Sleep(60);

        }
        else if (GetKeyState(VK_UP) < 0)
        {
            volume++;
            if (volume > 127)
            {
                volume = 127;
            }
            gotoxy(0, 15); printf("�� �� : %d  ", volume);
            Sleep(60);
        }

        if (hwaum % 2 == 1)
        {

            gotoxy(0, 13); printf("ȭ �� : ���� ");
            Sleep(100);


        }

        else if (hwaum % 2 == 0)
        {

            gotoxy(0, 13); printf("ȭ �� : ���� ");
            Sleep(100);

        }


    } // while(note2[j_2] != 100) ������ �κ�

    return 0; // ������ ����
}

unsigned __stdcall Thread_note1(void* arg)//������ ȭ��
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
            else if (note1[j_1] >= 200 && note1[j_1] <= 300) // ���ÿ� ���� ĥ��
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

        // ȭ�� ������ ��� �۾�
        if (hwaum % 2 == 0)
        {

            if (note1[j_1] == 0) { Sleep(speed * 2); j_1++; }
            else if (note1[j_1] >= 200 && note1[j_1] <= 300) { j_1++; }
            else { Sleep(speed * 2); j_1++; }


        }

    }
    return 0; // ������ ����

}

void MusicListen()
{
    system("mode con: cols=143 lines=24"); // �ǾƳ� �ǹ����� ȭ�� ũ�� ����
    system("cls");

    print_map(); // �ǹ�ǥ��
    gotoxy(0, 0);

    Midi_AllChannelSoundOff(m_DevHandle);
    Midi_SendShortMsg(m_DevHandle, 0xB0, 7, 127);



    while (1)
    {
        if (thread_on == 1)
        {
            _beginthreadex(NULL, 0, Thread_inst, 0, 0, NULL);////////////////////////������ ����
            _beginthreadex(NULL, 0, Thread_note1, 0, 0, NULL);////////////////////////������ ����  
            thread_on = 0; // �뷡������ �� ������ �ߵ��ɼ��� �־(�ߵ��� �����߻�)
        }


        while (note2[j_2] != 100)
        {

            if (note2[j_2] == 0) // ��ǥ ǥ��
            {
                Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + note2[j_2] + 100), volume);//30+i
                Sleep(speed * 2);
                j_2++;
            }
            else if (note2[j_2] >= 200 && note2[j_2] <= 300) // ���ÿ� �ľߵɶ�
            {
                Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + note2[j_2] - 200 + 22), volume);
                j_2++;
            }
            else if (note2[j_2] > 300 && note2[j_2] <= 400) // �̾ �ٷ� �ľߵɶ�1 (���ڹ���)
            {
                Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + note2[j_2] - 300 + 22), volume);
                Sleep(30);
                j_2++;

            }
            else if (note2[j_2] > 3300 && note2[j_2] <= 3400) // �̾ �ٷ� �ľߵɶ�2 (���ڹ���)
            {
                Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + note2[j_2] - 3300 + 22), volume);
                Sleep(speed * 2 - 30);
                j_2++;

            }
            else if (note2[j_2] > 400 && note2[j_2] <= 500) // 1/2���� ¥�� ���ö� 
            { //500�� �ݹ� ��ǥ
                Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + note2[j_2] - 400 + 22), volume);
                Sleep(speed);
                j_2++;

            }
            else
            {
                Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + note2[j_2] + 22), volume); // ����
                Sleep(speed * 2);
                j_2++;
            }

        }

        Sleep(speed * 2);
        Midi_AllChannelSoundOff(m_DevHandle); // �ܷ��ϴ� ���� ��� ����

        gotoxy(0, 19); printf("�ٽ� �����ðڽ��ϱ�? (y / n)");

        if (_getch() == 'y' || _getch() == 'Y')
        {
            j_1 = 0;
            j_2 = 0;
            thread_on = 1;

            gotoxy(0, 19); printf("                            "); // �ٽ� �����ðڽ��ϱ� �����

            continue;
        }
        else if (_getch() == 'n' || _getch() == 'N')
        {
            break;
        }

    } // while(1) ������ ��

    Finish();
}

