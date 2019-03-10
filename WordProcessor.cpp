#include "WordProcessor.h"
#include <ctime>
#include <cstdlib>

WordProcessor::WordProcessor(unsigned length)
{
	length_ = length;
	words_ = new Word*[length_];
	//srand((unsigned)time(0));
}


WordProcessor::~WordProcessor()
{
	for (unsigned i = 0; i < length_; ++i)
		delete words_[i];
	delete[]words_;
}

unsigned WordProcessor::generateRandomNumber() const
{
	return rand() % length_;
}

Word* WordProcessor::generateRandomWord() const
{
	Word* w = words_[generateRandomNumber()];
	w->resetWord();
	return w;
}
