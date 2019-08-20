#pragma once

#include "Scanner.h"
#include "Number.h"
#include "cctype"

namespace Interpreter {
	struct Atom : public Scanner {
		static Calculator* make(Iter& iter) {
			int number = 0;
			while (isdigit(*iter)) {
				number = (number * 10) + int((*iter) & 0x0f);
				++iter;
			}
			return new Number(number);
		}
	};
}