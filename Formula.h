/**
 * name : Formula.h;
 * date : 2018/5/8;
 * g++ version : 7.3.1;
 * g++ options : -O0;
 * */

//You should better build it
//whithout -std=c++11 -O2;

#ifndef FORMULA_H
#define FORMULA_H

#include "Item.h"

class Formula : public Item
{
private:
	Item *leftItem;
	Item *rightItem;
	char theOperator;
public:
	Formula();
	~Formula();

	void setValue(std::string str);

	std::string getValue();
	double calculate();

	void setValue(std::string::iterator begin,std::string::iterator end);
private:
	void clearAll();
};

#endif /* FORMULA_H */
