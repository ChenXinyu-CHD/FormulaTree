#include "Expression.h"

#include <exception>
#include <sstream>

using namespace std;

namespace {
    /*
    ʹ�õ��﷨��
    exp -> add_sub
    add_sub -> add_sub + mul_div | add_sub - mul_div | mul_div
    mul_div -> mul_div * atom | mul_div / atom | atom
    atom -> ( add_sub ) | number
    ������ݹ�֮��nil��������ԣ���
    exp -> add_sub
    add_sub -> mul_div add_sub_
    add_sub_ -> + mul_div add_sub_ | - mul_div add_sub_ | nil
    mul_div -> atom mul_div_
    mul_div_ -> * atom mul_div_ | / atom mul_div_ | nil
    atom -> ( add_sub ) | number
    */

    ExpPtr add_sub(const std::string& str, Size& pos);
    ExpPtr mul_div(const std::string& str, Size& pos);
    ExpPtr atom(const std::string& str, Size& pos);

    ExpPtr add_sub(const std::string& str, Size& pos) {
        auto result = mul_div(str, pos);
        auto token = lex(str, pos);
        while (
            token.type == Token::Operator &&
            (token.ch == '+' || token.ch == '-')
        ) {
            pos = token.end;
            auto new_result = make_shared<ExpNode>();
            new_result->op = token.ch;
            new_result->lhs = result;
            new_result->rhs = mul_div(str, pos);
            result = new_result;
            token = lex(str, pos);
        }
        return result;
    }
    ExpPtr mul_div(const std::string& str, Size& pos) {
        auto result = atom(str, pos);
        auto token = lex(str, pos);
        while (
            token.type == Token::Operator &&
            (token.ch == '*' || token.ch == '/')
        ) {
            pos = token.end;
            auto new_result = make_shared<ExpNode>();
            new_result->op = token.ch;
            new_result->lhs = result;
            new_result->rhs = atom(str, pos);
            result = new_result;
            token = lex(str, pos);
        }
        return result;
    }
    ExpPtr atom(const std::string& str, Size& pos) {
        auto token = lex(str, pos);
        if (token.type == Token::Number) {
            pos = token.end;
            auto result = make_shared<ExpLeaf>();
            result->number = token.number;
            return result;
        } else if (token.type == Token::Bracket && token.ch == '(') {
            pos = token.end;
            auto result = add_sub(str, pos);
            token = lex(str, pos);
            if (token.type == Token::Bracket && token.ch == ')') {
                pos = token.end;
                return result;
            } else {
                ostringstream sout;
                sout << "λ��" << token.begin << "�����Ų�ƥ�䣺" << str.substr(token.begin);
                throw exception(sout.str().c_str());
            }
        } else if (token.type == Token::End){
            ostringstream sout;
            sout << "λ��" <<token.begin << "��ȱ���Ҳ�����";
            throw exception(sout.str().c_str());
        } else {
            ostringstream sout;
            sout << "λ��" << token.begin << "�����޷�ʶ����ַ�����" << str.substr(token.begin);
            throw exception(sout.str().c_str());
        }
    }
}

ExpPtr parse(const std::string& str) {
    if (str.empty()) {
        throw exception("���ʽΪ��");
    } else {
        Size begin = 0;
        auto result = add_sub(str, begin);
        auto token = lex(str, begin);
        if (token.type != Token::End) {
            ostringstream sout;
            sout << "λ��" << begin << "�����޷�ʶ����ַ�����" << str.substr(begin);
            throw exception(sout.str().c_str());
        } else {
            return result;
        }
    }
}
