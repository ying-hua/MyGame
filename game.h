/*===========================
该文件定义了游戏类，用于控制游戏的进程
定义了开始游戏、结束游戏、暂停游戏等成员函数
成员函数都为静态成员函数
=============================*/
#pragma once
#include<windows.h>
#include"player.h"
class Game {
public:
	static void startGame1(); //开始单人游戏
	static void startGame2(); //开始双人游戏
	static void gameOver1(HANDLE hOut, Player player); //单人模式游戏结束
	static void gameOver2(HANDLE hOut, Player player1, Player player2); //双人模式游戏结束
	static void gamePause(HANDLE hOut); //游戏暂停
	static void exitGame(HANDLE hOut); //主动退出游戏
};
