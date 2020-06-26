#include <string>
#include <iostream>

#include "Expression.h"

using namespace std;

bool input(string& str) {
	cout << "请输入算数表达式(输入exit退出)：";
	return getline(cin, str) && str != "exit";
}

void show_tokens(const string& str) {
	Size begin = 0;
	auto token = lex(str, begin);
	while (token.type != Token::End) {
		switch (token.type) {
		case (Token::Number):
			cout << "Number，起始位置：" << token.begin 
				<< "终止位置：" << token.end
				<< "值：" << token.number << endl;
			break;
		case (Token::Bracket):
			cout << "Bracket，起始位置：" << token.begin
				<< "终止位置：" << token.end
				<< "值：" << token.ch << endl;
			break;
		case (Token::Operator):
			cout << "Operator，起始位置：" << token.begin
				<< "终止位置：" << token.end
				<< "值：" << token.ch << endl;
			break;
		case (Token::Error):
			cout << "Error，起始位置：" << token.begin
				<< "终止位置：" << token.end
				<< "值：" << token.ch << endl;
			break;
		}
		begin = token.end;
		token = lex(str, begin);
	}
}

int show_expr(ExpPtr exp, int depth) {
	for (int i = 0; i < depth; ++i) {
		cout << "\t|";
	}
	if (exp->is_leaf()) {
		auto leaf = reinterpret_pointer_cast<ExpLeaf>(exp);
		cout << "-Leaf number:" << leaf->number << endl;
		return depth - 1;
	} else {
		auto node = reinterpret_pointer_cast<ExpNode>(exp);
		cout << "-Node op:" << node->op << endl;
		show_expr(node->lhs, depth + 1);
		show_expr(node->rhs, depth + 1);

		return depth - 1;
	}
}

int main() {
	string str;
	while (input(str)) {
		cout << "词法记号流如下：" << endl;
		show_tokens(str);
		try {
			auto exp = parse(str);
			cout << endl << "抽象语法树如下：" << endl;
			show_expr(exp, 0);
			auto code = generate(exp);

			cout << endl << "中间代码如下(三地址码)：" << endl;
			for (auto& line : code) {
				cout << line << endl;
			}

			cout << endl << "运算结果：" << eval(exp) << endl;
		} catch (exception e){
			cerr << e.what() << endl;
		}
	}

	return 0;
}