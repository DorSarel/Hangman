#ifndef __WORD_H
#define __WORD_H

#include "Letter.h"
const int NOT_FOUND = -1;

class Word
{
private:
	Letter** wordL_;
	unsigned arrSize_;
	char* word_; // TBD - remove
	char* cachedWord_;
	unsigned size_;

public:
	Word(char* word);
	~Word();

	char* getWord() const { return word_; }

	unsigned getDifferentLettersInWord() const;
	void initCachedWord();
	void initLettersArr();
	const Letter* checkLetterInWord(char ch) const;
	void printCachedWord() const;
	bool fillCachedWord(char ch);
	bool isEqual() const;
	void convertTolower(char* word);

	void resetWord() { initCachedWord(); }
};

#endif // __WORD_H