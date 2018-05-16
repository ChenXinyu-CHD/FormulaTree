/**
 * name : Item.h;
 * date : 2018/5/8;
 * g++ version : 7.3.1;
 * g++ options : -O0;
 * */

//You should better build it
//whithout -std=c++11 -O2;

#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
public:
	virtual std::string getValue()=0;
	virtual double calculate()=0;

	virtual void setValue(std::string::iterator begin,std::string::iterator end)=0;
};

#endif /* ITEM_H */
