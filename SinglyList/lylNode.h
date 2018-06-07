#include<stdio.h>
#include<iostream>
using namespace std;

template <class T>
class lylNode 
{
public:
	T data;
	lylNode<T> *next;

	lylNode()      //构造结点，data域未初始化
	{
		this->next = NULL;
	}

	lylNode(T data, lylNode<T> *next=NULL)      //data赋值；next赋值，默认为NULL
	{
		this->data = data;
		this->next = next;
	}
};
