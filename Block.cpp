#include "Block.h"

Block::Block(int _x, int _y) : x(_x), y(_y)
{
	texture.loadFromFile("images/tiles.png");
}

//отобразить блок
void Block::paint(RenderWindow &win, int colorNum)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(colorNum * BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE));
	sprite.setPosition(x * BLOCK_SIZE, y * BLOCK_SIZE);
	win.draw(sprite);
}