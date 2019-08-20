#pragma once

#include "Cons.h"
#include "Priority.h"
#include "Number.h"

namespace Interpreter {
	struct Expression : Scanner {
		static Calculator* make(Iter& iter);
	};

	struct BarketExpression : Scanner {
		struct NotBarket : public ScannerException {
			virtual const char* what() {
				return "There's no barcket";
			}
		};
		struct BarcketNotMatch : public GrammerErr {
			virtual const char* what() {
				return "Barket do not match";
			}
		};
		static Calculator* make(Iter& iter) {
			Calculator* result = nullptr;
			if (*iter != '(') {
				throw NotBarket();
			}
			else {
				++iter;
				result = Expression::make(iter);
				if (*iter != ')') {
					throw BarcketNotMatch();
				}
				else {
					++iter;
				}
			}
			return result;
		}
	};

	template<
		typename Type,
		typename Next
	>struct AtomNode {
		static Calculator* make(Iter& iter) {
			Calculator* result = nullptr;
			try {
				result = Type::make(iter);
			}
			catch(ScannerException &){
				result = Next::make(iter);
			}
			return result;
		}
	};

	template<
		typename Type
	>struct AtomNode<Type, void> {
		static Calculator* make(Iter& iter) {
			Calculator* result = nullptr;
			try {
				result = Type::make(iter);
			} catch (ScannerException& Err) {
				std::cerr << Err.what() << std::endl;
				throw GrammerErr();
			}
			return result;
		}
	};

	using Atom =  tools::MakeList <
		tools::List<BarketExpression, NumberMaker>::type,
		AtomNode
	>::type;

	template<
		typename PriorityType,
		typename NextPriority
	>struct ExpressionNode {
		static Calculator* make(Iter& iter) {
			Calculator* lhs = NextPriority::make(iter);
			AbstractOperator* oper = PriorityType::make(iter);
			while (oper != nullptr) {
				oper->lhs = lhs;
				oper->rhs = NextPriority::make(iter);
				lhs = oper;
				oper = PriorityType::make(iter);
			}
			return lhs;
		}
	};

	template<typename PriorityType>
	struct ExpressionNode<PriorityType, void> {
		static Calculator* make(Iter& iter) {
			Calculator* lhs = Atom::make(iter);
			AbstractOperator* oper = PriorityType::make(iter);
			while (oper != nullptr) {
				oper->lhs = lhs;
				oper->rhs = Atom::make(iter);
				lhs = oper;
				oper = PriorityType::make(iter);
			}
			return lhs;
		}
	};

	using PriorityList = tools::List<
		Priority<
			tools::List<Operator<'+'>, Operator<'-'>>::type
		>,
		Priority<
			tools::List<Operator<'*'>, Operator<'/'>, Operator<'%'>>::type
		>
	>::type;

	using _Expression = tools::MakeList<
		PriorityList,
		ExpressionNode
	>::type;

	Calculator* Expression::make(Iter& iter) {
		return _Expression::make(iter);
	}
}