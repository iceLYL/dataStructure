#include "lylNode.h"
#include <stdio.h>
#include <iostream>
using namespace std;

template <class T>
class lylSinglyList 
{
public:
	lylNode<T> *head;      //ͷָ��

	/*------���캯��-------*/
	lylSinglyList();                               //����յ�����
	lylSinglyList(T values[], int n);       //���쵥������values�����ṩԪ��
	~lylSinglyList();
	/*------end-------*/

	bool empty();                                //�ж������Ƿ�Ϊ��
	int count();                                    //���ص�������
	T get(int i);                                 //���ص�i����0����Ԫ�ص�����
	virtual void set(int i, T x);              //���õ�i����0����Ԫ��Ϊx
	friend ostream& operator<<<>(ostream&, lylSinglyList<T>&);
	lylNode<T>* insert(int i, T x);          //����x��Ϊ��i����㣬���ؽ���ַ                      
	virtual lylNode<T>* insert(T x);       //�ڵ�����������Ԫ��x

	T remove(int i);                              //�����i����㣬�����ر�ɾ��Ԫ��
	void removeAll();                           //��յ�����
	int searchIndex(T key);                           //����key�������±�
	lylNode<T>* search(T key);           //˳������״γ��ֵĹؼ���ΪkeyԪ�أ����ؽ���ַ��
	                                                       //��δ�ҵ�������NULL�� 
	                                                        //T���������������==��
	void insertUnrepeatable(T x);          //β���벻�ظ�Ԫ��
	virtual void removeFirst(T key);       //ɾ���״γ��ֵĹؼ���ΪkeyԪ��

	/*���������*/
	bool operator==(lylSinglyList<T> &list);   //�Ƚ������������Ƿ����
	bool operator!=(lylSinglyList<T> &list);
	lylSinglyList(lylSinglyList<T> &list);
	lylSinglyList<T> &operator=(lylSinglyList<T> &list);   //���
	virtual void operator+=(lylSinglyList<T> &list);           //��list�����ڵ�ǰ������֮��
	/*end*/
};

template <class T>
lylSinglyList<T>::lylSinglyList()
{
	this->head = new lylNode<T>();    //����headͷ��㣬��lylNode()�޲ι��캯��
}

template<class T>
lylSinglyList<T>::lylSinglyList(T values[], int n)
{
	this->head = new lylNode<T>();
	lylNode<T> *p = this->head;  //pָ��head
	for (int i = 0; i < n; i++)
	{
		p->next = new lylNode<T>(values[i]);
		p = p->next;    //pָ���¿��ٵĽ�㣬Ҳ����������β���
	}
}

template <class T>
lylSinglyList<T>::~lylSinglyList()  ///////////////////////////////////////////////////���鲻ͬ
{
	lylNode<T> *rear = head;
	while (rear->next != NULL)    //rear��������������β��
	{
		rear = rear->next;
	}
	head = rear;     //ͷ=β���������
	delete this->head;
}

template <class T>
bool lylSinglyList<T>::empty()                               //�ж������Ƿ�Ϊ��  1:��
{
	if (NULL != this->head->next)
		return 0;
	else
		return 1;
}

template<class T>
int lylSinglyList<T>::count()                                   //���ص�������, ͷ��㲻��
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
T lylSinglyList<T>::get(int i)                                 //���ص�i����0����Ԫ�ص�����
{
	//////////////////////////////////////////////////////����T&��������������������

	lylNode<T> *p = this->head;
	for (int j = 0; j < i + 1 && p->next!=NULL ; j++)   //��0��ʼ
	{
		p = p->next;
	}
	if(i>=0&&p!=NULL)
		return p->data;
	throw out_of_range("i������Χ��");
}

template<class T>
void lylSinglyList<T>::set(int i, T x)              //���õ�i����0����Ԫ��Ϊx����
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
lylNode<T>* lylSinglyList<T>::insert(int i, T x)  //i��0��ʼ�����ص���head����Ķ���������ѭ��i�Σ���i=0��head����ĵ�һ��
{
	//insert�ݴ�:��i<0������head����
	lylNode<T> *p = this->head;
	for (int j = 0; j < i && p->next!=NULL; j++)
	{
		p = p->next;
	}
//	lylNode<T> *q = new lylNode<T>(x);
//	q->next = p->next;            
// ���������������һ���ʾ
	lylNode<T> *q = new lylNode<T>(x, p->next);
	p->next = q;
	return p->next;
}

template<class T>
lylNode<T>* lylSinglyList<T>::insert(T x)       //�ڵ�����������Ԫ��x
{
	lylNode<T> *p = this->head;
	while (p->next != NULL)
		p = p->next;
	lylNode<T> *rear = new lylNode<T>(x);
	p->next = rear;
	return p->next;
}

/*���������*/
template<class T>
bool lylSinglyList<T>::operator==(lylSinglyList<T> &list)   //�Ƚ������������Ƿ����
{
	lylNode<T> *p_this = this->head;
	lylNode<T> *p_list = list.head;
	int this_count = 0, list_count = 0;
	while (p_this->next != NULL && p_list != NULL)
	{
		this_count++; list_count++;
		p_this = p_this->next;
		p_list = p_list->next;
		if (p_this->data != p_list->data)         //���1�����ݲ�ͬ
			return 0;
	}
	if (p_this->next != NULL)                       //���2�����Ȳ�ͬ
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
T lylSinglyList<T>::remove(int i)                              //�����i (ͷ��㲻�㣬i��0��ʼ) ����㣬�����ر�ɾ��Ԫ��
{
	lylNode<T> *p = this->head;
	lylNode<T> *q;
	for (int j = 0; j < i ; j++)          //ɾ����i����㣬p�ǵ�i-1�����
	{
		p = p->next;
	}
	q = p->next;
	p->next = p->next->next;
	return q->data;
}

template<class T>
void lylSinglyList<T>::removeAll()                           //��յ�����
{
	this->head->next = NULL;
}

template<class T>
lylNode<T>* lylSinglyList<T>::search(T key)          //˳������״γ��ֵĹؼ���ΪkeyԪ�أ����ؽ���ַ��
									 //��δ�ҵ�������NULL�� 
									 //T���������������==��
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
int lylSinglyList<T>::searchIndex(T key)          //˳������״γ��ֵĹؼ���ΪkeyԪ�أ������±ꣻ
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
void lylSinglyList<T>::insertUnrepeatable(T x)          //β���벻�ظ�Ԫ��
{                                                       //�ظ������壻���ظ����顣����ӡ���
	if (search(x))  //search����������˵�������ظ���
		cout << "�Ѿ�����"<<x << endl;
	else
	{
		lylNode<T> *p = this->head;
		while (p->next != NULL)
			p = p->next;
		lylNode<T> *add = new lylNode<T>(x);
		p->next = add;
		cout << x << "����ɹ�" << endl;
	}
}

template<class T>
void lylSinglyList<T>::removeFirst(T key)      //ɾ���״γ��ֵĹؼ���ΪkeyԪ��
{
	lylNode<T> *p = search(key);
	lylNode<T> *p_remove = this->head;
	while (p_remove->next != p)
		p_remove = p_remove->next;
	p_remove->next = p->next;            //or : p_remove->next = p_remove->next->next;
}

template<class T>
bool lylSinglyList<T>::operator!=(lylSinglyList<T> &list)            //��==��
{
	lylNode<T> *p_this = this->head;
	lylNode<T> *p_list = list.head;
	int this_count = 0, list_count = 0;
	while (p_this->next != NULL && p_list != NULL)
	{
		this_count++; list_count++;
		p_this = p_this->next;
		p_list = p_list->next;
		if (p_this->data != p_list->data)         //���1�����ݲ�ͬ
			return 1;
	}
	if (p_this->next != NULL)                       //���2�����Ȳ�ͬ
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
	//���
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
lylSinglyList<T>& lylSinglyList<T>::operator=(lylSinglyList<T> &list)   //���
{
	//���
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
void lylSinglyList<T>::operator+=(lylSinglyList<T> &list)           //��list�����ڵ�ǰ������֮��
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