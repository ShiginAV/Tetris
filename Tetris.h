#pragma once
#include "Figure.h"



class Tetris
{
	bool gameOver = false;
	int gameScore = 0;
	int pastScore = 0;
	float timer = 0;
	float delay = 0.6f; //задержка
	void increaseSpeed(); //увеличение скорости
public:
	void run();
	void checkLines();
};