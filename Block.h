#pragma once
#include "TetrisGlobal.h"

class Block
{
	Texture texture;
	Sprite sprite;

public:
	int x, y;	
	Block(int _x, int _y);
	void paint(RenderWindow &win, int colorNum);	
};
