#ifndef NUMBER_H
#define NUMBER_H

#include "Scanner.h"
#include "Calculator.h"

namespace Interpreter {
	class Number : public Calculator {
	private:
		int number;
	public:
		Number(int value) : number(value){
			//Nothing to do;
		}
		int value() {
			return number;
		}
	};

	struct NumberMaker : Scanner {
		struct NotNumber : public ScannerException {
			virtual const char* what() {
				return "Not a Number!";
			}
		};
		static Calculator* make(Iter& iter) {
			Number* result = nullptr;
			if (!isdigit(*iter)) {
				throw NotNumber();
			}
			else {
				int number = 0;
				while (isdigit(*iter)) {
					number = (number * 10) + int((*iter) & 0x0f);
					++iter;
				}
				result = new Number(number);
			}
			return result;
		}
	};
}

#endif
