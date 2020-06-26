#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>
#include <vector>

#include "Token.h"

struct Expression {
	virtual bool is_leaf() const noexcept = 0;
	virtual ~Expression() = default;
};

using ExpPtr = std::shared_ptr<Expression>;

struct ExpNode final : public Expression {
	bool is_leaf() const noexcept override {
		return false;
	}

	ExpPtr lhs;
	ExpPtr rhs;
	char op = '\0';
};

using NodePtr = std::shared_ptr<ExpNode>;

struct ExpLeaf final : public Expression {
	bool is_leaf() const noexcept override {
		return true;
	}

	Number number = 0;
};

using LeafPtr = std::shared_ptr<ExpLeaf>;

ExpPtr parse(const std::string& str);
std::vector<std::string> generate(ExpPtr exp);
Number eval(ExpPtr exp);

#endif