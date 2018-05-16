/**
 * name : Formula.cpp;
 * date : 2018/5/8;
 * g++ version : 7.3.1;
 * g++ options : -O0;
 * */

//This is the defination of class Digit
//which is decleared in Digit.h;

//You should better build it
//without -std=c++11 -O2;

#include "Formula.h"
#include "Digit.h"
#include <iostream>
#include <cctype>

using namespace std;

Formula::Formula():
	leftItem(NULL),
	rightItem(NULL),
	theOperator('#')
{/* Nothing to do */}

Formula::~Formula()
{clearAll();}

void Formula::clearAll()
{
	if(NULL != leftItem)
		delete leftItem;
	if(NULL != rightItem)
		delete rightItem;
	theOperator = '#';
}

void Formula::setValue(string str)
{setValue(str.begin(),str.end());}

string Formula::getValue()
{
	string result;
	static const string SPACE = " ";
	result += leftItem->getValue() + SPACE + rightItem->getValue() + SPACE + theOperator;

	return result;
}

inline double calculate(double leftOne,double rightOne,char Operator)
{
	double result;

	switch(Operator)
	{
		case '+' :
			result = leftOne + rightOne;
			break;
		case '-' :
			result = leftOne - rightOne;
			break;
		case '*' :
			result = leftOne * rightOne;
			break;
		case '/' :
			result = leftOne / rightOne;
			break;
		default:
			throw "Operator Error in Fomula.";
	}
	return result;
}

double Formula::calculate()
{
	double result;
	try{
		result = ::calculate(leftItem->calculate(),rightItem->calculate(),theOperator);
	}catch(string errorMSG){
		cerr<<errorMSG<<endl;
	}

	return result;
}

inline bool isOperator(char ch)
{
	return 
	(
		('+' == ch) ||
		('-' == ch) ||
		('*' == ch) ||
		('/' == ch)
	);

}

inline string::iterator findLeft(string::iterator iter)
{
	int flag = 1;

	while(flag)
	{
		--iter;
		if(*iter == '(')
			--flag;
		if(*iter == ')')
			++flag;
	}

	return iter;
}

inline bool lower(char newOne,char oldOne)
{
	bool result = false;

	if(oldOne == '#')
		result = true;
	if(newOne == '+' || newOne == '-')
		if(oldOne == '*' || oldOne == '/')
			result = true;

	return result;
}

inline bool isAllDigit(string::iterator left,string::iterator right)
{
	bool result = true;

	while(left != right)
	{
		result = result && isdigit(*left);
		++left;
	}
	result = result && isdigit(*right);

	return result;
}

inline string::iterator findTheLowest(string::iterator begin,string::iterator end)
{
	string::iterator iter = end;
	string::iterator result;
	char theOperator = '#';

	while(iter != begin)
	{
		if(*iter == ')')
			iter = findLeft(iter);
		if(iter == begin)
			break;
		if(isOperator(*iter))
		{
			if(lower(*iter,theOperator))
			{
				theOperator = *iter;
				result = iter;
			}
		}
		--iter;
	}

	return result;
}

inline Item *makeAnItem(string::iterator begin,string::iterator end)
{
	Item *result;

	if(isAllDigit(begin,end))
		result = new Digit;
	else
		result = new Formula;

	result->setValue(begin,end);

	return result;
}

void Formula::setValue(string::iterator begin,string::iterator end)
{
	while(*end == '\0')
		--end;

	while(*end == ')' && begin == findLeft(end))
	{++begin;--end;}

	string::iterator iter = findTheLowest(begin,end);
	theOperator = *iter;

	leftItem = makeAnItem(begin,iter - 1);
	rightItem = makeAnItem(iter + 1,end);
}
