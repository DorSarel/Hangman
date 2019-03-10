#pragma warning (disable : 4996)

#include "Word.h"
#include <string>
#include <iostream>
using namespace std;



Word::Word(char* word)
{
	size_ = strlen(word);
	word_ = new char[size_ + 1];
	cachedWord_ = new char[size_ + 1];

	strncpy(word_, word, size_);
	word_[size_] = '\0';
	cachedWord_[size_] = '\0';

	convertTolower(word_);
	initLettersArr();

	cout << "Created new word object: " << word_ << endl;
}

Word::~Word()
{
	delete[]word_;
	delete[]cachedWord_;
}

void Word::initCachedWord()
{
	for (unsigned i = 0; i < size_; ++i)
	{
		if (word_[i] == ' ')
			cachedWord_[i] = ' ';
		else
			cachedWord_[i] = '_';
	}
}

const Letter* Word::checkLetterInWord(char ch) const
{
	for (unsigned i = 0; i < arrSize_; ++i)
	{
		if (wordL_[i]->isEqual(ch))
			return wordL_[i];
	}

	return nullptr;
}

void Word::printCachedWord() const
{
	for (unsigned i = 0; i < size_; ++i)
	{
		cout << cachedWord_[i] << " ";
	}

	cout << endl;
}

bool Word::fillCachedWord(char ch)
{
	bool res = false;
	const Letter* let = checkLetterInWord(ch);

	if (let != nullptr)
	{
		for (unsigned i = 0; i < let->getSize(); ++i)
		{
			cachedWord_[let->getOccurs()[i]] = ch;
		}
		res = true;
	}

	printCachedWord();
	return res;
}

bool Word::isEqual() const
{
	return (strcmp(word_, cachedWord_) == 0);
}

void Word::convertTolower(char* word)
{
	unsigned idx = 0;
	while (word[idx] != '\0')
	{
		word[idx] = tolower(word[idx]);
		++idx;
	}
}

unsigned Word::getDifferentLettersInWord() const
{ // bucket sort
	unsigned arr[26];
	for (unsigned i = 0; i < 26; ++i)
		arr[i] = 0;

	unsigned idx = 0;
	while (word_[idx] != '\0')
	{
		unsigned pos = word_[idx] - 'a';
		if (arr[pos] == 0)
			arr[pos] += 1;

		++idx;
	}

	unsigned res = 0;
	for (unsigned i = 0; i < 26; ++i)
	{
		if (arr[i] > 0)
			++res;
	}

	return res;
}

void Word::initLettersArr()
{
	arrSize_ = getDifferentLettersInWord();
	wordL_ = new Letter*[arrSize_];

	wordL_[0] = new Letter(word_[0], 0); // init first letter
	unsigned lettersArrSize = 1;
	unsigned idx = 1;
	bool shouldInsertNew = true;

	// dor - TBD efficiency
	while (word_[idx] != '\0')
	{
		shouldInsertNew = true;

		if (word_[idx] == ' ')
		{
			++idx;
			continue;
		}

		for (unsigned i = 0; i < lettersArrSize; ++i)
		{
			if (!wordL_[i]->isEqual(word_[idx]))
				continue;

			wordL_[i]->addIdxToArr(idx);
			shouldInsertNew = false;
		}

		if (shouldInsertNew)
		{
			wordL_[lettersArrSize] = new Letter(word_[idx], idx);
			++lettersArrSize;
		}
		++idx;
	}
}