#ifndef __WORD_PROCESSOR_H
#define __WORD_PROCESSOR_H

#include "Word.h"

class WordProcessor
{
private:
	Word **words_;
	unsigned length_;

public:
	WordProcessor(unsigned length);
	~WordProcessor();
	WordProcessor(WordProcessor& other) = delete;

	unsigned getLength() const { return length_; }
	Word** getWordsArr() { return words_; }

	Word* generateRandomWord() const;
	unsigned generateRandomNumber() const;
};

#endif //__WORD_PROCESSOR_H