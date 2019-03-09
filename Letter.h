#ifndef __LETTER_H
#define __LETTER_H

class Letter
{
private:
	char ch_;
	unsigned* occur_;
	unsigned logicalSize_;
	unsigned phSize_;

public:
	Letter(char c, unsigned idx);
	~Letter();

	unsigned* getOccurs() const { return occur_; }
	unsigned getSize() const { return phSize_; }
	bool isEqual(char c) const { return c == ch_; }
	void addIdxToArr(unsigned idx);
};

#endif //__LETTER_H