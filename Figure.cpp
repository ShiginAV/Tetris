#include "Figure.h"

//����
int field[FIELD_HEIGHT + 1][FIELD_WIDTH] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

//�����������
Figure::Figure()
{
	srand(time(0));
	type = rand() % 7;
	size = SHAPES[type][4][0];
	if (size == 4) y = -1;
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			shape[i][j] = SHAPES[type][i][j];
	createFromShape();
}

//�������� ������ �� ������
void Figure::createFromShape()
{
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			if (shape[j][i] == 1)
			{
				Block b(i + x, j + y);
				figure.push_back(b);
			}
}

//���������� ������
void Figure::paint(RenderWindow &win)
{
	for each (Block block in figure)
		block.paint(win, type);
}

//������ ��������� �����
bool Figure::isTouchGround()
{
	for (int i = 0; i < 4; ++i)
	{
		if (field[figure[i].y + 1][figure[i].x] > 0)
			return true;
	}
	return false;
}

//������ ��������� ������� ���� ��� ������ ������
bool Figure::isTouch(int direction)
{
	for (int i = 0; i < 4; ++i)
	{
		//�������� �� ������� �����
		if (direction == Keyboard::Left)
			if (figure[i].x == 0 || field[figure[i].y][figure[i].x - 1] > 0) return true;

		//�������� �� ������� ������
		if (direction == Keyboard::Right)
			if (figure[i].x == FIELD_WIDTH - 1 || field[figure[i].y][figure[i].x + 1] > 0) return true;
	}
	return false;
}

//������ ��������� ������� ������� ����
bool Figure::isCrossTop() 
{ 
	for (int i = 0; i < 4; ++i)
	{
		if (field[figure[i].y][figure[i].x] > 0)
			return true;
	}
	return false;
}

//�������� ������ �� ����
void Figure::leaveOnField() 
{
	for (int i = 0; i < 4; ++i)
	{
		if (type == 0) type = 7;

		field[figure[i].y][figure[i].x] = type;		
	}
}

//�������� ������ �� ��� ����
void Figure::stepDown() 
{
	for (int i = 0; i < 4; ++i)
	{
		figure[i].y += 1;		
	}
	y++;
}

//�������� ������
void Figure::drop() 
{
	while (!isTouchGround())
	{
		stepDown();
	}
}

//��������� ������ ����� ��� ������
void Figure::move(int direction)
{
	if (!isTouch(direction))
	{
		int dx = 0;
		if (direction == Keyboard::Left) dx = -1;
		if (direction == Keyboard::Right) dx = 1;
		for (int i = 0; i < 4; ++i)
		{
			figure[i].x += dx;
		}
		x += dx;
	}
}

//�� ������������ ������
bool Figure::notRotate()
{	
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)		
			if (shape[j][i] == 1)
			{
				if ((i + x) < 0 || (i + x) > FIELD_WIDTH - 1) return true;
				if (j + y < 0) return true;
				if(field[y + j][x + i] > 0) return true;
			}		
	return false;
}

//��������� ������
void Figure::rotate() 
{	
	switch (type)
	{
	case 0: case 1: case 2: case 3:
	{
		if (revers)
		{
			counterClockWiseRotation();
			revers = false;
		}
		else
		{
			clockWiseRotation();
			revers = true;
		}
		break;
	}
	case 4: case 5: case 6: clockWiseRotation();
		break;
	}

	if (!notRotate())
	{
		figure.clear();
		createFromShape();
	}	
	else
		counterClockWiseRotation();
}

//�������� �� ������� �������
void Figure::clockWiseRotation()
{
	for (int i = 0; i < size / 2; ++i)
		for (int j = i; j < size - 1 - i; ++j)
		{
			int tmp = shape[size - 1 - j][i];
			shape[size - 1 - j][i] = shape[size - 1 - i][size - 1 - j];
			shape[size - 1 - i][size - 1 - j] = shape[j][size - 1 - i];
			shape[j][size - 1 - i] = shape[i][j];
			shape[i][j] = tmp;
		}
}

//�������� ������ ������� �������
void Figure::counterClockWiseRotation()
{
	for (int i = 0; i < size / 2; ++i)
		for (int j = i; j < size - 1 - i; ++j)
		{
			int tmp = shape[i][j];
			shape[i][j] = shape[j][size - 1 - i];
			shape[j][size - 1 - i] = shape[size - 1 - i][size - 1 - j];
			shape[size - 1 - i][size - 1 - j] = shape[size - 1 - j][i];
			shape[size - 1 - j][i] = tmp;
		}	
}
