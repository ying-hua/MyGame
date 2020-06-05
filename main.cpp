#include<iostream>
#include<time.h>
#include"game.h"
using namespace std;
int main() {
	int mode;
	srand((unsigned)time(NULL));
	cout << "欢迎来到我罗斯方块，请选择游戏模式" << endl;
	cout << "输入 1 开始单人模式，输入 2 开始双人模式：";
	cin >> mode;
	if (mode == 1) {
		return 0;
	}
	else if (mode == 2) {
		Game::startGame2();
	}
	else {
		cout << "请重新输入" << endl;
		return 0;
	}
	return 0;
}
