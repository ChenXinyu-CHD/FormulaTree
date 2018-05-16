/**
 * name : main.cpp;
 * date : 2018/5/8;
 * g++ version : 7.3.1;
 * g++ options : -O0;
 * */

//You should better build it
//without -std=c++11 -O2;

#include <iostream>
#include "Formula.h"

using namespace std;

int main()
{
	Formula formula;
	string str;

	cin>>str;
	formula.setValue(str);

	cout<<formula.getValue()<<endl;
	cout<<formula.calculate()<<endl;

	return 0;
}
