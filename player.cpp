#pragma once
#include<string.h>
#include<time.h>
#include"player.h"
#include"block.h"
Player::Player() :nextBlock(),nowBlock(){
	name = "PlayerA";
	score = 0;
	memset(map, 0, sizeof(map));
}
void Player::setName(string n) {
	name = n;
}
void Player::setScore(int s) {
	score = s;
}
string Player::getName() {
	return name;
}
int Player::getScore() {
	return score;
}
int Player::eliminateRow(HANDLE hOut) { //从下往上消行
	int cnt = 0;
	int flag = 1; //某行全为1则flag=1
	for (int i = 20; i >= 1; ) {
		flag = 1;
		for (int j = 1; j <= 10; j++) { //判断是否满行
			if (map[i][j] == 0) {
				flag = 0;
				break;
			}
		}
		if (flag == 0) //没有满行则判断上一行
			i--;
		else { //满行
			score += 100;
			cnt++;
			for (int k = i-1; k >= 1; k--) { //地图下移
				for (int j = 1; j <= 10; j++) {
					map[k + 1][j] = map[k][j];
				}
			}
		}
	}
	return cnt;
}

void Player::addRow(HANDLE hOut, int x) { //增加x行
	int n, pos[15] = { 0 }; //pos为方块的位置,n为方块个数
	srand((unsigned)time(NULL));
	while(x--){
		n = rand() % 10;
		for (int i = 1; i <= n; i++) { //生成不同的n个位置
			pos[i] = rand() % 10 + 1;
			for (int j = 1; j < i; j++) {
				if (pos[i] == pos[j]) {
					i--;
					break;
				}
			}
		}
		for (int i = 2; i <= 20; i++) { //地图上移
			for (int j = 1; i <= 10; j++) {
				map[i - 1][j] = map[i][j];
			}
		}
		for (int j = 1; j <= 10; j++) { //底层置零
			map[20][j] = 0;
		}
		for (int i = 1; i <= n; i++) { //放置方块
			map[20][pos[i]] = 1;
		}
	}
}
bool Player::collisionDetection(HANDLE hOut, Block block) {//检测方块是否卡墙或超出地图
	int x, y, shape;
	x = block.getX();
	y = block.getY();
	shape = block.getShape();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (stdblock[shape][i][j] == 1 && (x + i > 20 || y + j > 10 || y + j < 1)) {
				return true;
			}
			if (x + i < 1)
				continue;
			if (stdblock[shape][i][j] == 1 && map[x + i][y + j] == 1) {
				return true;
			}
		}
	}
	return false;
}
