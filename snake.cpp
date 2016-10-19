#include <iostream>
#include <conio.h>
#include <Windows.h>
bool gameover;
const int width =20;
const int height = 20;
int x, y;
int objX, objY;
int score;
int tailX[100], tailY[100];
int nTail;
enum eDirection{ STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup()
{
	gameover = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	objX = rand() % width;
	objY = rand() % height;
	score = 0;
}

void Draw()
{
	system("cls");
	for (int i = 0; i < width + 2; i++)
		std::cout << "#";
	std::cout << std::endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				std::cout << "#";

			if (i == y && j == x)
				std::cout << "O";
			else if (i == objY && j == objX)
				std::cout << "Xd";
			else
			{
				bool print = false;
				for (int k = 0 ; k < nTail; k++)
				{

					if (tailX[k] == j && tailY[k] == i)
					{
						std::cout << "O";
						print = true;

					}
				
				}

				if (!print)
					std::cout << " ";
			}

			if (j == width - 1)
				std::cout << "#";

		}
		std::cout << std::endl;

	}

	for (int i = 0; i < width + 2; i++)
		std::cout << "#";
		std::cout << std::endl;
		std::cout << "The score is: " << score << std::endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameover = true;
			break;
  
		}
	}
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;

	}

	if (x > width || x < 0 || y > height || y < 0)
		gameover = true;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameover = true;

	if (x == objX && y == objY)
	{
		score += 10;
		objX = rand() % width;
		objY = rand() % height;
		nTail++;
	}
}

int main()
{
	Setup();
		while (!gameover)
		{
			
			Draw();
			Input();
			Logic();
			Sleep(80);
		}
		
	return 0;
}
