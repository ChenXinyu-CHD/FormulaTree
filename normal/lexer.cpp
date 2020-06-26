#include "Token.h"

#include <cctype>

using namespace std;

namespace {
    void skipBlank(const string& str, Size& begin) {
        for (Size& i = begin; i < str.size(); ++i) {
            if (!isspace(str[i])) {
                return;
            }
        }
    }

    Number getNum(const string& str, Size& pos) {
        Number result = 0;
        for (Size& i = pos; i < str.size() && isdigit(str[i]); ++i) {
            result = (result * 10) + (str[i] & 0x0f);
        }
        return result;
    }

    bool is_bracket(char ch) { return ch == '(' || ch == ')'; }
    bool is_operator(char ch) { return ch == '+' || ch == '-' || ch == '*' || ch == '/'; }
}

Token lex(const string& str, Size pos) {
    Token result;
    skipBlank(str, pos);
    result.begin = pos;
    if (pos < str.size()) {
        if (isdigit(str[pos])) {
            result.type = Token::Number;
            result.number = getNum(str, pos);
        } else if (is_bracket(str[pos])){
            result.type = Token::Bracket;
            result.ch = str[pos];
            ++pos;
        } else if (is_operator(str[pos])){
            result.type = Token::Operator;
            result.ch = str[pos];
            ++pos;
        } else {
            result.type = Token::Error;
            result.ch = str[pos];
            ++pos;
        }
    } else {
        result.type = Token::End;
        result.ch = '\0';
    }
    result.end = pos;
    return result;
}
