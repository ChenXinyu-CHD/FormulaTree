#ifndef PRIORITY_H
#define PRIORITY_H

#include "Cons.h"

#include "Operators.h"
#include "Scanner.h"

namespace Interpreter { 
	template<
		typename OperatorType,
		typename NextOperator
	>struct PriorityNode : Scanner {
		static AbstractOperator* make(Iter& iter) {
			if (*iter == OperatorType::name) {
				++iter;
				return new OperatorType;
			}
			else {
				return NextOperator::make(iter);
			}
		}
	};

	template<typename OperatorType>
	struct PriorityNode<OperatorType, void> : Scanner {
		static AbstractOperator* make(Iter& iter) {
			if (*iter == OperatorType::name) {
				++iter;
				return new OperatorType;
			}
			else {
				return nullptr;
			}
		}
	};

	template<typename OperatorList>
	using Priority = typename tools::MakeList<
		OperatorList,
		PriorityNode
	>::type;
}

#endif