#include "MIDI.h"
#include "MusicHeader.h"

/* �Լ� ���� */
void Guide();
void Hub();

int main()
{
    SetConsoleTitle(TEXT("MIDI Project")); //WCHAR_T ������ ��ȯ..
    Hub();
}

void Guide()
{
    system("cls");
    gotoxy(0, 3);
    printf("   ������ : 1403 �輺��\n");
    printf("   �� ������Ʈ�� �ܼ�â�� Ȱ���� MIDI(Musical Instrument Digital Interface) Ȱ���� �������� ����������ϴ�. \n\n");

    printf("   �� �������α׷��� ������� ������ ��� �� ����, ������ ����, �۰��� �� �ִ� ����� ������ �ֽ��ϴ�. \n\n");

    printf("   ** �۲��� Consolas�� ����˴ϴ�!! ** \n\n");

    printf("   > MusicListen �� ���� ������ ���� �� �ֽ��ϴ�. ���� ������ July - My soul �Դϴ�. \n");
    printf("   �� ������Ʈ�� �Ǳ� �ٲٱ�, �ӵ� �ٲٱ�, ȭ�� ����, ���� �ٲٱ� ���� �����մϴ�. \n");
    printf("\n");

    printf("   > MusicPlay �� ���� Ű���带 ���� �ǾƳ븦 �� �� �� �ֽ��ϴ�. \n\n");



    printf("   > SPACE < �� ���� ���� �������� �Ѱ��ּ��� \n\n");
    printf("   ���� ������ : 1/2");

    char c;
    while (1)
    {
        if (_kbhit()) {        //Ű���� �Է� Ȯ�� (true / false)
            c = _getch();
            switch (c) {
            case SPACE:
                goto A;
                break;
            }
        }
    }

A:
    system("cls");

    printf("\n\n   > MusicProduct �� ���� ������ ���� �� �ֽ��ϴ�. ������ �Ǳ⿡ ���� ��Ʈ�� �Է��� �����մϴ�. \n");
    printf("   �ǾƳ�, �ŵ������, ���̽�, �巳�� �����մϴ�. ������� ��Ʈ���� �����Ͽ� ������ �� �ֽ��ϴ�. \n");
    printf("   ���� ������ ���� ������Ʈ ����, �Ǳ� �ٲٱ� ���� ��ɵ� �����غ� �����Դϴ�. \n");
    printf("   4/4���ڸ� �����Ǹ�, 8���� �������� ������ �� �ֽ��ϴ�. (������..) \n");
    printf("   �̴� �ſ� ������ ���� �۾����� �����մϴ�. \n\n");


    printf("   > SPACE < �� ���� ������ �����մϴ�. \n");
    printf("   > Enter < �� ���� ������Ʈ ����� Ȯ���մϴ�. \n\n");
    printf("   ���� ������ : 2/2");

    char d;
    while (1)
    {
        if (_kbhit()) {        //Ű���� �Է� Ȯ�� (true / false)
            d = _getch();
            switch (d) {
            case SPACE:
                goto B;
                break;
            case ENTER:
                system("cls");

                printf(" ������Ʈ ����� �����ϴ�. \n\n\n");
                printf("   > SPACE < �� ���� ������ �����մϴ�. \n");
                
                while (1) {
                    if (_kbhit()) {        //Ű���� �Է� Ȯ�� (true / false)
                        d = _getch();
                        switch (d) {
                        case SPACE:
                            goto B;
                            break;
                        }
                    }
                }
                
            }
        }
    }

B:
    system("cls");
    Hub();
}

void Hub()
{
    if (m_DevHandle != NULL) {
        Midi_AllChannelSoundOff(m_DevHandle); // �ܷ��ϴ� ���� ��� ����
    }
    else {
        m_DevHandle = Midi_Open(0);
        if (m_DevHandle == NULL) exit(1);
    }
    
    
    int n = 0, t = 0;
    cursor(0); // Ŀ�� ����

    intro(); // ùȭ��

    gotoxy(5, 2); printf("MIDI");
    gotoxy(5, 20); printf("��� ����, SPACE�� Ȯ��");

    int selection = 0;
    int c = 0;

    gotoxy(10, 7 + 2 * selection); printf(">");
    gotoxy(12, 7); printf("Music Listen");
    gotoxy(12, 9); printf("Music Play");
    gotoxy(12, 11); printf("Music Product");
    gotoxy(12, 13); printf("Guide");
    gotoxy(12, 15); printf("Exit");

    while (1)
    {
        if (_kbhit()) {        //Ű���� �Է� Ȯ�� (true / false)
            c = _getch();
            switch (c) {
            case UP:
                gotoxy(10, 7 + 2 * selection); printf("  ");
                selection = (--selection + 5) % 5;
                gotoxy(10, 7 + 2 * selection); printf(">");
                break;
            case DOWN:
                gotoxy(10, 7 + 2 * selection); printf("  ");
                selection = (++selection) % 5;
                gotoxy(10, 7 + 2 * selection); printf(">");
                break;
            case SPACE:
                if (selection == 3) Guide();
                if (selection == 4) { system("cls"); exit(0); }

                system("cls");
                //�ε���... (�̰� ��Ʈ�������� ���� ����)
                printf("\n\n\n                                 NOW LOADING...                                       \n\n\n      ");
                for (int i = 0; i < 22; i++) {
                    printf("�� ");
                    Sleep(50);
                }
                Sleep(400);
                system("cls");

                if (selection == 0) MusicListen();
                if (selection == 1) MusicPlay();
                if (selection == 2) MusicProduct();
                break;
            }
        }
    }

}
