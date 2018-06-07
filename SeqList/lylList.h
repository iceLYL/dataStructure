#include <stdio.h>
#include <iostream>
using namespace std;
#include <exception>

template <class T> //��ģ�壬��T�����������ܳ��ֵ���������
class lylList 
{
	//˳�����Ա���Ҫ������Ա������
	//1.�洢�ռ����ʼλ�ã�*element ---��̬����, ָ���������ʼ��ַ
	//2.���Ա�����������MaxSize
	//3.��ǰ���ȣ�length  ��Ԫ�ظ���
  protected:
		T *element;
		int MaxSize;
		int length;

	public:
		void InitList(T value[], int n); //��ʼ����value--ֵ��int--����
		/*-----���캯������������------*/
		lylList(int MaxSize = 32);  //����ձ�maxsizeָ�� 
		lylList(int MaxSize, T x);    //maxsize��Ԫ�أ�ֵȫΪx
		lylList(T value[], int n);
		~lylList();
		/*-------------end-------------*/

		bool empty();   //�ж�˳����Ƿ�Ϊ��
		int count();       //����˳���Ԫ�ظ���

		 /*-----���������------*/
		 //�����±������
		T& operator[](int i);    
		//���������
		//C++ �ܹ�ʹ������ȡ����� >> ������������� << �������������õ���������
		//������������ȡ������������������������������û��Զ�����������͡�
		//��Ҫ����������غ�������Ϊ�����Ԫ����		
		//��ģ��ʱ��<>
		//����ʱ��д����ostream& operator<<<>(ostream& out, lylList<T>&list);    
		friend ostream& operator<<<>(ostream&, lylList<T>&);    
		/*-------------end-------------*/

		void printPrevious();     //����������Ӻ���ǰ
		void insert(int i, T x);     //����x��Ϊ��i��Ԫ��
		virtual void insert(T x);  //��˳���������x
		T remove(int i);             //ɾ����i��Ԫ�أ�������
		void removeAll();
		virtual int search(T key, int start = 0);   //��start��ʼ����keyԪ�أ�����Ԫ�����
		virtual void removeFirst(T key);            //ɾ���״γ��ֹؼ���ΪkeyԪ��

		lylList(lylList<T> &list);      //�������캯��
		lylList<T>& operator=(lylList<T> &list);    //����=��ֵ����������
		bool operator==(lylList<T> &list);   //�Ƚ�����˳�������ֵ�Ƿ����
		bool operator!=(lylList<T> &list);     //
		void operator+=(lylList<T> &list);    //��*this��ǰ˳���֮��ϲ�������list
		lylList<T> operator+(lylList<T> &list);   //����*this��list�ϲ����ӵĶ���

};

template <class T>
void lylList<T>::InitList(T value[], int n)
{

	lylList(value, n);
}

// ���캯����ɹ��ܣ���ֵ��Ա������
//1.ָ��MaxSize
//2.ָ��element��������Ϊ��̬������ʹ�ã�ͨ���±꣩�����ٿռ�new����ֵ
//3.��ֵlength
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

//������������delete�ͷ��ڴ�
//�ͷ����飬��delete[]
template <class T>
lylList<T>::~lylList()
{
	delete[]this->element;
}

template <class T>
bool lylList<T>::empty()   //C++�����ֵ�����ΪTrue,Ϊ�����False
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
	//ע���±���ܻᳬ����Χ
	//����Ҫд�жϺ��ݴ��ʩ
	//return this->element[i];  ���ܵ�д��һ��
	if (i >= 0 && i < this->length)
		return this->element[i];
	throw out_of_range("����i������Χ��");   //c++STL ��ΧԽ���쳣
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
void lylList<T>::printPrevious()  //����������Ӻ���ǰ
{
	for (int i = this->length - 1; i >= 0; i--)
		cout <<" "<< this->element[i];
	cout << endl;
}

template <class T>
void lylList<T>::insert(int i, T x)    //����x��Ϊ��i��Ԫ��
{
	if (i < 0) i = 1;    //i�ݴ�
	if (i > this->length) i = this->length;
	//1.�ж������Ƿ�
	//2.���������ݣ�����ok
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
	for (int j = this->length - 1; j >= i - 1; j--)    //��i��Ԫ�أ��±�Ϊi-1
		this->element[j + 1] = this->element[j];
	this->element[i - 1] = x;
	this->length++;
}

template <class T>
void lylList<T>::insert(T x)  //��˳���������x���麯��
{
	insert(length, x);
}

template <class T>
T lylList<T>::remove(int i)            //ɾ����i��Ԫ�أ�������
{
	
	int a;
	if (i >= 0 && i < this->length)
	{
		a = element[i - 1];
		for (int j = i - 1; j < this->length; j++)    //��i��Ԫ�أ��±�Ϊi-1
		{ 
			this->element[j] = this->element[j + 1];
			this->length--;
			break;
		}
		return a;
	}
/*
	//i��0��ʼ
	int a;
	if (i >= 0 && i < this->length)
	{
		a = element[i];
		for (int j = i ; j < this->length; j++)    //��i��Ԫ�أ��±�Ϊi-1
		{ 
			this->element[j] = this->element[j + 1];
			this->length--;
			break;
		}
		return a;
	}*/
	throw out_of_range("�±�i����˳����򲻺Ϸ���");
}

template <class T>
void lylList<T>::removeAll()
{
	this->length = 0; //ɾ������Ԫ�أ�δ�ͷſռ�
}

template <class T>
int lylList<T>::search(T key, int start = 0)  //��start��ʼ����keyԪ�أ�����Ԫ����� ;��
{
	for (int i = start; i < this->length; i++)
		if (this->element[i] == key)
			return i;
	return -1;
}

template <class T>
void lylList<T>::removeFirst(T key)            //ɾ���״γ��ֹؼ���ΪkeyԪ��;��
{

	for (int i = 0; i < this->length; i++)
	{
		if (this->element[i] == key)
		{
			remove(i+1);//remove����ɾ���ڼ������±��1��ʼ
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
lylList<T>& lylList<T>::operator=(lylList<T> &list)    //���
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
bool lylList<T>::operator==(lylList<T> &list)   //�Ƚ�����˳�������ֵ�Ƿ����
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
void lylList<T>::operator+=(lylList<T> &list)   //��*this��ǰ˳���֮��ϲ�������list
{
	if((this->length+list.length)>=this->MaxSize)
	{
		this->MaxSize = (this->MaxSize + list.MaxSize) * 2;   //����
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
lylList<T> lylList<T>::operator+(lylList<T> &list)  //����*this��list�ϲ����ӵĶ���
{	
	lylList a(this->length+list.length);
	a.length = a.MaxSize;
	for (int i = 0; i < this->length; i++)
		a.element[i] = this->element[i];
	for (int i = this->length; i <this->length + list.length; i++)
		a.element[i] = list.element[i - this->length];
	return a;
}