/*===========================
该文件定义了玩家类，涉及玩家的属性和操作
由于只有玩家正在下落中的方块能够移动和变形
所以将方块的移动和变形的函数声明在玩家类
这样做方便针对玩家进行方块操作

关于地图位置：
玩家有一个mapX属性，表示地图位置
在双人模式中，两名玩家有不同的地图
mapX方便打印方块和地图时将光标移动到不同位置
单人模式时mapX=0
双人模式时玩家1的mapX=0,玩家2的mapX=50
因为玩家1的地图向右平移50个字符就会和玩家2的地图重合
=============================*/
#pragma once
#include<windows.h>
#include<string>
#include"block.h"
using namespace std;
class Player {
public:
	Player();//构造函数
	void setName(string n);//设置玩家姓名
	void setScore(int s);//设置分数
	void setMapX(int x);//设置地图位置，玩家1为0，玩家2为50
	string getName();//获取玩家名字
	int getScore();//获取玩家分数
	int eliminateRow(HANDLE hOut);//判断并消行,加分,返回消去的行数
	void addRow(int x);//增加随机的x行
	bool collisionDetection(Block block);//检测方块是否卡墙或超出地图
	void goLeft(HANDLE hOut);//下落中的方块左移
	void goRight(HANDLE hOut);//下落中的方块右移右移
	void transform(HANDLE hOut);//下落中的方块变形
	void goDown(HANDLE hOut,Player &opponent);//加速下落，双人模式使用
	void goDown(HANDLE hOut);//加速下落，单人模式使用
	void buildMap(int x,int y,int shape);//将正在下落的方块固定在地图中
private:
	string name;//玩家名字
	int score;//玩家分数
	int map[25][15];//玩家当前的地图,从(1,1)到(20,10) 数值为1表示有方块,0表示没方块
	int mapX;//地图位置
	Block nextBlock;//下一个方块
	Block nowBlock;//正在下落的方块
	friend class Block;//这三个类为友元类
	friend class Render;
	friend class Game;
};
