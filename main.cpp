#include <iostream>

#include "Calculator.h"
#include "Expression.h"

using namespace std;
using namespace Interpreter;

int main() {
	Str str = "(1+2)*3";
	str += '\0';
	Iter iter = str.begin();
	Calculator* c = nullptr;
	try {
		c = Expression::make(iter);
	}catch (GrammerErr& Err) {
		cerr << Err.what() << endl;
	}

	try {
		if (c != nullptr) {
			cout << c->value() << endl;
		}
	}catch (CalculateException& Err) {
		cerr << Err.what() << endl;
	}
	
	delete c;
	return 0;
}