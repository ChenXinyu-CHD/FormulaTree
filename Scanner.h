#pragma once

#include <string>
#include <exception>

#include "Calculator.h"

namespace Interpreter {
	//Scanner及其所有子类都被用于扫描字符串（代码）
	//同时它们也是Calculator类及其子类的建造者
	//Scanner虽然具有继承树
	//但实际上它的子类并不重用父类的任何代码
	//同时它本身也不依赖运行时多态
	//它的继承体系只是在语义上标识其身份，在语法上是多余的。
	//Scanner类及其子类只具有static属性和方法，它们不能用于构造对象
	struct Scanner {
		static Calculator* make(Iter& iter) {
			return nullptr;
		}
	};
	//当前Scanner无法解析，但不清楚是否其它Scanner可否解析时抛出
	struct ScannerException : public std::exception {
		virtual const char* what() {
			return "Unresolved statement!";
		}
	};
	//可以直接确定表达式出错时抛出
	struct GrammerErr : public std::exception {
		virtual const char* what() {
			return "Unresolved statement!";
		}
	};
}