#ifndef OPERATORS_H
#define OPERATORS_H

#include "Calculator.h"

namespace Interpreter {
	class AbstractOperator : public Calculator {
	public:
		Calculator* lhs = nullptr;
		Calculator* rhs = nullptr;

		virtual ~AbstractOperator() {
			if (nullptr != lhs) {
				delete lhs;
			}
			if (nullptr != rhs) {
				delete rhs;
			}
		}
		int value() {
			int result = 0;
			if (lhs != nullptr && rhs != nullptr) {
				result = compute();
			}else {
				throwError();
			}
			return result;
		}
	protected:
		virtual inline int compute() = 0;
		virtual inline void throwError() = 0;
	};

	template<char oper>
	class Operator : public AbstractOperator {
	private:
		inline int compute() {
			return 0;
		}
		inline void throwError() {
			throw MissingOperand();
		}
	public:
		struct MissingOperand : CalculateException {
			const char* what() {
				const static Str ErrMsg = Str("Operator") + oper + Str(": missing operand.");
				return ErrMsg.c_str();
			}
		};
		//��������ʱȷ����������
		static const char name = oper;
	};

	template<>
	int Operator<'+'>::compute() {
		return lhs->value() + rhs->value();
	}
	template<>
	int Operator<'-'>::compute() {
		return lhs->value() - rhs->value();
	}
	template<>
	int Operator<'*'>::compute() {
		return lhs->value() * rhs->value();
	}
	template<>
	int Operator<'/'>::compute() {
		return lhs->value() / rhs->value();
	}
	template<>
	int Operator<'%'>::compute() {
		return lhs->value() % rhs->value();
	}
}

#endif