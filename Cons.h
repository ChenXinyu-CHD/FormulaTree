#ifndef CONS_H
#define CONS_H

namespace tools {
	template<
		typename T1,
		typename T2
	>struct Cons {
		using type = Cons<T1, T2>;
	};

	template<
		typename T
	>struct Car {
		using type = void;
	};

	template<
		typename T
	>struct Cdr {
		using type = void;
	};

	template<
		typename T1,
		typename T2
	>struct Car<Cons<T1, T2>> {
		using type = T1;
	};

	template<
		typename T1,
		typename T2
	>struct Cdr<Cons<T1, T2>> {
		using type = T2;
	};

	template<typename... args>
	struct List {
		using type = void;
	};

	template<typename arg, typename ...args>
	struct List<arg, args...> {
		using type = Cons<
			arg,
			typename List<args...>::type
		>;
	}; 

	//此方法名称有问题，它实质上是将List转化为链表的“函数”
	//Scanner子类的实现大多依赖此“函数”
	template<
		typename L,
		template<typename, typename>typename F
	>struct MakeList {
		using type = F<
			typename tools::Car<L>::type,
			typename MakeList<
				typename tools::Cdr<L>::type, F
			>::type
		>;
	};

	template<
		typename T,
		template<typename, typename>typename F
	>struct MakeList <Cons<T, void>, F>{
		using type = F<T, void>;
	};
}

#endif
