#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <cstdint>

using Size = std::string::size_type;
using Number = double;

struct Token final {
	Size begin = 0;
	Size end = 0;

	union {
		Number number = 0;
		char ch;
	};

	enum {
		End, Error, Number, Operator, Bracket
	} type = Error;
};

Token lex(const std::string& str, Size begin);

#endif