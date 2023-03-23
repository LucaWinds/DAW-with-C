#pragma once

//색 정의
#define black            0
#define dark_green        2    //     BLACK,            0 : 까망                  DARK_BLUE,      1 : 어두운 파랑 
#define dark_red        4
#define dark_yellow        6    //     DARK_GREEN,    2 : 어두운 초록          DARK_SKY_BLUE,  3 : 어두운 하늘
#define dark_gray        8 
#define dark_blue        1    //     DARK_RED,      4 : 어두운 빨강          DARK_VIOLET,    5 : 어두운 보라
#define dark_sky_blue    3
#define dark_violet        5    //     DARK_YELLOW,   6 : 어두운 노랑             GRAY,             7 : 회색 
#define green            10
#define red                12     //     DARK_GRAY,     8 : 어두운 회색          BLUE,             9 : 파랑 
#define yellow            14     
#define gray            7    //     GREEN,            10 : 초록                  SKY_BLUE,         11 : 하늘 
#define blue            9
#define sky_blue        11    //     RED,            12 : 빨강                 VIOLET,         13 : 보라
#define violet            13
#define white            15    //     YELLOW,        14 : 노랑                  WHITE,             15 : 하양

//키보드 정의
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define ENTER 13
#define ESC 27

//이동 함수
void MusicPlay();
void MusicProduct();
void MusicListen();
void MusicOpen(); //MusicPlay에 저장
void Hub();

//기본적인 함수 모음
void gotoxy(int x, int y);
void setcolor(int bgcolor, int color);
void cursor(int n);
void intro();
