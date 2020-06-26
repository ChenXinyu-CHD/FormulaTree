#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <exception>

namespace Interpreter {
	using Str = std::string;
	using Iter = Str::const_iterator;

	class Calculator {
	public:
		virtual int value() = 0;
	};

	struct CalculateException : public std::exception {
		virtual const char* what() {
			return "Can not calculate this expression!";
		}
	};
}

#endif
