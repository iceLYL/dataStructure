#include "lylNode.h"
#include <stdio.h>
#include <iostream>
using namespace std;

template <class T>
class lylSinglyList 
{
public:
	lylNode<T> *head;      //头指针

	/*------构造函数-------*/
	lylSinglyList();                               //构造空单链表
	lylSinglyList(T values[], int n);       //构造单链表，由values数组提供元素
	~lylSinglyList();
	/*------end-------*/

	bool empty();                                //判断链表是否为空
	int count();                                    //返回单链表长度
	T get(int i);                                 //返回第i（≥0）个元素的引用
	virtual void set(int i, T x);              //设置第i（≥0）个元素为x
	friend ostream& operator<<<>(ostream&, lylSinglyList<T>&);
	lylNode<T>* insert(int i, T x);          //插入x作为第i个结点，返回结点地址                      
	virtual lylNode<T>* insert(T x);       //在单链表最后插入元素x

	T remove(int i);                              //清除第i个结点，并返回被删除元素
	void removeAll();                           //清空单链表
	int searchIndex(T key);                           //查找key，返回下标
	lylNode<T>* search(T key);           //顺序查找首次出现的关键字为key元素，返回结点地址；
	                                                       //若未找到，返回NULL。 
	                                                        //T必须重载运算符“==”
	void insertUnrepeatable(T x);          //尾插入不重复元素
	virtual void removeFirst(T key);       //删除首次出现的关键字为key元素

	/*重载运算符*/
	bool operator==(lylSinglyList<T> &list);   //比较两条单链表是否相等
	bool operator!=(lylSinglyList<T> &list);
	lylSinglyList(lylSinglyList<T> &list);
	lylSinglyList<T> &operator=(lylSinglyList<T> &list);   //深拷贝
	virtual void operator+=(lylSinglyList<T> &list);           //将list连接在当前单链表之后
	/*end*/
};

template <class T>
lylSinglyList<T>::lylSinglyList()
{
	this->head = new lylNode<T>();    //创建head头结点，用lylNode()无参构造函数
}

template<class T>
lylSinglyList<T>::lylSinglyList(T values[], int n)
{
	this->head = new lylNode<T>();
	lylNode<T> *p = this->head;  //p指向head
	for (int i = 0; i < n; i++)
	{
		p->next = new lylNode<T>(values[i]);
		p = p->next;    //p指向新开辟的结点，也是这个链表的尾结点
	}
}

template <class T>
lylSinglyList<T>::~lylSinglyList()  ///////////////////////////////////////////////////与书不同
{
	lylNode<T> *rear = head;
	while (rear->next != NULL)    //rear遍历到整个链的尾部
	{
		rear = rear->next;
	}
	head = rear;     //头=尾，链表清空
	delete this->head;
}

template <class T>
bool lylSinglyList<T>::empty()                               //判断链表是否为空  1:空
{
	if (NULL != this->head->next)
		return 0;
	else
		return 1;
}

template<class T>
int lylSinglyList<T>::count()                                   //返回单链表长度, 头结点不算
{
	lylNode<T> *p = this->head;
	int count = 0;
	while (p->next != NULL)
	{
		p = p->next;
		count++;		
	}
	return count;
}

template<class T>
T lylSinglyList<T>::get(int i)                                 //返回第i（≥0）个元素的引用
{
	//////////////////////////////////////////////////////返回T&？？？？？？？？？？

	lylNode<T> *p = this->head;
	for (int j = 0; j < i + 1 && p->next!=NULL ; j++)   //从0开始
	{
		p = p->next;
	}
	if(i>=0&&p!=NULL)
		return p->data;
	throw out_of_range("i超出范围！");
}

template<class T>
void lylSinglyList<T>::set(int i, T x)              //设置第i（≥0）个元素为x，虚
{
	lylNode<T> *p = this->head;
	for (int j = 0; j < i + 1; j++)
	{
		p = p->next;
	}
	p->data = x;
}

template<class T>
ostream& operator<<<>(ostream& out, lylSinglyList<T>& list)
{
	lylNode<T> *p = list.head;
	while (p->next != NULL)
	{
		p = p->next;
		cout << " " << p->data;
	}
	cout << endl;
	return out;
}

template<class T>
lylNode<T>* lylSinglyList<T>::insert(int i, T x)  //i从0开始，返回的是head后面的东西，所以循环i次；即i=0是head后面的第一个
{
	//insert容错:若i<0，插在head后面
	lylNode<T> *p = this->head;
	for (int j = 0; j < i && p->next!=NULL; j++)
	{
		p = p->next;
	}
//	lylNode<T> *q = new lylNode<T>(x);
//	q->next = p->next;            
// 这两句可以用下面一句表示
	lylNode<T> *q = new lylNode<T>(x, p->next);
	p->next = q;
	return p->next;
}

template<class T>
lylNode<T>* lylSinglyList<T>::insert(T x)       //在单链表最后插入元素x
{
	lylNode<T> *p = this->head;
	while (p->next != NULL)
		p = p->next;
	lylNode<T> *rear = new lylNode<T>(x);
	p->next = rear;
	return p->next;
}

/*重载运算符*/
template<class T>
bool lylSinglyList<T>::operator==(lylSinglyList<T> &list)   //比较两条单链表是否相等
{
	lylNode<T> *p_this = this->head;
	lylNode<T> *p_list = list.head;
	int this_count = 0, list_count = 0;
	while (p_this->next != NULL && p_list != NULL)
	{
		this_count++; list_count++;
		p_this = p_this->next;
		p_list = p_list->next;
		if (p_this->data != p_list->data)         //情况1：内容不同
			return 0;
	}
	if (p_this->next != NULL)                       //情况2：长度不同
	{
		this_count++;
		p_this = p_this->next;
	}
	if (p_list->next != NULL)
	{
		list_count++;
		p_list = p_list->next;
	}
	if (this_count == list_count)
		return 1;
	else
		return 0;
}

template<class T>
T lylSinglyList<T>::remove(int i)                              //清除第i (头结点不算，i从0开始) 个结点，并返回被删除元素
{
	lylNode<T> *p = this->head;
	lylNode<T> *q;
	for (int j = 0; j < i ; j++)          //删除第i个结点，p是第i-1个结点
	{
		p = p->next;
	}
	q = p->next;
	p->next = p->next->next;
	return q->data;
}

template<class T>
void lylSinglyList<T>::removeAll()                           //清空单链表
{
	this->head->next = NULL;
}

template<class T>
lylNode<T>* lylSinglyList<T>::search(T key)          //顺序查找首次出现的关键字为key元素，返回结点地址；
									 //若未找到，返回NULL。 
									 //T必须重载运算符“==”
{
	lylNode<T> *p = this->head;
	int flag = 0;
	while (p->next != NULL)
	{
		p = p->next;
		if (p->data == key)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 1)
		return p;
	else
		return NULL;
}

template<class T>
int lylSinglyList<T>::searchIndex(T key)          //顺序查找首次出现的关键字为key元素，返回下标；
{
	lylNode<T> *p = this->head;
	int count = -1;
	int flag = 0;
	while (p->next != NULL)
	{
		p = p->next;
		count++;
		if (p->data == key)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 1)
		return count;
	else
		return NULL;
}

template<class T>
void lylSinglyList<T>::insertUnrepeatable(T x)          //尾插入不重复元素
{                                                       //重复：不插；非重复：查。并打印结果
	if (search(x))  //search返回整数，说明存在重复的
		cout << "已经存在"<<x << endl;
	else
	{
		lylNode<T> *p = this->head;
		while (p->next != NULL)
			p = p->next;
		lylNode<T> *add = new lylNode<T>(x);
		p->next = add;
		cout << x << "插入成功" << endl;
	}
}

template<class T>
void lylSinglyList<T>::removeFirst(T key)      //删除首次出现的关键字为key元素
{
	lylNode<T> *p = search(key);
	lylNode<T> *p_remove = this->head;
	while (p_remove->next != p)
		p_remove = p_remove->next;
	p_remove->next = p->next;            //or : p_remove->next = p_remove->next->next;
}

template<class T>
bool lylSinglyList<T>::operator!=(lylSinglyList<T> &list)            //用==改
{
	lylNode<T> *p_this = this->head;
	lylNode<T> *p_list = list.head;
	int this_count = 0, list_count = 0;
	while (p_this->next != NULL && p_list != NULL)
	{
		this_count++; list_count++;
		p_this = p_this->next;
		p_list = p_list->next;
		if (p_this->data != p_list->data)         //情况1：内容不同
			return 1;
	}
	if (p_this->next != NULL)                       //情况2：长度不同
	{
		this_count++;
		p_this = p_this->next;
	}
	if (p_list->next != NULL)
	{
		list_count++;
		p_list = p_list->next;
	}
	if (this_count == list_count)
		return 0;
	else
		return 1;
}

template<class T>
lylSinglyList<T>::lylSinglyList(lylSinglyList<T> &list)
{
	//深拷贝
	lylNode<T> *p = new lylNode<T>(),*q=list.head;
	this->head = new lylNode<T>();
	p = this->head;
	while (q->next != NULL)
	{
		p->next=new lylNode<T>();
		p = p->next;
		q = q->next;
		p->data = q->data;
	}
	
}

template<class T>
lylSinglyList<T>& lylSinglyList<T>::operator=(lylSinglyList<T> &list)   //深拷贝
{
	//深拷贝
	lylNode<T> *p = new lylNode<T>(), *q = list.head;
	this->head = new lylNode<T>();
	p = this->head;
	while (q->next != NULL)
	{
		p->next = new lylNode<T>();
		p = p->next;
		q = q->next;
		p->data = q->data;
	}
	p = this->head;
	return &p;
}

template<class T>
void lylSinglyList<T>::operator+=(lylSinglyList<T> &list)           //将list连接在当前单链表之后
{
	lylNode<T> *p = this->head,*q=list.head;
	while (p->next != NULL)
		p = p->next;
	while (q->next != NULL)
	{
		q = q->next;
		lylNode<T> *add = new lylNode<T>(q->data);
		p->next = add;
		p = p->next;
	}
}