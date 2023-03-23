#include <stdio.h>
#include <Windows.h>
#include "MusicHeader.h"

void gotoxy(int x, int y)      // 좌표 보내기 gotoxy 
{
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
void setcolor(int bgcolor, int color) // 배경,글자색
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bgcolor & 0xf) << 4) | color);
}

void cursor(int n) // 커서 보이기 & 숨기기
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = n;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}


void intro()
{
    int i;

    setcolor(white, black);
    for (i = 0; i < 40; i++)
    {

        printf("                                                                                                                                               ");

    }
    system("mode con: cols=120 lines=40");

}