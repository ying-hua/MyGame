#pragma once
#define BLUE FOREGROUND_BLUE
#define GREEN FOREGROUND_GREEN
#define RED FOREGROUND_RED
#define INTENSITY FOREGROUND_INTENSITY
#include<windows.h>
#include<iostream>
#include"render.h"
#include"player.h"
using namespace std;
void Render::gotoXY(HANDLE hOut, int x, int y) { //移动光标
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOut, pos);
}

void Render::initialPrint2(HANDLE hOut){
    SetConsoleTitle("我罗斯方块");
    COORD size = { 160, 40 };
    SetConsoleScreenBufferSize(hOut, size);
    SMALL_RECT rc = { 0, 0, 120, 30 };
    SetConsoleWindowInfo(hOut, true, &rc);
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(hOut, &cursor_info);
    SetConsoleTextAttribute(hOut, RED | GREEN | BLUE);
    gotoXY(hOut, 0, 0);
    for (int i = 0; i < 20; ++i)
    {
        cout << "■                    ■◆                      ◆" << endl;
    }
    gotoXY(hOut, 26, 0);//■◆●○★
    cout << "◆◆◆◆◆◆◆◆◆◆◆";
    gotoXY(hOut, 0, 20);
    cout << "■■■■■■■■■■■■◆◆◆◆◆◆◆◆◆◆◆◆◆";
    gotoXY(hOut, 26, 1);
    cout << "游戏模式：双人";
    gotoXY(hOut, 26, 2);
    cout << "玩    家：";
    gotoXY(hOut, 26, 3);
    cout << "分    数：0";
    gotoXY(hOut, 26, 5);
    cout << "下一方块：";
    gotoXY(hOut, 26, 11);
    cout << "操作方法：";
    gotoXY(hOut, 30, 12);
    cout << "↑：变形 ↓：下落";
    gotoXY(hOut, 30, 13);
    cout << "←：左移 →：右移";
    gotoXY(hOut, 30, 14);
    cout << "P ：开始/暂停";
    gotoXY(hOut, 30, 15);
    cout << "Esc ：退出游戏";
    gotoXY(hOut, 35, 19);
    cout << "By:黄新成";
    for (int i = 0; i < 20; ++i)
    {
        gotoXY(hOut, 50, i);
        cout << "■                    ■◆                      ◆";
    }
    gotoXY(hOut, 76, 0);
    cout << "◆◆◆◆◆◆◆◆◆◆◆";
    gotoXY(hOut, 50, 20);
    cout << "■■■■■■■■■■■■◆◆◆◆◆◆◆◆◆◆◆◆◆";
    gotoXY(hOut, 76, 1);
    cout << "游戏模式：双人";
    gotoXY(hOut, 76, 2);
    cout << "玩    家：";
    gotoXY(hOut, 76, 3);
    cout << "分    数：0";
    gotoXY(hOut, 76, 5);
    cout << "下一方块：";
    gotoXY(hOut, 76, 11);
    cout << "操作方法：";
    gotoXY(hOut, 80, 12);
    cout << "↑：变形 ↓：下落";
    gotoXY(hOut, 80, 13);
    cout << "←：左移 →：右移";
    gotoXY(hOut, 80, 14);
    cout << "P ：开始/暂停";
    gotoXY(hOut, 80, 15);
    cout << "Esc ：退出游戏";
    gotoXY(hOut, 85, 19);
    cout << "By:黄新成";
}
void Render::initialPrint1(HANDLE hOut) { //初始化单人界面
    SetConsoleTitle("我罗斯方块");
    COORD size = { 80, 25 };
    SetConsoleScreenBufferSize(hOut, size);
    SMALL_RECT rc = { 0, 0, 79, 24 };
    SetConsoleWindowInfo(hOut, true, &rc);
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(hOut, &cursor_info);
    SetConsoleTextAttribute(hOut, RED | GREEN | BLUE);
    gotoXY(hOut, 0, 0);
    for (int i = 0; i < 20; ++i)
    {
        cout << "■                    ■◆                      ◆" << endl;
    }
    gotoXY(hOut, 26, 0);
    cout << "◆◆◆◆◆◆◆◆◆◆◆";
    gotoXY(hOut, 0, 20);
    cout << "■■■■■■■■■■■■◆◆◆◆◆◆◆◆◆◆◆◆◆";
    gotoXY(hOut, 26, 1);
    cout << "游戏模式：单人";
    gotoXY(hOut, 26, 2);
    cout << "玩    家：";
    gotoXY(hOut, 26, 3);
    cout << "分    数：0";
    gotoXY(hOut, 26, 5);
    cout << "下一方块：";
    gotoXY(hOut, 26, 11);
    cout << "操作方法：";
    gotoXY(hOut, 30, 12);
    cout << "↑：变形 ↓：下落";
    gotoXY(hOut, 30, 13);
    cout << "←：左移 →：右移";
    gotoXY(hOut, 30, 14);
    cout << "P ：开始/暂停";
    gotoXY(hOut, 30, 15);
    cout << "Esc ：退出游戏";
    gotoXY(hOut, 35, 19);
    cout << "By:黄新成";
}
void Render::printBlock(HANDLE hOut, int block[4][4], int x,int y,int color) { //打印方块 
    SetConsoleTextAttribute(hOut, color);
    for (int i = 0; i < 4; i++) {
        if (y + i < 0)
            continue;
        for (int j = 0; j < 4; j++) {
            if (block[i][j] == 1) {
                Render::gotoXY(hOut, x+2*j, y+i);
                cout << "■";
            }
        }
    }
}
void Render::clearBlock(HANDLE hOut, int block[4][4], int x, int y) { //清除方块
    for (int i = 0; i < 4; i++) {
        if (y + i < 0)
            continue;
        for (int j = 0; j < 4; j++) {
            if (block[i][j] == 1) {
                Render::gotoXY(hOut, x + 2 * j, y + i);
                cout << "  ";
            }
        }
    }
}
void Render::printMap(HANDLE hOut, Player player) { //更新玩家地图
    SetConsoleTextAttribute(hOut, RED|GREEN|BLUE|INTENSITY);
    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= 10; j++) {
            if (player.map[i][j] == 1) {
                gotoXY(hOut, 2 * j + player.mapX, i - 1);
                cout << "■";
            }
            else {
                gotoXY(hOut, 2 * j + player.mapX, i - 1);
                cout << "  ";
            }
        }
    }
}
