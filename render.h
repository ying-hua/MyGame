#pragma once
#include<windows.h>
#include<string>
using namespace std;
class Render {
public:
	void initialPrint1(HANDLE hOut);  //初始化单人界面
	void initialPrint2(HANDLE hOut);//初始化双人界面
	void gotoXY(HANDLE hOut, int x, int y);  //移动光标
	void printBlock(HANDLE hOut, int block[4][4], int x, int y,int color);//打印方块
	void clearBlock(HANDLE hOut, int block[4][4], int x, int y);//消除方块
	void printName(HANDLE hOut, string name, int x, int y);//打印玩家名字
	void printScore(HANDLE hOut, int score, int x, int y);//更新分数
};
