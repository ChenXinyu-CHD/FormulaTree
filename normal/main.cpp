#include <string>
#include <iostream>

#include "Expression.h"

using namespace std;

bool input(string& str) {
	cout << "�������������ʽ(����exit�˳�)��";
	return getline(cin, str) && str != "exit";
}

void show_tokens(const string& str) {
	Size begin = 0;
	auto token = lex(str, begin);
	while (token.type != Token::End) {
		switch (token.type) {
		case (Token::Number):
			cout << "Number����ʼλ�ã�" << token.begin 
				<< "��ֹλ�ã�" << token.end
				<< "ֵ��" << token.number << endl;
			break;
		case (Token::Bracket):
			cout << "Bracket����ʼλ�ã�" << token.begin
				<< "��ֹλ�ã�" << token.end
				<< "ֵ��" << token.ch << endl;
			break;
		case (Token::Operator):
			cout << "Operator����ʼλ�ã�" << token.begin
				<< "��ֹλ�ã�" << token.end
				<< "ֵ��" << token.ch << endl;
			break;
		case (Token::Error):
			cout << "Error����ʼλ�ã�" << token.begin
				<< "��ֹλ�ã�" << token.end
				<< "ֵ��" << token.ch << endl;
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
		cout << "�ʷ��Ǻ������£�" << endl;
		show_tokens(str);
		try {
			auto exp = parse(str);
			cout << endl << "�����﷨�����£�" << endl;
			show_expr(exp, 0);
			auto code = generate(exp);

			cout << endl << "�м��������(����ַ��)��" << endl;
			for (auto& line : code) {
				cout << line << endl;
			}

			cout << endl << "��������" << eval(exp) << endl;
		} catch (exception e){
			cerr << e.what() << endl;
		}
	}

	return 0;
}