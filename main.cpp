/*===========================
该文件为主函数，控制游戏模式的选择
=============================*/
#include<iostream>
#include<time.h>
#include"game.h"
using namespace std;
int main() {
	int mode; //储存游戏模式
	srand((unsigned)time(NULL)); //生成随机数种子
	cout << "欢迎来到我罗斯方块，请选择游戏模式" << endl;
	cout << "输入 1 开始单人模式，输入 2 开始双人模式：";
	cin >> mode;
	if (mode == 1) { //输入1开始单人模式
		Game::startGame1();
	}
	else if (mode == 2) { //输入2开始双人模式
		Game::startGame2();
	}
	else { //输入错误
		cout << "你输错啦!" << endl;
	}
	return 0;
}
