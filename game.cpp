#include<iostream>
#include<conio.h>
#include"game.h"
#include"render.h"
#include"player.h"
#include"block.h"
using namespace std;
void Game::gameOver2(HANDLE hOut, Player player1, Player player2) { //未完成
	for (int i = 1; i <= 10; i++) {
		if (player1.map[1][i] == 1) {
			cout << "player1 lose";
		}
	}
	for (int i = 1; i <= 10; i++) {
		if (player2.map[1][i] == 1) {
			cout << "player2 lose";
		}
	}
}
void Game::gamePause(HANDLE hOut) { //未完成
	cout << "pause";
}
void Game::startGame2() {
	char key;//储存按键
	int speed = 50;//控制方块下落速度
	int times = 50;
	int shape1, shape2, x1, y1, x2, y2, color1, color2;//两个玩家正在下落的方块的属性
	Player player1, player2;
	Block tempBlock;
	string name1, name2;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "开始双人模式" << endl;
	cout << "请输入玩家1的名字(wasd控制):";
	cin >> name1;
	cout << "请输入玩家2的名字(方向键控制):";
	cin >> name2;
	player1.setName(name1);
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
		shape1 = player1.nowBlock.getShape();
		shape2 = player2.nowBlock.getShape();
		x1 = player1.nowBlock.getX();
		y1 = player1.nowBlock.getY();
		x2 = player2.nowBlock.getX();
		y2 = player2.nowBlock.getY();
		color1 = player1.nowBlock.getColor();
		color2 = player2.nowBlock.getColor();
		gameOver2(hOut, player1, player2);
		Render::printBlock(hOut, stdblock[shape1], 2 * y1, x1 - 1, color1);
		Render::printBlock(hOut, stdblock[shape2], 2 * y2 + 50, x2 - 1, color2);
		if (_kbhit()) {
			key = _getch();
			switch (key) {
			case 97:
				player1.goLeft(hOut); break;
			case 100:
				player1.goRight(hOut); break;
			case 119:
				player1.transform(hOut); break;
			case 115:
				player1.goDown(hOut, player2); break;
			case 75:
				player2.goLeft(hOut); break;
			case 77:
				player2.goRight(hOut); break;
			case 72:
				player2.transform(hOut); break;
			case 80:
				player2.goDown(hOut, player1); break;
			case 112:
				Game::gamePause(hOut); break;
			case 27://退出游戏
				break;
			default:break;
			}
		}
		Sleep(20);
		if (--times == 0) {
			times = speed;
			player1.goDown(hOut, player2);
			player2.goDown(hOut, player1);
		}
	}
	system("pause");
	return;
}
