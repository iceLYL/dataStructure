#include<stdio.h>
#include<iostream>
using namespace std;

template <class T>
class lylNode 
{
public:
	T data;
	lylNode<T> *next;

	lylNode()      //�����㣬data��δ��ʼ��
	{
		this->next = NULL;
	}

	lylNode(T data, lylNode<T> *next=NULL)      //data��ֵ��next��ֵ��Ĭ��ΪNULL
	{
		this->data = data;
		this->next = next;
	}
};
