#pragma once
#include<windows.h>
#include"player.h"
class Game {
public:
	static void startGame2();
	static void gameOver2(HANDLE hOut, Player player1, Player player2);
	static void gamePause(HANDLE hOut);
};
