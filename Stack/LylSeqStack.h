#include"lylList.h"
template<class T>

class LylSeqStack
{
private:
	lylList<T> list;    //使用顺序表存储栈元素

public:
	//有默认构造函数和析构函数
	bool empty() {
		return this->list.empty();
	}

	void push(T x) {
		this->list.insert(x);
	}

	T pop(){
		if(!empty())
			this->list.remove(list.length - 1);
		throw logic_error("空栈，不能执行出栈操作");
	}

	T get() {   //返回栈顶元素
		if(!empty())
			return this->list[list.length - 1];
		throw logic_error("空栈，不能获得栈顶元素");
	}
};
