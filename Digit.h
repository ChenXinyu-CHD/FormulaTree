/**
 * name : Digit.h;
 * date : 2018/5/8;
 * g++ version : 7.3.1;
 * g++ options : -O0;
 * */

//You should better build it
//whithout -std=c++11 -O2;

#ifndef DIGIT_H
#define DIGIT_H

#include "Item.h"

class Digit : public Item
{
private:
	int value;
public:
	std::string getValue();
	double calculate();

	void setValue(std::string::iterator begin,std::string::iterator end);
};

#endif /* DIGIT_H */
