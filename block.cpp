/*===========================
该文件实现了方块类的成员函数
=============================*/
#pragma once
#define BLUE FOREGROUND_BLUE
#define GREEN FOREGROUND_GREEN
#define RED FOREGROUND_RED
#define INTENSITY FOREGROUND_INTENSITY
#include<time.h>
#include<stdlib.h>
#include"block.h"
#include"player.h"
//构造函数
Block::Block() {
	posX = 0;
	posY = 0;
	color = 0;
	shape = 0;
}
//复制构造函数
Block::Block(const Block& b2) {
	posX = b2.posX;
	posY = b2.posY;
	color = b2.color;
	shape = b2.shape;
}
//设置方块x坐标
void Block::setX(int x) {
	posX = x;
}
//设置方块y坐标
void Block::setY(int y) {
	posY = y;
}
//设置方块形状
void Block::setShape(int s) {
	shape = s;
}
/*===========================
随机生成方块
先随机方块的类型(7种类型之一)
若该类型的方块有不同变化形状  (如横条和竖条就是一种类型的两种变化形状)
则再随机一种变化形状
一种类型的方块始终对应一种颜色
最后存入方块的shape和color属性
=============================*/
void Block::roundBlock() {
	int random;//随机数
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
//获取方块x坐标
int Block::getX() {
	return posX;
}
//获取方块y坐标
int Block::getY() {
	return posY;
}
//获取方块颜色
int Block::getColor() {
	return color;
}
//获取方块形状
int Block::getShape() {
	return shape;
}
