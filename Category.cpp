#include "Category.h"
#include <string>


Category::Category(char* subject, int nElem)
{
	wp_ = new WordProcessor(nElem);
	subject_ = new char[strlen(subject) + 1];
	strcpy(subject_, subject);
}


Category::~Category()
{
	delete wp_;
	delete[]subject_;
}
