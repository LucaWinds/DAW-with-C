#include "MIDI.h"
#include "MusicHeader.h"

/* 함수 선언 */
void Guide();
void Hub();

int main()
{
    SetConsoleTitle(TEXT("MIDI Project")); //WCHAR_T 형으로 변환..
    Hub();
}

void Guide()
{
    system("cls");
    gotoxy(0, 3);
    printf("   만든사람 : 1403 김성현\n");
    printf("   이 프로젝트는 콘솔창을 활용한 MIDI(Musical Instrument Digital Interface) 활용을 목적으로 만들어졌습니다. \n\n");

    printf("   이 응용프로그램은 만들어진 음악을 듣는 것 부터, 음악을 연주, 작곡할 수 있는 기능을 가지고 있습니다. \n\n");

    printf("   ** 글꼴은 Consolas가 권장됩니다!! ** \n\n");

    printf("   > MusicListen 을 통해 음악을 들을 수 있습니다. 사용된 음악은 July - My soul 입니다. \n");
    printf("   이 프로젝트는 악기 바꾸기, 속도 바꾸기, 화음 제거, 음량 바꾸기 등을 지원합니다. \n");
    printf("\n");

    printf("   > MusicPlay 을 통해 키보드를 통해 피아노를 쳐 볼 수 있습니다. \n\n");



    printf("   > SPACE < 를 눌러 다음 페이지로 넘겨주세요 \n\n");
    printf("   현재 페이지 : 1/2");

    char c;
    while (1)
    {
        if (_kbhit()) {        //키보드 입력 확인 (true / false)
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

    printf("\n\n   > MusicProduct 을 통해 음악을 만들어볼 수 있습니다. 각각의 악기에 대한 노트를 입력해 연주합니다. \n");
    printf("   피아노, 신디사이저, 베이스, 드럼을 지원합니다. 만들어진 노트들을 종합하여 연주할 수 있습니다. \n");
    printf("   추후 파일을 통한 프로젝트 저장, 악기 바꾸기 등의 기능도 구현해볼 예정입니다. \n");
    printf("   4/4박자만 지원되며, 8마디 루프만을 제작할 수 있습니다. (힘들어요..) \n");
    printf("   이는 매우 간단한 음악 작업에만 적합합니다. \n\n");


    printf("   > SPACE < 를 눌러 도움말을 종료합니다. \n");
    printf("   > Enter < 를 눌러 업데이트 기록을 확인합니다. \n\n");
    printf("   현재 페이지 : 2/2");

    char d;
    while (1)
    {
        if (_kbhit()) {        //키보드 입력 확인 (true / false)
            d = _getch();
            switch (d) {
            case SPACE:
                goto B;
                break;
            case ENTER:
                system("cls");

                printf(" 업데이트 기록이 없습니다. \n\n\n");
                printf("   > SPACE < 를 눌러 도움말을 종료합니다. \n");
                
                while (1) {
                    if (_kbhit()) {        //키보드 입력 확인 (true / false)
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
        Midi_AllChannelSoundOff(m_DevHandle); // 잔류하던 음을 모두 종료
    }
    else {
        m_DevHandle = Midi_Open(0);
        if (m_DevHandle == NULL) exit(1);
    }
    
    
    int n = 0, t = 0;
    cursor(0); // 커서 숨김

    intro(); // 첫화면

    gotoxy(5, 2); printf("MIDI");
    gotoxy(5, 20); printf("↑↓ 선택, SPACE로 확정");

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
        if (_kbhit()) {        //키보드 입력 확인 (true / false)
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
                //로딩중... (이거 테트리스에서 쓴거 맞음)
                printf("\n\n\n                                 NOW LOADING...                                       \n\n\n      ");
                for (int i = 0; i < 22; i++) {
                    printf("■ ");
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
