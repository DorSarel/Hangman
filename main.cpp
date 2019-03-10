#include <iostream>
#include <stdlib.h>
#include "WordProcessor.h"
#include "Word.h"
using namespace std;

const unsigned char MAX_SIZE = 255;
const unsigned char MAX_ATTEMPTS = 8;

void readWords(WordProcessor& wp);
bool startGame(const WordProcessor& wp, Word**);
bool play(Word* word);
int getGameState(bool isWon);

int main()
{

	cout << "Welcome to my Hangman Game!!!" << endl;
	cout << "In order to start - please enter number of words to be inserted: ";
	unsigned nOfWords;
	cin >> nOfWords;

	WordProcessor wp(nOfWords);
	readWords(wp);

	cout << "Let`s start playing!!!" << endl;

	int choice = 1;
	Word* wordInUse = nullptr;
	bool isWon = false;

	do
	{
		switch (choice)
		{
		case 0:
			cout << "Bye Bye" << endl;
			exit(1);
			break;

		case 1:
			 isWon = startGame(wp, &wordInUse);
			 break;

		case 2:
			wordInUse->resetWord();
			isWon = play(wordInUse);
			break;
		}

		choice = getGameState(isWon);
		system("cls");
	} while (true);

	return 0;
}

void readWords(WordProcessor& wp)
{
	char temp[MAX_SIZE];
	Word** arr = wp.getWordsArr();

	cin.getline(temp, MAX_SIZE); //handle buffer
	for (unsigned idx = 0; idx < wp.getLength(); ++idx)
	{
		cout << "Enter word [" << idx + 1 << " / " << wp.getLength() << "]: ";
		cin.getline(temp, MAX_SIZE);

		arr[idx] = new Word(temp);
	}
	system("cls");
}

bool startGame(const WordProcessor& wp, Word** wordInUse)
{
	*wordInUse = wp.generateRandomWord();
	return play(*wordInUse);
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
		cout << "Congratulations !!! You discovered the word \"" << word->getWord() << "\" successfuly" << endl;
		isWon = true;
	}
	else
		cout << "You lost..." << endl;

	return isWon;
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