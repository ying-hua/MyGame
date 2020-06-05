#pragma once
#include<string.h>
#include<time.h>
#include"player.h"
#include"block.h"
#include"render.h"
Player::Player() :nextBlock(),nowBlock(){
	name = "PlayerA";
	score = 0;
	memset(map, 0, sizeof(map));
	mapX = 0;
}
void Player::setName(string n) {
	name = n;
}
void Player::setScore(int s) {
	score = s;
}
void Player::setMapX(int x) {
	mapX = x;
}
string Player::getName() {
	return name;
}
int Player::getScore() {
	return score;
}
int Player::eliminateRow() { //从下往上消行
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

void Player::addRow(int x) { //增加x行
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
bool Player::collisionDetection(Block block) {//检测方块是否卡墙或超出地图
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
void Player::goLeft(HANDLE hOut) {
	int x, y, shape,color;
	Block tempBlock;
	x = nowBlock.getX();
	y = nowBlock.getY();
	shape = nowBlock.getShape();
	color = nowBlock.getColor();
	tempBlock = nowBlock;
	tempBlock.setY(y - 1);
	if (!collisionDetection(tempBlock)) { // 不发生碰撞，可以移动
		Render::clearBlock(hOut, stdblock[shape], 2 * y + mapX, x - 1);
		y--;
		nowBlock.setY(y);
		Render::printBlock(hOut, stdblock[shape], 2 * y + mapX, x - 1, color);//可以去掉?
	}
}
void Player::goRight(HANDLE hOut) {
	int x, y, shape, color;
	Block tempBlock;
	x = nowBlock.getX();
	y = nowBlock.getY();
	shape = nowBlock.getShape();
	color = nowBlock.getColor();
	tempBlock = nowBlock;
	tempBlock.setY(y + 1);
	if (!collisionDetection(tempBlock)) { // 不发生碰撞，可以移动
		Render::clearBlock(hOut, stdblock[shape], 2 * y + mapX, x - 1);
		y++;
		nowBlock.setY(y);
		Render::printBlock(hOut, stdblock[shape], 2 * y + mapX, x - 1, color);//去掉？
	}
}
void Player::buildMap(int x,int y,int shape) { //将方块固定在地图中
	for (int i = 0; i < 4; i++) {
		if (x + i < 1)
			continue;
		for (int j = 0; j < 4; j++) {
			if (stdblock[shape][i][j] == 1) {
				map[x + i][y + j] = 1;
			}
		}
	}
}
void Player::goDown(HANDLE hOut,Player opponent) { //下落
	int x, y, shape, color, cnt = 0; //x,y为下落中的方块在地图上的坐标,cnt为消行数
	Block tempBlock;//临时方块
	x = nowBlock.getX();//变量获取数据
	y = nowBlock.getY();
	shape = nowBlock.getShape();
	color = nowBlock.getColor();
	tempBlock = nowBlock;
	Render::clearBlock(hOut, stdblock[shape], 2 * y + mapX, x - 1);//清除当前正在下落的方块
	tempBlock.setX(x + 1);
	if (!collisionDetection(tempBlock)) { // 不发生碰撞，可以移动
		x++;
		nowBlock.setX(x);//更新坐标
		Render::printBlock(hOut, stdblock[shape], 2 * y + mapX, x - 1, color);//去掉？
	}
	else { //无法下落
		buildMap(x,y,shape);//将方块固定在地图中
		cnt = eliminateRow();
		if (cnt!=0) { //可以消行
			opponent.addRow(cnt);
			Render::printMap(hOut, opponent);//更新对手的地图
		}
		Render::printMap(hOut, *this);//更新本玩家的地图
		nowBlock = nextBlock;
		nowBlock.setX(-2);//方块从地图上方落下
		nowBlock.setY(4);
		nextBlock.roundBlock(); //随机生成下一个方块
		x = nowBlock.getX();//变量更新
		y = nowBlock.getY();
		shape = nowBlock.getShape();
		color = nowBlock.getColor();
		Render::printBlock(hOut, stdblock[shape], 2 * y + mapX, x - 1, color); //打印刚落下的方块
	}
}
void Player::transform(HANDLE hOut) {
	int x, y, shape, color; //x,y为下落中的方块在地图上的坐标
	Block tempBlock;//临时方块
	x = nowBlock.getX();//变量获取数据
	y = nowBlock.getY();
	shape = nowBlock.getShape();
	color = nowBlock.getColor();
	tempBlock = nowBlock;
	if (shape == 5)
		return;
	if (shape == 2) {
		tempBlock.setShape(1);
		if (!collisionDetection(tempBlock)) {
			Render::clearBlock(hOut, stdblock[shape], x, y);
			nowBlock.setShape(1);
			return;
		}
		tempBlock.setY(y - 1);
		if (!collisionDetection(tempBlock)) {
			Render::clearBlock(hOut, stdblock[shape], x, y);
			nowBlock.setShape(1);
			nowBlock.setY(y - 1);
			return;
		}
		tempBlock.setY(y + 1);
		if (!collisionDetection(tempBlock)) {
			Render::clearBlock(hOut, stdblock[shape], x, y);
			nowBlock.setShape(1);
			nowBlock.setY(y + 1);
			return;
		}
		tempBlock.setY(y + 2);
		if (!collisionDetection(tempBlock)) {
			Render::clearBlock(hOut, stdblock[shape], x, y);
			nowBlock.setShape(1);
			nowBlock.setY(y + 2);
			return;
		}
	}
	else if (shape % 2 == 1) {
		tempBlock.setShape(shape + 1);
		if (!collisionDetection(tempBlock)) {
			Render::clearBlock(hOut, stdblock[shape], x, y);
			nowBlock.setShape(shape + 1);
			return;
		}
	}
	else if (shape % 4 == 0) {
		tempBlock.setShape(shape - 3);
		if (!collisionDetection(tempBlock)) {
			Render::clearBlock(hOut, stdblock[shape], x, y);
			nowBlock.setShape(shape - 3);
			return;
		}
		tempBlock.setY(y - 1);
		if (!collisionDetection(tempBlock)) {
			Render::clearBlock(hOut, stdblock[shape], x, y);
			nowBlock.setShape(shape - 3);
			nowBlock.setY(y - 1);
			return;
		}
	}
	else {
		int tshape = 0;
		if (shape == 10 || shape == 14 || shape == 18)
			tshape = shape + 1;
		else
			tshape = shape - 1;
		tempBlock.setShape(tshape);
		if (!collisionDetection(tempBlock)) {
			Render::clearBlock(hOut, stdblock[shape], x, y);
			nowBlock.setShape(tshape);
			return;
		}
		tempBlock.setY(y + 1);
		if (!collisionDetection(tempBlock)) {
			Render::clearBlock(hOut, stdblock[shape], x, y);
			nowBlock.setShape(tshape);
			nowBlock.setY(y + 1);
			return;
		}
	}
}
