#pragma once
#include<windows.h>
#include<string>
#include"player.h"
using namespace std;
class Render {
public:
	static void initialPrint1(HANDLE hOut,string name);  //初始化单人界面
	static void initialPrint2(HANDLE hOut,string name1,string name2);//初始化双人界面
	static void gotoXY(HANDLE hOut, int x, int y);  //移动光标
	static void printBlock(HANDLE hOut, int block[4][4],int x,int y,int color);//打印方块
	static void clearBlock(HANDLE hOut, int block[4][4],int x,int y);//消除方块
	static void printScore(HANDLE hOut, int score, int x, int y);//更新分数
	static void printMap(HANDLE hOut,Player player);
};
