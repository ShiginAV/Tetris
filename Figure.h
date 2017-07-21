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

	Figure();//�����������

	bool isTouchGround();//������ ��������� �����
			
	bool isCrossTop();//������ ��������� ������� ������� ����

	bool isTouch(int direction = 0);//������ ��������� ������� ���� ��� ������ ������

	void leaveOnField();//�������� ������ �� ����

	void stepDown();//�������� ������ �� ��� ����

	void drop();//�������� ������

	void move(int direction);//��������� ������ ����� ��� ������
	
	void rotate();//��������� ������

	void paint(RenderWindow &win);//���������� ������

private:
	bool notRotate();

	void createFromShape();//�������� ������ �� ������

	void clockWiseRotation();//�������� �� ������� �������

	void counterClockWiseRotation();//�������� ������ ������� �������
};