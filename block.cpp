#pragma once
#define BLUE FOREGROUND_BLUE
#define GREEN FOREGROUND_GREEN
#define RED FOREGROUND_RED
#define INTENSITY FOREGROUND_INTENSITY
#include<time.h>
#include<stdlib.h>
#include"block.h"
#include"player.h"
Block::Block() {
	posX = 0;
	posY = 0;
	color = 0;
	shape = 0;
}
Block::Block(const Block& b2) {
	posX = b2.posX;
	posY = b2.posY;
	color = b2.color;
	shape = b2.shape;
}
void Block::setX(int x) {
	posX = x;
}
void Block::setY(int y) {
	posY = y;
}
void Block::setShape(int s) {
	shape = s;
}
void Block::roundBlock() {
	int random;//随机数
	//srand((unsigned)time(NULL));
	random = rand() % 7;//产生0-6的随机数,随机一种方块
	random = random * 4 + 1;
	switch (random) {//随机方块形状和颜色
		case 1:color = GREEN | INTENSITY; random += rand() % 2; break;//亮绿
		case 5:color = RED | INTENSITY;break;//红
		case 9:color = RED | BLUE | INTENSITY; random += rand() % 4; break;//品红
		case 13:color = RED | GREEN | INTENSITY; random += rand() % 4; break;//黄
		case 17:color = BLUE | GREEN | INTENSITY; random += rand() % 4; break;//青
		case 21:color = BLUE | INTENSITY; random += rand() % 2; break;//蓝
		case 25:color = GREEN; random += rand() % 2; break;//绿
		default:break;
	}
	shape = random;
}
int Block::getX() {
	return posX;
}
int Block::getY() {
	return posY;
}
int Block::getColor() {
	return color;
}
int Block::getShape() {
	return shape;
}
