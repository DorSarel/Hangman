#include "Letter.h"
#include <stdlib.h>

Letter::Letter(char c, unsigned idx)
{
	ch_ = c;
	phSize_ = 1;
	logicalSize_ = 0;
	occur_ = new unsigned[phSize_];
	addIdxToArr(idx);
}


Letter::~Letter()
{
	delete[]occur_;
}

void Letter::addIdxToArr(unsigned idx)
{
	if (phSize_ == logicalSize_)
	{
		phSize_++;
		occur_ = (unsigned*)realloc(occur_, phSize_ * sizeof(unsigned));
	}

	occur_[logicalSize_] = idx;
	++logicalSize_;
}
