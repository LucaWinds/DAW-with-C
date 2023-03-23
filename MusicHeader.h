#pragma once

//�� ����
#define black            0
#define dark_green        2    //     BLACK,            0 : ���                  DARK_BLUE,      1 : ��ο� �Ķ� 
#define dark_red        4
#define dark_yellow        6    //     DARK_GREEN,    2 : ��ο� �ʷ�          DARK_SKY_BLUE,  3 : ��ο� �ϴ�
#define dark_gray        8 
#define dark_blue        1    //     DARK_RED,      4 : ��ο� ����          DARK_VIOLET,    5 : ��ο� ����
#define dark_sky_blue    3
#define dark_violet        5    //     DARK_YELLOW,   6 : ��ο� ���             GRAY,             7 : ȸ�� 
#define green            10
#define red                12     //     DARK_GRAY,     8 : ��ο� ȸ��          BLUE,             9 : �Ķ� 
#define yellow            14     
#define gray            7    //     GREEN,            10 : �ʷ�                  SKY_BLUE,         11 : �ϴ� 
#define blue            9
#define sky_blue        11    //     RED,            12 : ����                 VIOLET,         13 : ����
#define violet            13
#define white            15    //     YELLOW,        14 : ���                  WHITE,             15 : �Ͼ�

//Ű���� ����
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define ENTER 13
#define ESC 27

//�̵� �Լ�
void MusicPlay();
void MusicProduct();
void MusicListen();
void MusicOpen(); //MusicPlay�� ����
void Hub();

//�⺻���� �Լ� ����
void gotoxy(int x, int y);
void setcolor(int bgcolor, int color);
void cursor(int n);
void intro();
