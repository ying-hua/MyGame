/*===========================
该文件定义了渲染类，用于控制渲染，即将游戏内容打印在屏幕上
单人模式和双人模式下游戏界面的初始化有所不同
因此分别定义了函数
关于坐标的不同：
渲染类的成员函数需要传入的坐标参数都为方块在屏幕上的坐标
而不是在玩家地图中的坐标
因此该坐标与方块类中的坐标不同
方块坐标需要转换成屏幕上的坐标再传参
=============================*/
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
	static void printMap(HANDLE hOut, Player player);//打印玩家地图
	static void printWin(HANDLE hOut, string name);//双人模式玩家获胜画面
};
