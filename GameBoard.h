#pragma once
class GameBoard
{
private:
	char *name_;
	int score_;

public:
	GameBoard(char* name = "Player 1", int score = 0);
	~GameBoard();

	int getScore() { return score_; }

	void incrementScore();
	void decrementScore(unsigned score = 10);
	void printStatistic();
};

