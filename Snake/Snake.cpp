#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdlib>
using namespace std;

void cleanBoard(char** board, int magnitude, char sample)
{
	for (int i = 1; i <= magnitude; i++)
	{
		for (int j = 1; j <= magnitude; j++)
		{
			board[i][j] = sample;
		}
	}
}

void showBoard(int magnitude, char** board)
{
	system("cls");
	for (int i = 0; i <= magnitude + 1; i++)
	{
		for (int j = 0; j <= magnitude + 1; j++)
			cout << board[i][j];
		cout << endl;
	}
}

void fillBoard(char** board, int magnitude)
{
	for (int i = 0; i < magnitude + 2; i++)
		board[0][i] = '#';
	for (int i = 0; i < magnitude + 2; i++)
		board[magnitude + 1][i] = '#';
	for (int i = 0; i < magnitude + 2; i++)
		board[i][0] = '#';
	for (int i = 0; i < magnitude + 2; i++)
		board[i][magnitude + 1] = '#';
}
void snakeBoard(char** board, int** snake, int slengh, int* fruit)
{
	board[fruit[0]][fruit[1]] = '$';
	for (int i = 1; i < slengh; i++)
	{
		board[snake[i][0]][snake[i][1]] = '@';
	}
	board[snake[0][0]][snake[0][1]] = '&';
}

void snakeMove(int** snake, char direction, int slengh)
{
	for (int i = slengh; i > 0; i--)
	{
		snake[i][0] = snake[i - 1][0];
		snake[i][1] = snake[i - 1][1];
	}
	switch (direction)
	{
	case 'w': snake[0][0] -= 1; break;
	case 'd': snake[0][1] += 1; break;
	case 's': snake[0][0] += 1; break;
	case 'a': snake[0][1] -= 1; break;
	}
}

bool snakeWallCollision(int** snake, int magnitude)
{
	if (snake[0][0] == 0 || snake[0][0] == magnitude + 1 || snake[0][1] == 0 || snake[0][1] == magnitude + 1)
	{
		system("cls");
		cout << "Game Over" << endl;
		return true;
	}
	else return false;
}

bool snakeSnakeCollision(int** snake, int snakeLengh)
{
	for (int i = 1; i < snakeLengh; i++)
		if (snake[0][0] == snake[i][0] && snake[0][1] == snake[i][1]) {
			system("cls");
			cout << "Game Over" << endl;
			return true;
		}
	return false;
}

void snakeFruit(int** snake, int* fruit, int &snakeLengh, int magnitude)
{
	if (snake[0][0] == fruit[0] && snake[0][1] == fruit[1])
	{
		bool pf = true;
		snakeLengh++;
		snake[snakeLengh][0] = snake[snakeLengh - 1][0]+1;
		snake[snakeLengh][1] = snake[snakeLengh - 1][1]+1;
		while (pf) 
		{
			pf = false;
			fruit[0] = (rand() % magnitude) + 1;
			fruit[1] = (rand() % magnitude) + 1;
			for (int i = 0; i < snakeLengh; i++)
				if (fruit[0] == snake[i][0] && fruit[1] == snake[i][1]) pf = true;
		}
	}

}

int main()
{
	bool magnitudeRight = true;
	int magnitude;
	char direction = 's';
	int* fruit = new int[2];
	srand(time(NULL));
	fruit[0] = 7;
	fruit[1] = 8;
	
	cout << "Jak duza ma byc plansza? Od 10x10 do 20x20" << endl;
	//while (magnitudeRight)
	//{
		magnitude = 10;
		/*if (magnitude > 20 || magnitude < 10)
			cout << "Podales zle wymiary, podaj jeszcze raz." << endl;
		else
			magnitudeRight = false;*/
	/*}*/
	char blank;
	char** board = new char*[magnitude+2];
	for (int i = 0; i < magnitude + 2; i++)
		board[i] = new char[magnitude + 2];
	fillBoard(board, magnitude);
	showBoard(magnitude, board);
	int snakeLengh = 5;
	int** snake = new int*[400];
	for (int i = 0; i < 400; i++)
		snake[i] = new int[2];
	snake[0][0] = 5;
	snake[0][1] = 1;
	snake[1][0] = 4;
	snake[1][1] = 1;
	snake[2][0] = 3;
	snake[2][1] = 1;
	snake[3][0] = 2;
	snake[3][1] = 1;
	snake[4][0] = 1;
	snake[4][1] = 1;

	blank = board[1][1];
	snakeBoard(board, snake, snakeLengh, fruit);
	showBoard(magnitude, board);
	
	bool wall = false;
	while (true)
	{
		if (snakeWallCollision(snake, magnitude)) break;
		
		while (true)
		{
			direction = _getch();
			if (direction == 'w' || direction == 'd' || direction == 's' || direction == 'a') break;
		}
		snakeFruit(snake, fruit, snakeLengh, magnitude);
		snakeMove(snake, direction, snakeLengh);
		if (snakeSnakeCollision(snake, snakeLengh)) break;
		
		cleanBoard(board, magnitude, blank);
		snakeBoard(board, snake, snakeLengh, fruit);
		showBoard(magnitude, board);
	}
	delete snake;
	delete board;

}