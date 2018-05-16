/**
 * name : Digit.cpp;
 * date : 2018/5/8;
 * g++ version : 7.3.l;
 * g++ options : -O0;
 * */

//This is the defination of class Digit
//which is decleared in Digit.h;

//You should better build it
//without -std=c++11 -O2;

#include "Digit.h"
#include <sstream>

using namespace std;

string Digit::getValue()
{
	ostringstream result;
	result<<value;

	return result.str();
}

double Digit::calculate()
{return value;}

void Digit::setValue(string::iterator begin,string::iterator end)
{
	value = 0.0;
	int number = 0;

	while(begin != end)
	{
		number *= 10;
		number += (int)(*begin & 0x0f);
		++begin;
	}
	number *= 10;
	number += (int)(*begin & 0x0f);

	value = number;
}
