#include <iostream>
#include <stdlib.h>
#include "WordProcessor.h"
#include "Word.h"
using namespace std;

const unsigned char MAX_SIZE = 255;
const unsigned char MAX_ATTEMPTS = 5;

void readWords(WordProcessor& wp);
void startGame(const WordProcessor& wp);

int main()
{

	cout << "Welcome to my Hangman Game!!!" << endl;
	cout << "In order to start - please enter number of words to be inserted: ";
	unsigned nOfWords;
	cin >> nOfWords;

	WordProcessor wp(nOfWords);
	readWords(wp);

	cout << "Lets start playing!!!" << endl;

	int choice;
	do
	{
		startGame(wp);
		cout << "Do you want another round? (1=yes, 0=no) " << endl;
		cin >> choice;

		if (choice == 0)
		{
			cout << "Bye Bye" << endl;
			exit(1);
		}

		system("cls");
	} while (choice != 0);

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

void startGame(const WordProcessor& wp)
{
	unsigned attempts = 0;
	char toCheck;
	Word* currentWord = wp.generateRandomWord();
	currentWord->printCachedWord();

	while (!currentWord->isEqual() && attempts < MAX_ATTEMPTS)
	{
		cout << "Insert char [" << attempts + 1 << " / " << (int)MAX_ATTEMPTS << "]: ";
		cin >> toCheck;

		if (!currentWord->fillCachedWord(toCheck))
		{
			++attempts;
			cout << "Oops... Wrong choice..." << endl;
		}
		else
			cout << "Great! Keep going :)" << endl;
	}

	if (currentWord->isEqual() && attempts < MAX_ATTEMPTS)
		cout << "Congratulations !!! You discovered the word \"" << currentWord->getWord() << "\" successfuly" << endl;
	else
		cout << "You lost..." << endl;
}