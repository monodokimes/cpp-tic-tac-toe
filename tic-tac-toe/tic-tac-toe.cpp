// tic-tac-toe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>

bool checkVictory(char board[]);
bool checkDraw(char board[], char players[]);
int getInput();
void drawBoard(char board[]);
void runGame();

int main()
{
	runGame();
}

bool checkVictory(char board[])
{
	// Check columns
	for (size_t i = 0; i < 3; i++)
	{
		if (board[i] == board[i + 3] && board[i] == board[i + 6])
			return true;
	}

	// Check rows
	for (size_t i = 0; i < 9; i += 3)
	{
		if (board[i] == board[i + 1] && board[i] == board[i + 2])
			return true;
	}

	// Check diagonals
	if ((board[0] == board[4] && board[0] == board[8]) || (board[2] == board[4] && board[2] == board[6]))
		return true;

	return false;
}

bool checkDraw(char board[], char players[])
{
	for (size_t i = 0; i < sizeof(players) / sizeof(char); i++)
	{
		for (size_t j = 0; j < sizeof(board) / sizeof(char); j++)
		{
			if (board[j] != players[i])
				return false;
		}
	}
	return true;
}

int getInput()
{
	bool inputValid = false;
	int result = 0;
	std::stringstream stream;

	do
	{
		std::string userInput;
		std::cout << "Enter a number [1-9]: ";
		std::cin >> userInput;
		stream = std::stringstream(userInput);
		inputValid = !(stream >> result).fail() && result >= 1 && result <= 9;
	} while (!inputValid);

	return result - 1;
}

void drawBoard(char board[])
{
	std::cout << "+---+---+---+" << std::endl;
	for (size_t i = 0; i < 9; i += 3)
	{
		std::cout << "|   |   |   |" << std::endl;
		std::cout << "| " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << " |" << std::endl;
		std::cout << "|   |   |   |" << std::endl;
		std::cout << "+---+---+---+" << std::endl;
	}
}

void runGame()
{
	char board[] = {
		'1', '2', '3',
		'4', '5', '6',
		'7', '8', '9'
	};
	char players[] = { 'X', 'O' };
	int currentPlayer = 1;
	int moves = 0;
	int maxMoves = 9;
	bool gameOver = false;

	while (!gameOver)
	{
		system("cls");

		bool validMove = true;
		int move = 0;
		currentPlayer = currentPlayer == 0 ? 1 : 0;

		drawBoard(board);
		std::cout << players[currentPlayer] << " to move" << std::endl;
		do
		{
			validMove = true;
			move = getInput();

			for (size_t i = 0; i < sizeof(players) / sizeof(char); i++)
			{
				if (board[move] == players[i])
				{
					std::cout << "Space occupied" << std::endl;
					validMove = false;
				}
			}
		} while (!validMove);

		board[move] = players[currentPlayer];
		moves++;

		gameOver = checkVictory(board) || moves == maxMoves;
	}

	if (checkVictory(board))
	{
		std::cout << "Game over! Player " << players[currentPlayer] << " wins!" << std::endl;
		return;
	}

	std::cout << "Game over! It was a draw!" << std::endl;
}


