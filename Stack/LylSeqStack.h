#include"lylList.h"
template<class T>

class LylSeqStack
{
private:
	lylList<T> list;    //ʹ��˳���洢ջԪ��

public:
	//��Ĭ�Ϲ��캯������������
	bool empty() {
		return this->list.empty();
	}

	void push(T x) {
		this->list.insert(x);
	}

	T pop(){
		if(!empty())
			this->list.remove(list.length - 1);
		throw logic_error("��ջ������ִ�г�ջ����");
	}

	T get() {   //����ջ��Ԫ��
		if(!empty())
			return this->list[list.length - 1];
		throw logic_error("��ջ�����ܻ��ջ��Ԫ��");
	}
};
