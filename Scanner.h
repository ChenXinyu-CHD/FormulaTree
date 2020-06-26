#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <exception>

#include "Calculator.h"

namespace Interpreter {
	//Scanner�����������඼������ɨ���ַ��������룩
	//ͬʱ����Ҳ��Calculator�༰������Ľ�����
	//Scanner��Ȼ���м̳���
	//��ʵ�����������ಢ�����ø�����κδ���
	//ͬʱ������Ҳ����������ʱ��̬
	//���ļ̳���ϵֻ���������ϱ�ʶ�����ݣ����﷨���Ƕ���ġ�
	//Scanner�༰������ֻ����static���Ժͷ��������ǲ������ڹ������
	struct Scanner {
		static Calculator* make(Iter& iter) {
			return nullptr;
		}
	};
	//��ǰScanner�޷���������������Ƿ�����Scanner�ɷ����ʱ�׳�
	struct ScannerException : public std::exception {
		virtual const char* what() {
			return "Unresolved statement!";
		}
	};
	//����ֱ��ȷ������ʽ����ʱ�׳�
	struct GrammerErr : public std::exception {
		virtual const char* what() {
			return "Unresolved statement!";
		}
	};
}

#endif