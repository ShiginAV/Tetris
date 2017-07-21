#include "Tetris.h"

//���������� ��������
void Tetris::increaseSpeed()
{	
	if (gameScore - pastScore >= 500)
	{
		pastScore = gameScore;
		delay -= 0.1f;
	}
}

//�������� �� ����� 
void Tetris::checkLines()
{
	int row = FIELD_HEIGHT - 1;
	int countFillRows = 0;

	while (row > 0) 
	{
		int filled = 1; //���-�� ����������� �����
		for (int col = 0; col < FIELD_WIDTH; ++col)
			filled *= (field[row][col] > 0) ? 1 : ((field[row][col] < 0) ? -1 : 0);

		if (filled > 0)
		{
			countFillRows++;
			for (int i = row; i > 0; --i)
				for (int j = 0; j < FIELD_WIDTH; ++j)				
					field[i][j] = field[i - 1][j];				
		}
		else
			row--;
	}
	if (countFillRows > 0) 	
		gameScore += SCORES[countFillRows - 1];
	increaseSpeed();
}

//====================================================================
void Tetris::run()
{
	RenderWindow window(VideoMode(FIELD_WIDTH * BLOCK_SIZE, FIELD_HEIGHT * BLOCK_SIZE), "Tetris!");
	window.setSize(Vector2u(FIELD_WIDTH * BLOCK_SIZE * 1.5, FIELD_HEIGHT * BLOCK_SIZE * 1.5));
	Figure *figure = new Figure();
	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();

			//���������� ������� ������						
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Up) figure->rotate();
				if (event.key.code == Keyboard::Left || event.key.code == Keyboard::Right) figure->move(event.key.code);
				if (event.key.code == Keyboard::Down) figure->drop();
			}
		}
//===========================������� ������=============================================

		if (!gameOver)
		{
			checkLines();//�������� �� �����
			window.setTitle("Tetris! SCORE = "+ std::to_string(gameScore));
			if (timer > delay)
			{							
				if (figure->isTouchGround()) //���� ������ ��������� �����
				{
					figure->leaveOnField(); //�������� ������ �� �����				
					delete figure;
					figure = new Figure();//����� ������
					gameOver = figure->isCrossTop();
				}
				else
				{
					figure->stepDown();//�������� ������ �� 1 ��� ����	
				}
				timer = 0;		
			}
		}		
//===========================����� �� �����================================

		for (int i = 0; i < FIELD_HEIGHT; ++i)				
			for (int j = 0; j < FIELD_WIDTH; ++j)
			{
				if (field[i][j] > 0)
				{
					Block b(j, i);
					b.paint(window, field[i][j]);
				}
			}

		figure->paint(window);
		window.display();				
		window.clear();		
	}	
}