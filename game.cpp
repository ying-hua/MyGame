/*===========================
该文件实现了游戏类的成员函数
=============================*/
#define BLUE FOREGROUND_BLUE
#define GREEN FOREGROUND_GREEN
#define RED FOREGROUND_RED
#define INTENSITY FOREGROUND_INTENSITY
#include<iostream>
#include<conio.h>
#include"game.h"
#include"render.h"
#include"player.h"
#include"block.h"
using namespace std;
/*===========================
主动退出游戏
玩家按Esc键时调用
进行按键检测
若又按了一次Esc键就退出函数
按下P键继续游戏
=============================*/
void Game::exitGame(HANDLE hOut) {
	char key; //key储存按键
	SetConsoleTextAttribute(hOut, RED | GREEN | BLUE | INTENSITY);
	Render::gotoXY(hOut, 0, 22); //光标移动到指定位置
	cout << "再按一次Esc退出游戏" << endl; //打印文字
	cout << "按下P继续游戏";
	while(1) {
		if (_kbhit()) {
			key = _getch(); //按键检测
			switch (key) {
			case 27:exit(0); //按Esc确认退出
			case 112: //按P继续游戏
				Render::gotoXY(hOut, 0, 22);
				cout << "                   " << endl; //清除文字
				cout << "             ";
				return;
			}
		}
	}
}
/*===========================
单人模式游戏结束
对玩家的地图检测
若第一行有方块则游戏结束
=============================*/
void Game::gameOver1(HANDLE hOut,Player player) {
	char key;
	for (int i = 1; i <= 10; i++) {
		if (player.map[1][i] == 1) { //检测地图第一行
			SetConsoleTextAttribute(hOut, RED | GREEN | BLUE | INTENSITY);
			Render::gotoXY(hOut, 0, 23);
			cout << "游戏结束" << endl;
			cout << "再接再厉哦,退出重来吧";
			exit(0);
		}
	}
}
/*===========================
双人模式游戏结束
对两个玩家的地图分别进行检测
游戏结束后打印玩家获胜画面
=============================*/
void Game::gameOver2(HANDLE hOut, Player player1, Player player2) { 
	char key;
	for (int i = 1; i <= 10; i++) {
		if (player1.map[1][i] == 1) { //若玩家1的地图满了
			Render::printWin(hOut, player2.getName()); //则玩家2获胜
			exit(0);
		}
	}
	for (int i = 1; i <= 10; i++) {
		if (player2.map[1][i] == 1) { //同理
			Render::printWin(hOut, player1.getName());
			exit(0);
		}
	}
}
/*===========================
游戏暂停
游戏中按P键调用
在屏幕下方打印游戏暂停
再按一次P键继续游戏
=============================*/
void Game::gamePause(HANDLE hOut) {
	char key;
	SetConsoleTextAttribute(hOut, RED | GREEN | BLUE | INTENSITY);
	Render::gotoXY(hOut, 0, 22);
	cout << "游戏暂停" << endl;
	cout << "再按一次P继续游戏";
	while (1) {
		if (_kbhit()) {
			key = _getch();
			switch (key) {
			case 27:exitGame(hOut); break;
			case 112:
				Render::gotoXY(hOut, 0, 22);
				cout << "        " << endl;
				cout << "                 ";
				return;
			}
		}
	}
}
/*===========================
双人模式开始游戏
控制整个游戏的进程
先进行一些界面、方块初始化
不断进行按键检测，玩家可以控制正在下落的方块
不断打印方块
每隔一段时间方块自动下落
=============================*/
void Game::startGame2() {
	char key;//储存按键
	int speed = 1200;//控制方块下落速度，speed越小，下落速度越快
	int times = speed; //times初始化，游戏进行中会不断自减，减为0时自动执行一次下落函数
	int shape1, shape2, x1, y1, x2, y2, color1, color2;//两个玩家正在下落的方块的属性
	Player player1, player2; //两个玩家
	Player& p1 = player1, & p2 = player2; //定义引用，下落函数需要使用
	string name1, name2; //两玩家的名字
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //获取输出句柄，渲染时需要传参
	cout << "开始双人模式" << endl; //打印信息，输入姓名
	cout << "请输入玩家1的名字(wasd控制):";
	cin >> name1;
	cout << "请输入玩家2的名字(方向键控制):";
	cin >> name2;
	player1.setName(name1); //以下为各种初始化
	player2.setName(name2);
	player1.setMapX(0);
	player2.setMapX(50);
	player1.nowBlock.setX(-2);
	player1.nowBlock.setY(4);
	player2.nowBlock.setX(-2);
	player2.nowBlock.setY(4);
	Render::initialPrint2(hOut, name1, name2); //初始化界面
	Render::printBlock(hOut, stdblock[player1.nextBlock.getShape()], 30, 6, player1.nextBlock.getColor()); //打印下一个方块
	Render::printBlock(hOut, stdblock[player2.nextBlock.getShape()], 80, 6, player2.nextBlock.getColor());
	while (1) {
		shape1 = player1.nowBlock.getShape(); //以下为各种获取信息
		shape2 = player2.nowBlock.getShape();
		x1 = player1.nowBlock.getX();
		y1 = player1.nowBlock.getY();
		x2 = player2.nowBlock.getX();
		y2 = player2.nowBlock.getY();
		color1 = player1.nowBlock.getColor();
		color2 = player2.nowBlock.getColor();
		gameOver2(hOut, player1, player2); //检测游戏是否结束
		Render::printBlock(hOut, stdblock[shape1], 2 * y1, x1 - 1, color1); //不断打印方块
		Render::printBlock(hOut, stdblock[shape2], 2 * y2 + 50, x2 - 1, color2);
		if (_kbhit()) { //按键检测
			key = _getch(); //获取按键
			switch (key) {
			case 97: //←键
				player1.goLeft(hOut); break;
			case 100://→键
				player1.goRight(hOut); break;
			case 119://↑键
				player1.transform(hOut); break;
			case 115://↓键
				player1.goDown(hOut, p2); break;
			case 75://A键
				player2.goLeft(hOut); break;
			case 77://D键
				player2.goRight(hOut); break;
			case 72://W键
				player2.transform(hOut); break;
			case 80://S键
				player2.goDown(hOut, p1); break;
			case 112://P键
				gamePause(hOut); break;
			case 27://Esc键
				exitGame(hOut);break;
			default:break;
			}
		}
		//Sleep(20); //停顿20毫秒，加上后speed可以调小
		if (--times == 0) { //隔一段时间times会等于0，方块自动下落
			times = speed;
			player1.goDown(hOut, p2);
			player2.goDown(hOut, p1);
		}
	}
}
//单人模式开始游戏，与双人模式类似，有些不同
void Game::startGame1() {
	char key;//储存按键
	int speed = 1500;//控制方块下落速度
	int times = speed;
	int shape, x, y, color;//玩家正在下落的方块的属性
	Player player;
	Player& pl = player;
	string name;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "开始单人模式模式" << endl;
	cout << "请输入您的名字:";
	cin >> name;
	player.setName(name);
	player.setMapX(0);
	player.nowBlock.setX(-2);
	player.nowBlock.setY(4);
	Render::initialPrint1(hOut, name); //初始化界面
	Render::printBlock(hOut, stdblock[player.nextBlock.getShape()], 30, 6, player.nextBlock.getColor()); //打印下一个方块
	while (1) {
		shape = player.nowBlock.getShape();
		x = player.nowBlock.getX();
		y = player.nowBlock.getY();
		color = player.nowBlock.getColor();
		gameOver1(hOut, player);
		Render::printBlock(hOut, stdblock[shape], 2 * y, x - 1, color);
		if (_kbhit()) {
			key = _getch();
			switch (key) { //单人模式用方向键控制
			case 75:
				player.goLeft(hOut); break;
			case 77:
				player.goRight(hOut); break;
			case 72:
				player.transform(hOut); break;
			case 80:
				player.goDown(hOut); break;
			case 112:
				gamePause(hOut); break;
			case 27:
				exitGame(hOut); break;
			default:break;
			}
		}
		//Sleep(20);
		if (--times == 0) {
			times = speed;
			player.goDown(hOut);
		}
	}
}
