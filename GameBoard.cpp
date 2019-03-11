#pragma warning (disable : 4996)

#include "GameBoard.h"
#include <string>
#include <iostream>
using namespace std;

GameBoard::GameBoard(char* name, int score)
{
	score_ = score;
	name_ = new char[strlen(name) + 1];
	strcpy(name_, name);
}


GameBoard::~GameBoard()
{
	delete[]name_;
}

void GameBoard::incrementScore()
{
	score_ += 10;
	cout << "Current player score is: " << score_ << endl;
}

void GameBoard::decrementScore(unsigned score)
{
	score_ -= score;
	if (score_ < 0)
		score_ = 0;

	cout << "Current player score is: " << score_ << endl;
}

void GameBoard::printStatistic()
{
	cout << endl;
	cout << "Player Statistics:" << endl;
	cout << "Score: " << score_ << endl;
	cout << endl;
}