#ifndef __CATEGORY_H
#define __CATEGORY_H

#include "WordProcessor.h"

class Category
{
private:
	WordProcessor* wp_;
	char* subject_;

public:
	Category(char* subject, int nWords);
	~Category();

	char* getSubject() { return subject_; }
	WordProcessor* getWordProcessor() { return wp_; }
};

#endif //__CATEGORY_H