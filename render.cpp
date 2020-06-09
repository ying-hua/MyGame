/*===========================
该文件实现了渲染类的成员函数
=============================*/
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
//移动光标，将光标移动到屏幕上的指定位置
void Render::gotoXY(HANDLE hOut, int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOut, pos);
}
/*===========================
双人模式初始化窗口和界面
=============================*/
void Render::initialPrint2(HANDLE hOut,string name1,string name2){
    SetConsoleTitle("我罗斯方块"); //设置窗口标题
    COORD size = { 160, 40 }; //屏幕缓冲区大小
    SetConsoleScreenBufferSize(hOut, size); //设置屏幕缓冲区大小
    SMALL_RECT rc = { 0, 0, 120, 30 }; //控制台窗口大小和显示位置
    SetConsoleWindowInfo(hOut, true, &rc); //设置控制台窗口
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 }; //设置光标信息
    SetConsoleCursorInfo(hOut, &cursor_info); //隐藏光标
    SetConsoleTextAttribute(hOut, RED | GREEN | BLUE); //改变文本颜色为白色
    gotoXY(hOut, 0, 0); //开始初始化游戏界面
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
    cout << name1;
    gotoXY(hOut, 26, 3);
    cout << "分    数：0";
    gotoXY(hOut, 26, 5);
    cout << "下一方块：";
    gotoXY(hOut, 26, 11);
    cout << "操作方法：";
    gotoXY(hOut, 30, 12);
    cout << "W ：变形 S ：下落";
    gotoXY(hOut, 30, 13);
    cout << "A ：左移 D ：右移";
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
    cout << name2;
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
//单人模式初始化界面，与双人模式类似
void Render::initialPrint1(HANDLE hOut,string name) {
    SetConsoleTitle("我罗斯方块");
    COORD size = { 80, 25 }; //单人模式窗口更小
    SetConsoleScreenBufferSize(hOut, size);
    SMALL_RECT rc = { 0, 0, 79, 24 };
    SetConsoleWindowInfo(hOut, true, &rc);
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(hOut, &cursor_info);
    SetConsoleTextAttribute(hOut, RED | GREEN | BLUE);
    gotoXY(hOut, 0, 0); //开始初始化界面
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
    cout << name;
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
/*===========================
打印方块
传入需要打印的方块数组、坐标和颜色
在指定位置打印方块
方块超出屏幕上边的部分不会打印
方块的坐标不是在玩家地图上的坐标，而是在屏幕上的坐标
=============================*/
void Render::printBlock(HANDLE hOut, int block[4][4], int x,int y,int color) {
    SetConsoleTextAttribute(hOut, color); //设置颜色
    for (int i = 0; i < 4; i++) { //开始打印方块
        if (y + i < 0) //忽略超出地图上边的部分
            continue;
        for (int j = 0; j < 4; j++) {
            if (block[i][j] == 1) {
                Render::gotoXY(hOut, x + 2 * j, y + i); //移动光标打印方块
                cout << "■";
            }
        }
    }
}
/*===========================
清除方块
将指定坐标，指定形状的方块从屏幕中删除
与打印方块类似
=============================*/
void Render::clearBlock(HANDLE hOut, int block[4][4], int x, int y) {
    for (int i = 0; i < 4; i++) {
        if (y + i < 0) //超出地图上边的忽略
            continue;
        for (int j = 0; j < 4; j++) {
            if (block[i][j] == 1) {
                Render::gotoXY(hOut, x + 2 * j, y + i);
                cout << "  "; //打印空格相当于删除
            }
        }
    }
}
/*===========================
打印玩家地图
打印指定玩家的地图
双人模式中两玩家地图的位置不同，用mapX的值区分
=============================*/
void Render::printMap(HANDLE hOut, Player player) {
    SetConsoleTextAttribute(hOut, RED | GREEN | BLUE | INTENSITY); //设置颜色为亮白色
    for (int i = 1; i <= 20; i++) { //开始打印地图
        for (int j = 1; j <= 10; j++) {
            if (player.map[i][j] == 1) { //有方块的地方
                gotoXY(hOut, 2 * j + player.mapX, i - 1);
                cout << "■";
            }
            else { //无方块的地方
                gotoXY(hOut, 2 * j + player.mapX, i - 1);
                cout << "  ";
            }
        }
    }
}
//打印玩家分数，在指定位置打印分数
void Render::printScore(HANDLE hOut, int score, int x, int y) {
    gotoXY(hOut, x, y);
    cout << score;
}
/*===========================
打印玩家获胜画面
打印玩家获胜的信息和一个俄罗斯方块奖杯
传入的参数为获胜的玩家
=============================*/
void Render::printWin(HANDLE hOut, string name) {
    SetConsoleTextAttribute(hOut, RED | GREEN | BLUE); //设置颜色为白色
    gotoXY(hOut, 0, 23);
    cout << "游戏结束";
    gotoXY(hOut, 0, 24);
    cout << name << "获胜！";
    gotoXY(hOut, 0, 25);
    cout << "按Esc键退出游戏";
    SetConsoleTextAttribute(hOut, BLUE | INTENSITY); //蓝色
    gotoXY(hOut, 46, 23);
    cout << "■■";
    gotoXY(hOut, 48, 24);
    cout << "■■";
    SetConsoleTextAttribute(hOut, RED | GREEN | INTENSITY); //黄色
    gotoXY(hOut, 42, 25);
    cout << "■    ■    ■";
    gotoXY(hOut, 44, 26);
    cout << "■■■■■";
    gotoXY(hOut, 46, 27);
    cout << "■■■";
    SetConsoleTextAttribute(hOut, RED | INTENSITY); //红色
    gotoXY(hOut, 48, 28);
    cout << "■";
    gotoXY(hOut, 46, 29);
    cout << "■■■";
    SetConsoleTextAttribute(hOut, RED | GREEN | BLUE); //白色
}
