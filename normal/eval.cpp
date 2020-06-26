#include "Expression.h"

using namespace std;

Number eval(ExpPtr exp) {
	if (exp->is_leaf()) {
		auto leaf = reinterpret_pointer_cast<ExpLeaf>(exp);
		return leaf->number;
	} else {
		auto node = reinterpret_pointer_cast<ExpNode>(exp);
		auto lhs = eval(node->lhs);
		auto rhs = eval(node->rhs);

		switch (node->op) {
			case('+'): return lhs + rhs;
			case('-'): return lhs - rhs;
			case('*'): return lhs * rhs;
			case('/'): return lhs / rhs;
			default: return 0;	// 实际根本不可能执行此句
		}
	}
}