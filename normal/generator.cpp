#include "Expression.h"

#include <sstream>

using namespace std;

namespace {
	string generate(ExpPtr exp, vector<string>& code) {
		if (exp->is_leaf()) {
			auto leaf = reinterpret_pointer_cast<ExpLeaf>(exp);
			return to_string(uint64_t(leaf->number));
		} else {
			auto node = reinterpret_pointer_cast<ExpNode>(exp);
			auto lhs = generate(node->lhs, code);
			auto rhs = generate(node->rhs, code);

			ostringstream sout;
			sout << 'x' << code.size();
			auto result = sout.str();

			sout << '=' << lhs << node->op << rhs;
			code.push_back(sout.str());

			return result;
		}
	}
}

vector<string> generate(ExpPtr exp) {
	vector<string> result;
	generate(exp, result);

	return result;
}
