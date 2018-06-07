#include <stdio.h>
#include <iostream>
using namespace std;
#include <exception>

template <class T> //类模板，用T代替其他可能出现的数据类型
class lylList 
{
	//顺序线性表需要三个成员变量：
	//1.存储空间的起始位置：*element ---动态数组, 指向数组的起始地址
	//2.线性表的最大容量：MaxSize
	//3.当前长度：length  即元素个数
  protected:
		T *element;
		int MaxSize;
		int length;

	public:
		void InitList(T value[], int n); //初始化，value--值，int--个数
		/*-----构造函数、析构函数------*/
		lylList(int MaxSize = 32);  //构造空表，maxsize指定 
		lylList(int MaxSize, T x);    //maxsize个元素，值全为x
		lylList(T value[], int n);
		~lylList();
		/*-------------end-------------*/

		bool empty();   //判断顺序表是否为空
		int count();       //返回顺序表元素个数

		 /*-----运算符重载------*/
		 //重载下标运算符
		T& operator[](int i);    
		//运算符重载
		//C++ 能够使用流提取运算符 >> 和流插入运算符 << 来输入和输出内置的数据类型
		//可以重载流提取运算符和流插入运算符来操作对象等用户自定义的数据类型。
		//需要把运算符重载函数声明为类的友元函数		
		//有模板时用<>
		//定义时的写法：ostream& operator<<<>(ostream& out, lylList<T>&list);    
		friend ostream& operator<<<>(ostream&, lylList<T>&);    
		/*-------------end-------------*/

		void printPrevious();     //反序输出，从后向前
		void insert(int i, T x);     //插入x作为第i个元素
		virtual void insert(T x);  //在顺序表最后插入x
		T remove(int i);             //删除第i个元素，并返回
		void removeAll();
		virtual int search(T key, int start = 0);   //从start开始查找key元素，返回元素序号
		virtual void removeFirst(T key);            //删除首次出现关键字为key元素

		lylList(lylList<T> &list);      //拷贝构造函数
		lylList<T>& operator=(lylList<T> &list);    //重载=赋值运算符，深拷贝
		bool operator==(lylList<T> &list);   //比较两个顺序表对象的值是否相等
		bool operator!=(lylList<T> &list);     //
		void operator+=(lylList<T> &list);    //在*this当前顺序表之后合并并连接list
		lylList<T> operator+(lylList<T> &list);   //返回*this与list合并连接的对象

};

template <class T>
void lylList<T>::InitList(T value[], int n)
{

	lylList(value, n);
}

// 构造函数完成功能：赋值成员变量：
//1.指定MaxSize
//2.指针element，可以作为动态数组来使用（通过下标）；开辟空间new；赋值
//3.赋值length
template <class T>
lylList<T>::lylList(T value[], int n)
{
	this->MaxSize = n * 2;
	this->length = n;
	this->element = new T[this.MaxSize];
	for (int i = 0; i < n; i++)
		this.element[i] = value[i];
}

template <class T>
lylList<T>::lylList(int MaxSize = 32)
{
	this->element = new T[MaxSize];
	this->MaxSize = MaxSize;
	this->length = 0;
}

template <class T>
lylList<T>::lylList(int MaxSize, T x)
{
	this->MaxSize = MaxSize;
	this->element = new T[this->MaxSize];
	this->length = MaxSize;
	for (int i = 0; i < MaxSize; i++)
		this->element[i] = x;
}

//析构函数：用delete释放内存
//释放数组，用delete[]
template <class T>
lylList<T>::~lylList()
{
	delete[]this->element;
}

template <class T>
bool lylList<T>::empty()   //C++中如果值非零就为True,为零就是False
{
	return this->length==0;
}

template <class T>
int lylList<T>::count()
{
	return this->length;
}

template <class T>
T& lylList<T>::operator[](int i)
{
	//注意下标可能会超过范围
	//所以要写判断和容错措施
	//return this->element[i];  不能单写这一个
	if (i >= 0 && i < this->length)
		return this->element[i];
	throw out_of_range("参数i超出范围！");   //c++STL 范围越界异常
}

template <class T>
ostream& operator<<<>(ostream& out, lylList<T>&list)
{
	if (list.length > 0)
	{
		for (int i = 0; i < list.length; i++)
				out <<" "<< list.element[i];
		out << endl;
	}
	return out;
}

template <class T>
void lylList<T>::printPrevious()  //反序输出，从后向前
{
	for (int i = this->length - 1; i >= 0; i--)
		cout <<" "<< this->element[i];
	cout << endl;
}

template <class T>
void lylList<T>::insert(int i, T x)    //插入x作为第i个元素
{
	if (i < 0) i = 1;    //i容错
	if (i > this->length) i = this->length;
	//1.判断容量是否够
	//2.不够，扩容；够，ok
	if (this->length == this->MaxSize)
	{
		this->MaxSize = this->MaxSize * 2;
		T *a = new T[this->length];
		for (int j = 0; j < this->length; j++)
			a[j] = this->element[j];
		this->element = new T[this->MaxSize];
		for (int j = 0; j < this->length; j++)
			this->element[j] = a[j];
	}
	for (int j = this->length - 1; j >= i - 1; j--)    //第i个元素，下标为i-1
		this->element[j + 1] = this->element[j];
	this->element[i - 1] = x;
	this->length++;
}

template <class T>
void lylList<T>::insert(T x)  //在顺序表最后插入x，虚函数
{
	insert(length, x);
}

template <class T>
T lylList<T>::remove(int i)            //删除第i个元素，并返回
{
	
	int a;
	if (i >= 0 && i < this->length)
	{
		a = element[i - 1];
		for (int j = i - 1; j < this->length; j++)    //第i个元素，下标为i-1
		{ 
			this->element[j] = this->element[j + 1];
			this->length--;
			break;
		}
		return a;
	}
/*
	//i从0开始
	int a;
	if (i >= 0 && i < this->length)
	{
		a = element[i];
		for (int j = i ; j < this->length; j++)    //第i个元素，下标为i-1
		{ 
			this->element[j] = this->element[j + 1];
			this->length--;
			break;
		}
		return a;
	}*/
	throw out_of_range("下标i超出顺序表，或不合法！");
}

template <class T>
void lylList<T>::removeAll()
{
	this->length = 0; //删除所有元素，未释放空间
}

template <class T>
int lylList<T>::search(T key, int start = 0)  //从start开始查找key元素，返回元素序号 ;虚
{
	for (int i = start; i < this->length; i++)
		if (this->element[i] == key)
			return i;
	return -1;
}

template <class T>
void lylList<T>::removeFirst(T key)            //删除首次出现关键字为key元素;虚
{

	for (int i = 0; i < this->length; i++)
	{
		if (this->element[i] == key)
		{
			remove(i+1);//remove中是删除第几个，下标从1开始
			break;
		}
	}
}

template <class T>
lylList<T>::lylList(lylList<T> &list)
{	
	this->element = new T[list.MaxSize];
	for (int i = 0; i < list.length; i++)
	{
		this->element[i] = list.element[i];
	}	
	this->length = list.length;
	this->MaxSize = list.MaxSize;
}

template <class T>
lylList<T>& lylList<T>::operator=(lylList<T> &list)    //深拷贝
{
	this->element = new T[list.MaxSize];
	for (int i = 0; i < list.length; i++)
	{
		this->element[i] = list.element[i];
	}
	this->length = list.length;
	this->MaxSize = list.MaxSize;
	return this;
}

template <class T>
bool lylList<T>::operator==(lylList<T> &list)   //比较两个顺序表对象的值是否相等
{
	int flag = 0;
	if (this->length == list.length)
	{
		for (int i = 0; i < this->length; i++)
		{
			if (this->element[i] == list.element[i])
			{
				flag++;
				continue;
			}
			else
				break;
		}
		if (flag == this->length)
			return 1;
	}
	return 0;
}

template <class T>
bool lylList<T>::operator!=(lylList<T> &list)
{
	int flag = 0;
	if (this->length == list.length)
	{
		for (int i = 0; i < this->length; i++)
		{
			if (this->element[i] == list.element[i])
			{
				flag++;
				continue;
			}
			else
				break;
		}
		if (flag == this->length)
			return 0;
	}
	return 1;
}

template <class T>
void lylList<T>::operator+=(lylList<T> &list)   //在*this当前顺序表之后合并并连接list
{
	if((this->length+list.length)>=this->MaxSize)
	{
		this->MaxSize = (this->MaxSize + list.MaxSize) * 2;   //扩容
		T *a = new T[this->length];
		for (int i = 0; i < this->length; i++)
			a[i] = this->element[i];
		this->element = new T[this->MaxSize];
		for (int i = 0; i < this->length; i++)
			this->element[i]=a[i];
	}
	for (int i = this->length; i <this->length+list.length; i++)
		this->element[i] = list.element[i-this->length];
	this->length = this->length + list.length;
}

template <class T>
lylList<T> lylList<T>::operator+(lylList<T> &list)  //返回*this与list合并连接的对象
{	
	lylList a(this->length+list.length);
	a.length = a.MaxSize;
	for (int i = 0; i < this->length; i++)
		a.element[i] = this->element[i];
	for (int i = this->length; i <this->length + list.length; i++)
		a.element[i] = list.element[i - this->length];
	return a;
}