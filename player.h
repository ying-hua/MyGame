#pragma once
#include<windows.h>
#include<string>
#include"block.h"
using namespace std;
class Player {
public:
	Player();//构造函数
	void setName(string n);
	void setScore(int s);//设置分数
	void setMapX(int x);//设置地图位置，玩家1为0，玩家2为50
	string getName();//获取玩家名字
	int getScore();//获取玩家分数
	int eliminateRow();//判断并消行,加分,返回消去的行数
	void addRow(int x);//增加随机的x行
	bool collisionDetection(Block block);//检测方块是否卡墙或超出地图
	void goLeft(HANDLE hOut);//左移
	void goRight(HANDLE hOut);//右移
	void transform(HANDLE hOut);//变形
	void goDown(HANDLE hOut,Player opponent);//加速下落
	void buildMap(int x,int y,int shape);//将正在下落的方块固定在地图中
private:
	string name;//玩家名字
	int score;//玩家分数
	int map[25][15];//玩家当前的地图,从(1,1)到(20,10)
	int mapX;//地图位置
	Block nextBlock;//下一个方块
	Block nowBlock;//正在下落的方块
	friend class Block;
	friend class Render;
};
