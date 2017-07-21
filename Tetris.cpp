#include "Tetris.h"

//увеличение скорости
void Tetris::increaseSpeed()
{	
	if (gameScore - pastScore >= 500)
	{
		pastScore = gameScore;
		delay -= 0.1f;
	}
}

//проверка на линию 
void Tetris::checkLines()
{
	int row = FIELD_HEIGHT - 1;
	int countFillRows = 0;

	while (row > 0) 
	{
		int filled = 1; //кол-во заполненных линий
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

			//обработчик нажатия клавиш						
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Up) figure->rotate();
				if (event.key.code == Keyboard::Left || event.key.code == Keyboard::Right) figure->move(event.key.code);
				if (event.key.code == Keyboard::Down) figure->drop();
			}
		}
//===========================главная логика=============================================

		if (!gameOver)
		{
			checkLines();//проверка на линию
			window.setTitle("Tetris! SCORE = "+ std::to_string(gameScore));
			if (timer > delay)
			{							
				if (figure->isTouchGround()) //если фигура коснулась земли
				{
					figure->leaveOnField(); //оставить фигуру на земле				
					delete figure;
					figure = new Figure();//новая фигура
					gameOver = figure->isCrossTop();
				}
				else
				{
					figure->stepDown();//сдвинуть фигуру на 1 шаг вниз	
				}
				timer = 0;		
			}
		}		
//===========================вывод на экран================================

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