#pragma once
#include "Block.h"
#include <vector>

class Figure
{	
	int type, size;
	int shape[4][4];
	int x = 3, y = 0;	
	bool revers = false;
public:	
	std::vector <Block> figure;

	Figure();//конструктор

	bool isTouchGround();//фигура коснулась земли
			
	bool isCrossTop();//фигура пересекла верхнюю границу поля

	bool isTouch(int direction = 0);//фигура коснулась границы поля или другой фигуры

	void leaveOnField();//оставить фигуру на поле

	void stepDown();//сдвинуть фигуру на шаг вниз

	void drop();//опустить фигуру

	void move(int direction);//подвинуть фигуру влево или вправо
	
	void rotate();//повернуть фигуру

	void paint(RenderWindow &win);//отобразить фигуру

private:
	bool notRotate();

	void createFromShape();//создание фигуры из блоков

	void clockWiseRotation();//вращение по часовой стрелке

	void counterClockWiseRotation();//вращение против часовой стрелки
};