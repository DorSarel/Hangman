#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include "Category.h"
#include "GameBoard.h"
#include "WordProcessor.h"
#include "Word.h"
using namespace std;

const unsigned char MAX_SIZE = 255;
const unsigned char MAX_ATTEMPTS = 8;

void startGame(Category**, unsigned nOfCategories);
bool playNewWord(const WordProcessor* wp, Word** wordInUse);
bool playAgain(Word* word);
bool play(Word* word);
int getGameState(bool isWon);
void winningMsg(Word* word);
bool losingMsg(Word* word);
void readWords(WordProcessor* wp);
void readCategories(Category**, unsigned nOfCategories);
Category* generateCategory(Category**, unsigned nOfCategories);

// Globals
GameBoard gb;

int main()
{

	cout << "Welcome to my Hangman Game!!!" << endl;
	cout << "In order to start - Please enter number of catgories you want to enter: ";
	unsigned nOfCategories;
	cin >> nOfCategories;

	Category** categories = new Category*[nOfCategories];
	readCategories(categories, nOfCategories);

	cout << "Categories has been created. Start adding words..." << endl;

	for (unsigned idx = 0; idx < nOfCategories; ++idx)
	{
		cout << "Enter words for " << categories[idx]->getSubject() << " category" << endl;
		readWords(categories[idx]->getWordProcessor());
		cout << endl;
	}

	cout << "Let`s start playing!!!" << endl;
	startGame(categories, nOfCategories);

	delete[]categories;
	return 0;
}

void readCategories(Category** categories, unsigned nOfCategories)
{
	char subject[MAX_SIZE];
	unsigned nOfWords;
	for (unsigned idx = 0; idx < nOfCategories; ++idx)
	{
		cout << "Enter the category name: ";
		cin.getline(subject, MAX_SIZE);
		cin.getline(subject, MAX_SIZE);

		cout << "Enter number of words for the category: ";
		cin >> nOfWords;

		categories[idx] = new Category(subject, nOfWords);
		cin.getline(subject, MAX_SIZE); // flush
		cout << endl;
	}
}

void readWords(WordProcessor* wp)
{
	char temp[MAX_SIZE];
	Word** arr = wp->getWordsArr();

	cin.getline(temp, MAX_SIZE); //handle buffer
	for (unsigned idx = 0; idx < wp->getLength(); ++idx)
	{
		cout << "Enter word [" << idx + 1 << " / " << wp->getLength() << "]: ";
		cin.getline(temp, MAX_SIZE);

		arr[idx] = new Word(temp);
	}
	system("cls");
}

Category* generateCategory(Category** categories, unsigned nOfCategories)
{
	return categories[rand() % nOfCategories];
}

void startGame(Category** categories, unsigned nOfCategories)
{
	Word* wordInUse = nullptr;
	Category* currentCategory = nullptr;
	int choice = 1; // for first round
	bool isWon = false;

	do
	{
		currentCategory = generateCategory(categories, nOfCategories);
		switch (choice)
		{
		case 0:
			cout << "Bye Bye" << endl;
			gb.printStatistic();
			exit(1);
			break;

		case 1:
			isWon = playNewWord(currentCategory->getWordProcessor(), &wordInUse);
			break;

		case 2:
			isWon = playAgain(wordInUse);
			break;
		}

		choice = getGameState(isWon);
		system("cls");
	} while (true);
}

bool playNewWord(const WordProcessor* wp, Word** wordInUse)
{
	*wordInUse = wp->generateRandomWord();
	return play(*wordInUse);
}

bool playAgain(Word* word)
{
	word->resetWord();
	return play(word);
}

bool play(Word* word)
{
	unsigned attempts = 0;
	char toCheck;
	bool isWon = false;

	word->printCachedWord();

	while (!word->isEqual() && attempts < MAX_ATTEMPTS)
	{
		cout << "Insert char [" << attempts + 1 << " / " << (int)MAX_ATTEMPTS << "]: ";
		cin >> toCheck;

		if (!word->fillCachedWord(toCheck))
		{
			++attempts;
			cout << "Oops... Wrong choice..." << endl;
		}
		else
			cout << "Great! Keep going :)" << endl;
	}

	if (word->isEqual() && attempts < MAX_ATTEMPTS)
	{
		winningMsg(word);
		isWon = true;
	}
	else
	{
		isWon = losingMsg(word);
	}

	return isWon;
}

void winningMsg(Word* word)
{
	cout << "Congratulations !!! You discovered the word \"" << word->getWord() << "\" successfuly" << endl;
	gb.incrementScore();
}

bool losingMsg(Word* word)
{
	cout << "You lost..." << endl;
	gb.decrementScore();

	if (gb.getScore() > 0)
	{
		cout << "Do you want another " << MAX_ATTEMPTS << " attempts for 5 points? ";
		int choice;
		cin >> choice;

		if (choice)
		{
			gb.decrementScore(5);
			return play(word);
		}
	}

	return false;
}

int getGameState(bool isWon)
{
	int choice;
	if (isWon)
	{
		cout << "Do you want another round? (1=yes, 0=no) " << endl;
	}
	else
	{
		cout << "Do you want a new word (1)?, the same word (2)? or finish (0)? ";
	}
	cin >> choice;
	return choice;
}