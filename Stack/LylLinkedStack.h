#include "lylSinglyList.h"

// ��ʽջ
// �涨���ڱ�ͷ��ջ
template<class T>
class LylLinkedStack
{
private:
	lylSinglyList<T> list;

public:
	bool empty() 
	{
		return this->list.empty();
	}
	void push(T x)
	{
		this->list.insert(0,x);
	}
	T pop()
	{
		if(!empty())
			return this->list.remove(0);
		throw logic_error("The stack is empty!");
	}
	T get() 
	{
		if (!empty())
			return this->list.search(list.count());
		throw logic_error("The stack is empty!");
	}
};