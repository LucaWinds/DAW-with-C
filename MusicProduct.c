#include "MIDI.h"
#include "MusicHeader.h"
#include "PlayAll.h"


/* ��Ʈ ���� */
static int Pianonote[10000] = { 0 };
static int Synthnote[10000] = { 0 };
static int Bassnote[10000] = { 0 };
/* ���� ���� �迭 ���� */
int PianoLoop[64][25] = { 0 };
int SynthLoop[64][25] = { 0 };
int BassLoop[64][25] = { 0 };
int DrumLoop[64][4] = { 0 };

/* �������� ���� */
int mode = 0;
int EditX = 0;
int EditY = 0;
static int MusicTime = 0; 
static int Speed = 150; // Speed * 8 => �� ���� �� �ð� (ms)
static int Volume = 127;

/* ���� ���� : �Ǳ� <- ���߿� �����ϰ���..*/
int synthInst = 0;
int BassInst = 0;

/*���ο� �Ǳ� �Ҹ� üũ�� �� ���� �Լ�*/
void Test() {
    system("cls");
    for (int i = 0; i < 24; i++) {
        Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + i), 127);
        printf("i = %d", i);
        Sleep(200);
        system("cls");
    }


}

/* �Լ� ���� */
void DrumProduct();
void DrumDraw();

void PianoProduct();
void PianoDraw();
void PianoPlay();

void SynthProduct();
void SynthDraw();
void SynthPlay();

void BassProduct();
void BassDraw();
void BassPlay();


void MusicProduct()
{

    intro(); // ùȭ��
    system("mode con: cols=143 lines=50");

    gotoxy(5, 2); printf("Music Product Tool");
    gotoxy(5, 20); printf("��� ����, SPACE�� Ȯ��");

    int selection = 0;
    int c = 0;

    gotoxy(10, 7 + 2 * selection); printf(">");
    gotoxy(12, 7); printf("PIANO");
    gotoxy(12, 9); printf("SYNTH");
    gotoxy(12, 11); printf("BASS");
    gotoxy(12, 13); printf("DRUM");
    gotoxy(12, 15); printf("Play All");
    gotoxy(12, 17); printf("Exit");

    while (1)
    {
        if (_kbhit()) {        //Ű���� �Է� Ȯ�� (true / false)
            c = _getch();
            switch (c) {
            case UP:
                gotoxy(10, 7 + 2 * selection); printf("  ");
                selection = (--selection + 6) % 6;
                gotoxy(10, 7 + 2 * selection); printf(">");
                break;
            case DOWN:
                gotoxy(10, 7 + 2 * selection); printf("  ");
                selection = (++selection) % 6;
                gotoxy(10, 7 + 2 * selection); printf(">");
                break;
            case SPACE:
                if (selection == 0) PianoProduct();
                else if (selection == 1) SynthProduct();
                else if (selection == 2) BassProduct();
                else if (selection == 3) DrumProduct();
                else if (selection == 4) PlayAll(Pianonote, Synthnote, Bassnote, DrumLoop);
                else if (selection == 5) { system("cls"); Hub(0); }
                break;
            }
        }
    }
}

void DrumProduct()
{
    system("cls");
    mode = 0;
    EditX = 0;
    EditY = 0;
    MusicTime = 0;

    Midi_AllChannelSoundOff(m_DevHandle);

    Midi_SendShortMsg(m_DevHandle, CHANGE_INST, 112, 0);

    //Midi_SendShortMsg(m_DevHandle, CHANGE_INST, 117, 0); //117 : Melodic Drum -> ������.
    //Midi_SendShortMsg(m_DevHandle, CHANGE_INST, 118, 0); //118 : Synth Drum -> ű���� ����.
    //��� : ���׾ ũ���õ� ���� ű�� �ִ�. ű��. ��û ������. (�̰� Midi???) �׳� ���� ����� ����.


    DrumDraw();



    while (1) {
        if (mode == 0) { //���� ���
            if (_kbhit() == 1)if (_getch() == 27) MusicProduct(); // esc �������� ����
            else if (GetKeyState(VK_RIGHT) < 0)
            {
                if (EditX < 63) {
                    EditX++;
                    system("cls");
                    DrumDraw();
                    Sleep(30);
                }
            }
            else if (GetKeyState(VK_LEFT) < 0)
            {
                if (EditX > 0) {
                    EditX--;
                    system("cls");
                    DrumDraw();
                    Sleep(30);
                }
            }
            else if (GetKeyState(VK_DOWN) < 0)
            {
                if (EditY < 3) {
                    EditY++;
                    system("cls");
                    DrumDraw();
                    Sleep(80);
                }
            }
            else if (GetKeyState(VK_UP) < 0)
            {
                if (EditY > 0) {
                    EditY--;
                    system("cls");
                    DrumDraw();
                    Sleep(80);
                }
            }
            else if (GetKeyState(VK_RETURN) < 0)
            {
                if (DrumLoop[EditX][EditY] == 0) DrumLoop[EditX][EditY] = 1;
                else DrumLoop[EditX][EditY] = 0;

                system("cls");
                DrumDraw();
                Sleep(30);
            }
            else if (GetKeyState(VK_SPACE) < 0)
            {
                mode = 1;
                system("cls");
                DrumDraw();
            }
        }
        else { //���� ���
            if (_kbhit() == 1)if (_getch() == 27) MusicProduct();
            else if (GetKeyState(VK_RETURN) < 0)
            {
                for (MusicTime = 0;; MusicTime++) {
                    if (MusicTime == 64) MusicTime = 0;
                    system("cls");
                    DrumDraw();
                    Sleep(Speed);

                    /* MUST BE CHECKED!!!!*/
                    if (DrumLoop[MusicTime][0] == 1) Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + 0), 127);
                    if (DrumLoop[MusicTime][1] == 1) Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + 0), 127);
                    if (DrumLoop[MusicTime][2] == 1) Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + 0), 127);
                    if (DrumLoop[MusicTime][3] == 1) Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + 0), 127);

                    //Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + X), 127); ����..
                    //X�� 1 -> �ѼҸ�..?
                    //X�� 6,7,8,9 -> �ѼҸ� �Ҹ��� ���� Ŀ���µ�?

                    //�˰��ϱ� �ǱⰡ 117�� �ƴ϶� 127�̾���???
                    //...

                    if (_kbhit() == 1)if (_getch() == 27) {
                        mode = 0;
                        break;
                    }

                }


            }
            else if (GetKeyState(VK_SPACE) < 0)
            {
                Midi_Close(m_DevHandle); // �Ҹ����� �� �� ���� ����
                mode = 0;
                system("cls");
                DrumDraw();
            }
        }
    }
}
void DrumDraw()
{
    /*�⺻ ���*/
    gotoxy(0, 0);
    printf("\n");
    printf("BEATMAKER|  1               2               3               4               5               6               7               8\n");
    printf("___________________________________________________________________________________________________________________________________________\n");
    printf("            1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8\n\n");
    printf("KICK     | ");
    for (int i = 0; i < 64; i++) {
        if (DrumLoop[i][0] == 0) printf("��");
        else printf("��");
    }
    printf("\n\n");
    printf("SNARE    | ");
    for (int i = 0; i < 64; i++) {
        if (DrumLoop[i][1] == 0) printf("��");
        else printf("��");
    }
    printf("\n\n");
    printf("HI-HAT   | ");
    for (int i = 0; i < 64; i++) {
        if (DrumLoop[i][2] == 0) printf("��");
        else printf("��");
    }
    printf("\n\n");
    printf("CRASH    | ");
    for (int i = 0; i < 64; i++) {
        if (DrumLoop[i][3] == 0) printf("��");
        else printf("��");
    }
    printf("\n\n\n");
    if (mode == 0) printf("���� ��� : ���� ���� ���\n\n");
    else printf("���� ��� : ���� ���� ���\n\n");
    printf("[SPACE]�� ���� ���� / ���� ���� ��� ��ȯ\n\n");

    if (mode == 0) printf("ȭ��ǥ�� ĭ�� ������ ��, [ENTER]�� ��Ʈ�� �߰��� �� �ֽ��ϴ�.\n\n");
    else printf("[ENTER]�� ���� ������ �����غ�����!\n\n");

    printf("[ESC] : ����");

    /*ȭ��ǥ ���*/
    if (mode == 0) {
        gotoxy(11 + 2*EditX, 12); printf("��");
        gotoxy(139, 5 + 2 * EditY); printf("<");
    }
    else {
        gotoxy(11 + 2 * MusicTime, 12); printf("��");
    }
}

void PianoDraw()
{
    /*�⺻ ���*/
    gotoxy(0, 0);
    printf("\n");
    printf("PIANO    |  1               2               3               4               5               6               7               8\n");
    printf("___________________________________________________________________________________________________________________________________________\n");
    printf("            1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8\n\n");

    printf("B        | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][0] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("A#       | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][1] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("A        | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][2] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("G#       | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][3] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("G        | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][4] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("F#       | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][5] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("F        | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][6] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("E        | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][7] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("D#       | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][8] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("D        | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][9] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("C#       | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][10] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("C        | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][11] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("B        | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][12] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("A#       | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][13] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("A        | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][14] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("G#       | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][15] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("G        | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][16] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("F#       | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][17] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("F        | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][18] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("E        | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][19] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("D#       | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][20] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("D        | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][21] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("C#       | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][22] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("C        | ");
    for (int i = 0; i < 64; i++) {
        if (PianoLoop[i][23] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    
    
    printf("\n\n\n");
    if (mode == 0) printf("���� ��� : ���� ���� ���\n\n");
    else printf("���� ��� : ���� ���� ���\n\n");
    printf("[SPACE]�� ���� ���� / ���� ���� ��� ��ȯ\n\n");

    if (mode == 0) printf("ȭ��ǥ�� ĭ�� ������ ��, [ENTER]�� ��Ʈ�� �߰��� �� �ֽ��ϴ�.\n\n");
    else printf("[ENTER]�� ���� ������ �����غ�����!\n\n");

    printf("[ESC] : ����");

    /*ȭ��ǥ ���*/
    if (mode == 0) {
        gotoxy(11 + 2 * EditX, 29); printf("��");
        gotoxy(139, 5 + EditY); printf("<");
    }
    else {
       // gotoxy(11 + 2 * MusicTime, 29); printf("��");
    }
}
void PianoProduct()
{
    system("cls");
    mode = 0;
    EditX = 0;
    EditY = 0;
    MusicTime = 0;

    PianoDraw();


    while (1) {
        if (mode == 0) { //���� ���
            if (_kbhit() == 1)if (_getch() == 27) MusicProduct(); // esc �������� ����
            else if (GetKeyState(VK_RIGHT) < 0)
            {
                if (EditX < 63) {
                    EditX++;
                    system("cls");
                    PianoDraw();
                    Sleep(30);
                }
            }
            else if (GetKeyState(VK_LEFT) < 0)
            {
                if (EditX > 0) {
                    EditX--;
                    system("cls");
                    PianoDraw();
                    Sleep(30);
                }
            }
            else if (GetKeyState(VK_DOWN) < 0)
            {
                if (EditY < 23) {
                    EditY++;
                    system("cls");
                    PianoDraw();
                    Sleep(80);
                }
            }
            else if (GetKeyState(VK_UP) < 0)
            {
                if (EditY > 0) {
                    EditY--;
                    system("cls");
                    PianoDraw();
                    Sleep(80);
                }
            }
            else if (GetKeyState(VK_RETURN) < 0)
            {
                if (PianoLoop[EditX][EditY] == 0) PianoLoop[EditX][EditY] = 1;
                else PianoLoop[EditX][EditY] = 0;

                system("cls");
                PianoDraw();
                Sleep(30);
            }
            else if (GetKeyState(VK_SPACE) < 0)
            {
                mode = 1;
                system("cls");
                PianoDraw();
            }
        }
        else { //���� ���
            if (_kbhit() == 1)if (_getch() == 27) MusicProduct(); // esc �������� ����
            else if (GetKeyState(VK_RETURN) < 0)
            {
                mode = 1;

                int cnt = 0;
                int LoopT = 0;
                /* Loop�� Note�� �ٲٱ� */

                for (int i = 0; LoopT < 64; LoopT++) {
                    

                    for (int j = 0; j < 24; j++) {
                        if (PianoLoop[LoopT][j]==1) {
                            if (cnt > 0) {
                                Pianonote[i - 1] += 200;
                            }
                            Pianonote[i] = 25 - j;
                            cnt++;
                            i++;
                        }
                    }

                    if (cnt == 0) {
                        Pianonote[i] = 500;
                        i++;
                    }
                    else {
                        cnt = 0;
                    }

                    if (LoopT == 63) Pianonote[i] = 100;
                }
                /*
                500�� �ݹ� ��ǥ, 0~23�� �� ǥ�� (23 : C ~ 0 : B)
                200 ������ ���� ����ġ��
                100�� ������
                */

                Midi_AllChannelSoundOff(m_DevHandle);
                Midi_SendShortMsg(m_DevHandle, 0xB0, 7, 127);


                Midi_SendShortMsg(m_DevHandle, CHANGE_INST, 0, 0); // 0 : Grand Piano


                MusicTime = 0;

                
                while (mode != 0)
                {
                    PianoPlay();
                    if (MusicTime >= 64) MusicTime = 0;

                    if (GetKeyState(VK_RETURN) < 0) {
                        Midi_AllChannelSoundOff(m_DevHandle); // �ܷ��ϴ� ���� ��� ����
                        Midi_Close(m_DevHandle); // �Ҹ����� �� �� ���� ����
                        mode = 0;
                        system("cls");
                        PianoDraw();
                    }
                }
                
                Sleep(Speed * 2);
            }
            else if (GetKeyState(VK_SPACE) < 0)
            {
                Midi_AllChannelSoundOff(m_DevHandle); // �ܷ��ϴ� ���� ��� ����
                mode = 0;
                system("cls");
                PianoDraw();
            }
        }
    }
}
void PianoPlay()
{
    if (Pianonote[MusicTime] == 0) // ��ǥ ǥ��
    {
        Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Pianonote[MusicTime] + 100), Volume);//30+i
        Sleep(Speed * 2);
        MusicTime++;
    }
    else if (Pianonote[MusicTime] >= 200 && Pianonote[MusicTime] <= 300) // ���ÿ� �ľߵɶ�
    {
        Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Pianonote[MusicTime] - 200 + 10), Volume);
        MusicTime++;
    }
    else if (Pianonote[MusicTime] > 300 && Pianonote[MusicTime] <= 400) // �̾ �ٷ� �ľߵɶ�1 (���ڹ���)
    {
        Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Pianonote[MusicTime] - 300 + 22), Volume);
        Sleep(30);
        MusicTime++;
    }
    else if (Pianonote[MusicTime] > 3300 && Pianonote[MusicTime] <= 3400) // �̾ �ٷ� �ľߵɶ�2 (���ڹ���)
    {
        Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Pianonote[MusicTime] - 3300 + 22), Volume);
        Sleep(Speed * 2 - 30);
        MusicTime++;
    }
    else if (Pianonote[MusicTime] > 400 && Pianonote[MusicTime] <= 500) // 1/2���� ¥�� ���ö� 
    { //500�� �ݹ� ��ǥ
        Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Pianonote[MusicTime] - 400 + 10), Volume);
        Sleep(Speed);
        MusicTime++;
    }
    else
    {
        Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Pianonote[MusicTime] + 10), Volume); // ����
        Sleep(Speed * 2);
        MusicTime++;
    }

    if (_kbhit() == 1)if (_getch() == 27) {
        mode = 0;
    }
}

void SynthDraw()
{
    /*�⺻ ���*/
    gotoxy(0, 0);
    printf("\n");
    printf("SYNTH    |  1               2               3               4               5               6               7               8\n");
    printf("___________________________________________________________________________________________________________________________________________\n");
    printf("            1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8\n\n");

    printf("B        | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][0] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("A#       | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][1] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("A        | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][2] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("G#       | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][3] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("G        | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][4] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("F#       | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][5] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("F        | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][6] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("E        | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][7] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("D#       | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][8] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("D        | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][9] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("C#       | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][10] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("C        | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][11] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("B        | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][12] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("A#       | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][13] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("A        | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][14] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("G#       | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][15] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("G        | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][16] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("F#       | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][17] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("F        | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][18] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("E        | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][19] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("D#       | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][20] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("D        | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][21] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("C#       | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][22] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("C        | ");
    for (int i = 0; i < 64; i++) {
        if (SynthLoop[i][23] == 0) printf("��");
        else printf("��");
    }
    printf("\n");


    printf("\n\n\n");
    if (mode == 0) printf("���� ��� : ���� ���� ���\n\n");
    else printf("���� ��� : ���� ���� ���\n\n");
    printf("[SPACE]�� ���� ���� / ���� ���� ��� ��ȯ\n\n");

    if (mode == 0) printf("ȭ��ǥ�� ĭ�� ������ ��, [ENTER]�� ��Ʈ�� �߰��� �� �ֽ��ϴ�.\n\n");
    else printf("[ENTER]�� ���� ������ �����غ�����!\n\n");

    printf("[ESC] : ����");

    /*ȭ��ǥ ���*/
    if (mode == 0) {
        gotoxy(11 + 2 * EditX, 29); printf("��");
        gotoxy(139, 5 + EditY); printf("<");
    }
    else {
        // gotoxy(11 + 2 * MusicTime, 29); printf("��");
    }
}
void SynthProduct()
{
    system("cls");
    mode = 0;
    EditX = 0;
    EditY = 0;
    MusicTime = 0;

    SynthDraw();


    while (1) {
        if (mode == 0) { //���� ���
            if (_kbhit() == 1)if (_getch() == 27) MusicProduct(); // esc �������� ����
            else if (GetKeyState(VK_RIGHT) < 0)
            {
                if (EditX < 63) {
                    EditX++;
                    system("cls");
                    SynthDraw();
                    Sleep(30);
                }
            }
            else if (GetKeyState(VK_LEFT) < 0)
            {
                if (EditX > 0) {
                    EditX--;
                    system("cls");
                    SynthDraw();
                    Sleep(30);
                }
            }
            else if (GetKeyState(VK_DOWN) < 0)
            {
                if (EditY < 23) {
                    EditY++;
                    system("cls");
                    SynthDraw();
                    Sleep(80);
                }
            }
            else if (GetKeyState(VK_UP) < 0)
            {
                if (EditY > 0) {
                    EditY--;
                    system("cls");
                    SynthDraw();
                    Sleep(80);
                }
            }
            else if (GetKeyState(VK_RETURN) < 0)
            {
                if (SynthLoop[EditX][EditY] == 0) SynthLoop[EditX][EditY] = 1;
                else SynthLoop[EditX][EditY] = 0;

                system("cls");
                SynthDraw();
                Sleep(30);
            }
            else if (GetKeyState(VK_SPACE) < 0)
            {
                mode = 1;
                system("cls");
                SynthDraw();
            }
        }
        else { //���� ���
            if (_kbhit() == 1)if (_getch() == 27) MusicProduct(); // esc �������� ����
            else if (GetKeyState(VK_RETURN) < 0)
            {
                mode = 1;

                int cnt = 0;
                int LoopT = 0;
                /* Loop�� Note�� �ٲٱ� */

                for (int i = 0; LoopT < 64; LoopT++) {


                    for (int j = 0; j < 24; j++) {
                        if (SynthLoop[LoopT][j] == 1) {
                            if (cnt > 0) {
                                Synthnote[i - 1] += 200;
                            }
                            Synthnote[i] = 25 - j;
                            cnt++;
                            i++;
                        }
                    }

                    if (cnt == 0) {
                        Synthnote[i] = 500;
                        i++;
                    }
                    else {
                        cnt = 0;
                    }

                    if (LoopT == 63) Synthnote[i] = 100;
                }
                /*
                500�� �ݹ� ��ǥ, 0~23�� �� ǥ�� (23 : C ~ 0 : B)
                200 ������ ���� ����ġ��
                100�� ������
                */

                Midi_AllChannelSoundOff(m_DevHandle);
                Midi_SendShortMsg(m_DevHandle, 0xB0, 7, 127);

                Midi_SendShortMsg(m_DevHandle, CHANGE_INST, synthInst+81, 0); // 81 : square wave synth

                MusicTime = 0;


                while (mode != 0)
                {
                    SynthPlay();
                    if (MusicTime >= 64) MusicTime = 0;
                    
                    if (GetKeyState(VK_SPACE) < 0)
                    {
                        Midi_AllChannelSoundOff(m_DevHandle); // �ܷ��ϴ� ���� ��� ����
                        Midi_Close(m_DevHandle); // �Ҹ����� �� �� ���� ����
                        mode = 0;
                        system("cls");
                        SynthDraw();
                    }
                }

                Sleep(Speed * 2);
            }
            else if (GetKeyState(VK_SPACE) < 0)
            {
                Midi_AllChannelSoundOff(m_DevHandle); // �ܷ��ϴ� ���� ��� ����
                mode = 0;
                system("cls");
                SynthDraw();
            }
        }
    }
}
void SynthPlay()
{
    Midi_AllChannelSoundOff(m_DevHandle); // �ܷ��ϴ� ���� ��� ����
    
    if (Synthnote[MusicTime] == 0) // ��ǥ ǥ��
    {
        Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Synthnote[MusicTime] + 100), Volume);//30+i
        Sleep(Speed * 2);
        MusicTime++;
    }
    else if (Synthnote[MusicTime] >= 200 && Synthnote[MusicTime] <= 300) // ���ÿ� �ľߵɶ�
    {
        Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Synthnote[MusicTime] - 200 + 10), Volume);
        MusicTime++;
    }
    else if (Synthnote[MusicTime] > 300 && Synthnote[MusicTime] <= 400) // �̾ �ٷ� �ľߵɶ�1 (���ڹ���)
    {
        Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Synthnote[MusicTime] - 300 + 22), Volume);
        Sleep(30);
        MusicTime++;
    }
    else if (Synthnote[MusicTime] > 3300 && Synthnote[MusicTime] <= 3400) // �̾ �ٷ� �ľߵɶ�2 (���ڹ���)
    {
        Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Synthnote[MusicTime] - 3300 + 22), Volume);
        Sleep(Speed * 2 - 30);
        MusicTime++;
    }
    else if (Synthnote[MusicTime] > 400 && Synthnote[MusicTime] <= 500) // 1/2���� ¥�� ���ö� 
    { //500�� �ݹ� ��ǥ
        Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Synthnote[MusicTime] - 400 + 10), Volume);
        Sleep(Speed);
        MusicTime++;
    }
    else
    {
        Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Synthnote[MusicTime] + 10), Volume); // ����
        Sleep(Speed * 2);
        MusicTime++;
    }

    if (_kbhit() == 1)if (_getch() == 27) {
        mode = 0;
    }
}

void BassDraw()
{
    /*�⺻ ���*/
    gotoxy(0, 0);
    printf("\n");
    printf("BASS     |  1               2               3               4               5               6               7               8\n");
    printf("___________________________________________________________________________________________________________________________________________\n");
    printf("            1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8\n\n");

    printf("B        | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][0] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("A#       | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][1] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("A        | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][2] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("G#       | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][3] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("G        | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][4] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("F#       | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][5] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("F        | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][6] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("E        | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][7] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("D#       | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][8] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("D        | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][9] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("C#       | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][10] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("C        | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][11] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("B        | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][12] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("A#       | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][13] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("A        | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][14] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("G#       | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][15] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("G        | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][16] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("F#       | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][17] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("F        | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][18] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("E        | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][19] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("D#       | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][20] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("D        | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][21] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("C#       | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][22] == 0) printf("��");
        else printf("��");
    }
    printf("\n");
    printf("C        | ");
    for (int i = 0; i < 64; i++) {
        if (BassLoop[i][23] == 0) printf("��");
        else printf("��");
    }
    printf("\n");


    printf("\n\n\n");
    if (mode == 0) printf("���� ��� : ���� ���� ���\n\n");
    else printf("���� ��� : ���� ���� ���\n\n");
    printf("[SPACE]�� ���� ���� / ���� ���� ��� ��ȯ\n\n");

    if (mode == 0) printf("ȭ��ǥ�� ĭ�� ������ ��, [ENTER]�� ��Ʈ�� �߰��� �� �ֽ��ϴ�.\n\n");
    else printf("[ENTER]�� ���� ������ �����غ�����!\n\n");

    printf("[ESC] : ����");

    /*ȭ��ǥ ���*/
    if (mode == 0) {
        gotoxy(11 + 2 * EditX, 29); printf("��");
        gotoxy(139, 5 + EditY); printf("<");
    }
    else {
        // gotoxy(11 + 2 * MusicTime, 29); printf("��");
    }
}
void BassProduct()
{
    system("cls");
    mode = 0;
    EditX = 0;
    EditY = 0;
    MusicTime = 0;

    BassDraw();


    while (1) {
        if (mode == 0) { //���� ���
            if (_kbhit() == 1)if (_getch() == 27) MusicProduct(); // esc �������� ����
            else if (GetKeyState(VK_RIGHT) < 0)
            {
                if (EditX < 63) {
                    EditX++;
                    system("cls");
                    BassDraw();
                    Sleep(30);
                }
            }
            else if (GetKeyState(VK_LEFT) < 0)
            {
                if (EditX > 0) {
                    EditX--;
                    system("cls");
                    BassDraw();
                    Sleep(30);
                }
            }
            else if (GetKeyState(VK_DOWN) < 0)
            {
                if (EditY < 23) {
                    EditY++;
                    system("cls");
                    BassDraw();
                    Sleep(80);
                }
            }
            else if (GetKeyState(VK_UP) < 0)
            {
                if (EditY > 0) {
                    EditY--;
                    system("cls");
                    BassDraw();
                    Sleep(80);
                }
            }
            else if (GetKeyState(VK_RETURN) < 0)
            {
                if (BassLoop[EditX][EditY] == 0) BassLoop[EditX][EditY] = 1;
                else BassLoop[EditX][EditY] = 0;

                system("cls");
                BassDraw();
                Sleep(30);
            }
            else if (GetKeyState(VK_SPACE) < 0)
            {
                mode = 1;
                system("cls");
                BassDraw();
            }
        }
        else { //���� ���
            if (_kbhit() == 1)if (_getch() == 27) MusicProduct(); // esc �������� ����
            else if (GetKeyState(VK_RETURN) < 0)
            {
                mode = 1;

                int cnt = 0;
                int LoopT = 0;
                /* Loop�� Note�� �ٲٱ� */

                for (int i = 0; LoopT < 64; LoopT++) {


                    for (int j = 0; j < 24; j++) {
                        if (BassLoop[LoopT][j] == 1) {
                            if (cnt > 0) {
                                Bassnote[i - 1] += 200;
                            }
                            Bassnote[i] = 25 - j;
                            cnt++;
                            i++;
                        }
                    }

                    if (cnt == 0) {
                        Bassnote[i] = 500;
                        i++;
                    }
                    else {
                        cnt = 0;
                    }

                    if (LoopT == 63) Bassnote[i] = 100;
                }
                /*
                500�� �ݹ� ��ǥ, 0~23�� �� ǥ�� (23 : C ~ 0 : B)
                200 ������ ���� ����ġ��
                100�� ������
                */

                Midi_AllChannelSoundOff(m_DevHandle);
                Midi_SendShortMsg(m_DevHandle, 0xB0, 7, 127);

                Midi_SendShortMsg(m_DevHandle, CHANGE_INST, BassInst + 33, 0); // 33 : Acustic Bass

                MusicTime = 0;

                while (mode != 0)
                {
                    BassPlay();
                    if (MusicTime >= 64) MusicTime = 0;
                }

                Sleep(Speed * 2);
            }
            else if (GetKeyState(VK_SPACE) < 0)
            {
                Midi_AllChannelSoundOff(m_DevHandle); // �ܷ��ϴ� ���� ��� ����
                mode = 0;
                system("cls");
                BassDraw();
            }
        }
    }
}
void BassPlay()
{
    Midi_AllChannelSoundOff(m_DevHandle); // �ܷ��ϴ� ���� ��� ����
    
    if (Bassnote[MusicTime] == 0) // ��ǥ ǥ��
    {
        Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Bassnote[MusicTime] + 100), Volume);//30+i
        Sleep(Speed * 2);
        MusicTime++;
    }
    else if (Bassnote[MusicTime] >= 200 && Bassnote[MusicTime] <= 300) // ���ÿ� �ľߵɶ�
    {
        Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Bassnote[MusicTime] - 200 - 2), Volume);
        MusicTime++;
    }
    else if (Bassnote[MusicTime] > 300 && Bassnote[MusicTime] <= 400) // �̾ �ٷ� �ľߵɶ�1 (���ڹ���)
    {
        Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Bassnote[MusicTime] - 300 + 22), Volume);
        Sleep(30);
        MusicTime++;
    }
    else if (Bassnote[MusicTime] > 3300 && Bassnote[MusicTime] <= 3400) // �̾ �ٷ� �ľߵɶ�2 (���ڹ���)
    {
        Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Bassnote[MusicTime] - 3300 + 22), Volume);
        Sleep(Speed * 2 - 30);
        MusicTime++;
    }
    else if (Bassnote[MusicTime] > 400 && Bassnote[MusicTime] <= 500) // 1/2���� ¥�� ���ö� 
    { //500�� �ݹ� ��ǥ
        Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Bassnote[MusicTime] - 400 - 2), Volume);
        Sleep(Speed);
        MusicTime++;
    }
    else
    {
        Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + Bassnote[MusicTime] - 2), Volume); // ����
        Sleep(Speed * 2);
        MusicTime++;
    }

    if (_kbhit() == 1)if (_getch() == 27) {
        mode = 0;
    }
}