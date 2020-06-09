/*===========================
该文件实现了玩家类的成员函数
=============================*/
#pragma once
#define BLUE FOREGROUND_BLUE
#define GREEN FOREGROUND_GREEN
#define RED FOREGROUND_RED
#define INTENSITY FOREGROUND_INTENSITY
#include<string.h>
#include<time.h>
#include"player.h"
#include"block.h"
#include"render.h"
/*===========================
玩家的构造函数
随机化下一个方块和正在下落的方块
=============================*/
Player::Player() :nextBlock(),nowBlock(){
	name = "Player";
	score = 0;
	memset(map, 0, sizeof(map));
	mapX = 0;
	nextBlock.roundBlock();
	nowBlock.roundBlock();
}
//设置姓名
void Player::setName(string n) {
	name = n;
}
//设置分数
void Player::setScore(int s) {
	score = s;
}
//设置地图位置
void Player::setMapX(int x) {
	mapX = x;
}
//获取姓名
string Player::getName() {
	return name;
}
//获取分数
int Player::getScore() {
	return score;
}
/*===========================
消行函数
满行时对玩家的地图消行,同时更新分数,返回值为消去的行数
消行完成后只是更新玩家的地图数组
打印地图的操作由渲染类完成
=============================*/
int Player::eliminateRow(HANDLE hOut) {
	int cnt = 0;//消行数
	int flag = 1; //某行全满则flag=1
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
	SetConsoleTextAttribute(hOut, RED | GREEN | BLUE);
	Render::printScore(hOut, score, 36 + mapX, 3); //在指定位置打印分数,玩家1在(36,3),玩家2在(86,3)
	return cnt;
}
/*===========================
加行
仅在双人模式使用
某玩家消行时,对手便在底部增加一行
增加的一行不可能是满行，其他情况都有可能
传入的参数x为增加的行数
=============================*/
void Player::addRow(int x) { 
	int n, pos[15] = { 0 }; //pos为方块的位置,n为方块个数
	while(x--){
		n = rand() % 10;//随机方块个数 0~9
		for (int i = 1; i <= n; i++) { //生成不同的n个位置
			pos[i] = rand() % 10 + 1;  //pos[i]的取值为1~10
			for (int j = 1; j < i; j++) { //判断是否重复，执行后保证所有方块的位置不重复
				if (pos[i] == pos[j]) {
					i--;
					break;
				}
			}
		}
		for (int i = 2; i <= 20; i++) { //地图上移
			for (int j = 1; j <= 10; j++) {
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
/*===========================
碰撞检测
用于检测方块是否与其他方块重叠或超出地图范围
传入的参数为需要进行检测的方块，地图为该玩家的地图
方块超出地图上方的部分不会进行判断
重叠或超出地图返回true,否则返回false
要先进行超出地图检测防止出现bug
=============================*/
bool Player::collisionDetection(Block block) {
	int x, y, shape;//储存方块信息
	x = block.getX();//获取方块信息
	y = block.getY();
	shape = block.getShape();
	for (int i = 0; i < 4; i++) { //开始检测
		for (int j = 0; j < 4; j++) {
			if (stdblock[shape][i][j] == 1 && (x + i > 20 || y + j > 10 || y + j < 1)) { //检测是否超出地图左边、右边、下边
				return true;
			}
			if (x + i < 1) //方块超出地图上边的部分跳过检测
				continue;
			if (stdblock[shape][i][j] == 1 && map[x + i][y + j] == 1) { //检测方块是否和地图内的方块重合
				return true;
			}
		}
	}
	return false;
}
/*===========================
方块左移
先进行碰撞检测
若方块能左移就左移，否则跳过
该函数不会打印左移后的方块
=============================*/
void Player::goLeft(HANDLE hOut) {
	int x, y, shape,color; //方块信息
	Block tempBlock; //临时方块
	x = nowBlock.getX(); //获取方块信息
	y = nowBlock.getY();
	shape = nowBlock.getShape();
	color = nowBlock.getColor();
	tempBlock = nowBlock;
	tempBlock.setY(y - 1); //临时方块左移
	if (!collisionDetection(tempBlock)) { // 不发生碰撞，可以移动
		Render::clearBlock(hOut, stdblock[shape], 2 * y + mapX, x - 1); //清除原来的方块
		y--; //将正在下落的方块左移
		nowBlock.setY(y);
	}
}
//方块右移函数，与左移类似
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
	}
}
/*===========================
构建地图
用于将刚沉底的方块固定在地图上
超出地图上边的部分忽略
该函数只会更新玩家的地图数组
不会打印地图
参数x,y为方块在地图中的坐标,shape为方块形状
=============================*/
void Player::buildMap(int x,int y,int shape) {
	for (int i = 0; i < 4; i++) {
		if (x + i < 1) //超出地图上边的忽略
			continue;
		for (int j = 0; j < 4; j++) {
			if (stdblock[shape][i][j] == 1) {
				map[x + i][y + j] = 1;
			}
		}
	}
}
/*===========================
双人模式方块下落
先进行碰撞检测
若方块可以下落则下落
不能下落时执行以下操作：
将方块固定在地图中,
进行消行判断，成功则对手进行加行操作,
打印地图,
新方块开始下落,
随机生成下一个方块;
参数opponent为对手
=============================*/
void Player::goDown(HANDLE hOut,Player &opponent) {
	int x, y, shape, color, cnt = 0; //x,y为下落中的方块在地图上的坐标,cnt为消行数
	Block tempBlock;//临时方块
	x = nowBlock.getX();//变量获取数据
	y = nowBlock.getY();
	shape = nowBlock.getShape();
	color = nowBlock.getColor();
	tempBlock = nowBlock;
	Render::clearBlock(hOut, stdblock[shape], 2 * y + mapX, x - 1);//清除当前正在下落的方块
	tempBlock.setX(x + 1); //临时方块下移
	if (!collisionDetection(tempBlock)) { // 不发生碰撞，可以移动
		x++;
		nowBlock.setX(x);//更新坐标
	}
	else {                  //无法下落
		buildMap(x,y,shape);//将方块固定在地图中
		cnt = eliminateRow(hOut);
		if (cnt != 0) { //可以消行
			opponent.addRow(cnt); //对手加行
			Render::printMap(hOut, opponent);//更新对手的地图
		}
		Render::printMap(hOut, *this);//更新本玩家的地图
		nowBlock = nextBlock;
		nowBlock.setX(-2);//方块从地图上方落下,(-2,4)为地图中心上部位置
		nowBlock.setY(4);
		Render::clearBlock(hOut, stdblock[nextBlock.getShape()], 30 + mapX, 6);//清除下一个方块,(30+mapX,6)为下一个方块在屏幕上的位置
		nextBlock.roundBlock(); //随机生成下一个方块
		x = nowBlock.getX();//变量更新
		y = nowBlock.getY();
		shape = nowBlock.getShape();
		color = nowBlock.getColor();
		Render::printBlock(hOut, stdblock[nextBlock.getShape()], 30 + mapX, 6, nextBlock.getColor());//打印下一个方块
	}
}
/*===========================
方块变形
先进行碰撞检测
若能变形就变形，否则跳过
有些方块靠近地图边缘变形时会超出地图
该函数将会自动将方块左右移动，使方块恰好不会超出地图
左右移动多少格与方块形状有关
因此对不同的方块要进行不同的处理，代码较长
而有些方块可以进行相同处理
因此要对方块特点分类
=============================*/
void Player::transform(HANDLE hOut) {
	int x, y, shape, color; //x,y为下落中的方块在地图上的坐标
	Block tempBlock;//临时方块
	x = nowBlock.getX();//变量获取数据
	y = nowBlock.getY();
	shape = nowBlock.getShape();
	color = nowBlock.getColor();
	tempBlock = nowBlock;
	if (shape == 5) //立方体形方块不会变形
		return;
	if (shape == 2) { //竖条形方块
		tempBlock.setShape(1); //变形为横条形
		if (!collisionDetection(tempBlock)) { //若能够变形
			Render::clearBlock(hOut, stdblock[shape], 2 * y + mapX, x - 1); //就把当前形状的方块清除
			nowBlock.setShape(1); //正在下落的方块变形
			return; //退出函数
		}
		tempBlock.setY(y - 1); //直接变形方块可能卡出地图外，那就试试向左移动一格能不能变形
		if (!collisionDetection(tempBlock)) {
			Render::clearBlock(hOut, stdblock[shape], 2 * y + mapX, x - 1);
			nowBlock.setShape(1);
			nowBlock.setY(y - 1); //自动往左移动一格
			return;
		}
		tempBlock.setY(y + 1); //再试试向右移动一格能不能变形
		if (!collisionDetection(tempBlock)) {
			Render::clearBlock(hOut, stdblock[shape], 2 * y + mapX, x - 1);
			nowBlock.setShape(1);
			nowBlock.setY(y + 1);
			return;
		}
		tempBlock.setY(y + 2); //再试试向右移动两格能不能变形
		if (!collisionDetection(tempBlock)) {
			Render::clearBlock(hOut, stdblock[shape], 2 * y + mapX, x - 1);
			nowBlock.setShape(1);
			nowBlock.setY(y + 2);
			return;
		}
	}
	else if (shape % 2 == 1) { //编号为奇数的方块有共同特点(除了编号为5的立方体形方块)
		tempBlock.setShape(shape + 1); //变形为下一个形状
		if (!collisionDetection(tempBlock)) { //可以直接变形
			Render::clearBlock(hOut, stdblock[shape], 2 * y + mapX, x - 1);
			nowBlock.setShape(shape + 1);
			return;
		}
	}
	else if (shape % 4 == 0) { //编号为4的倍数的方块
		tempBlock.setShape(shape - 3);
		if (!collisionDetection(tempBlock)) {
			Render::clearBlock(hOut, stdblock[shape], 2 * y + mapX, x - 1);
			nowBlock.setShape(shape - 3);
			return;
		}
		tempBlock.setY(y + 1);
		if (!collisionDetection(tempBlock)) {
			Render::clearBlock(hOut, stdblock[shape], 2 * y + mapX, x - 1);
			nowBlock.setShape(shape - 3);
			nowBlock.setY(y + 1);
			return;
		}
	}
	else if (shape == 22 || shape == 26) { //这两种方块的下一个形状为shape-1
		tempBlock.setShape(shape - 1);
		if (!collisionDetection(tempBlock)) {
			Render::clearBlock(hOut, stdblock[shape], 2 * y + mapX, x - 1);
			nowBlock.setShape(shape-1);
			return;
		}
		tempBlock.setY(y + 1);
		if (!collisionDetection(tempBlock)) {
			Render::clearBlock(hOut, stdblock[shape], 2 * y + mapX, x - 1);
			nowBlock.setShape(shape-1);
			nowBlock.setY(y + 1);
			return;
		}
	}
	else { //剩下的方块编号为10,14,18
		tempBlock.setShape(shape + 1);
		if (!collisionDetection(tempBlock)) {
			Render::clearBlock(hOut, stdblock[shape], 2 * y + mapX, x - 1);
			nowBlock.setShape(shape + 1);
			return;
		}
		tempBlock.setY(y + 1);
		if (!collisionDetection(tempBlock)) {
			Render::clearBlock(hOut, stdblock[shape], 2 * y + mapX, x - 1);
			nowBlock.setShape(shape + 1);
			nowBlock.setY(y + 1);
			return;
		}
	}
}
//单人模式方块下落，没有对手，不进行加行操作
void Player::goDown(HANDLE hOut) {
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
	}
	else { //无法下落
		buildMap(x, y, shape);//将方块固定在地图中
		cnt = eliminateRow(hOut); //消行
		Render::printMap(hOut, *this);//更新本玩家的地图
		nowBlock = nextBlock;
		nowBlock.setX(-2);//方块从地图上方落下
		nowBlock.setY(4);
		Render::clearBlock(hOut, stdblock[nextBlock.getShape()], 30 + mapX, 6);//清除下一个方块
		nextBlock.roundBlock(); //随机生成下一个方块
		x = nowBlock.getX();//变量更新
		y = nowBlock.getY();
		shape = nowBlock.getShape();
		color = nowBlock.getColor();
		Render::printBlock(hOut, stdblock[nextBlock.getShape()], 30 + mapX, 6, nextBlock.getColor());//打印下一个方块
	}
}
