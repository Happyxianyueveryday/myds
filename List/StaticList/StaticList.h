#ifndef STATICLIST_H
#define STATICLIST_H
#include <iostream>
#include <string>
#include "List.h"       

using namespace std;

template<typename T>
struct Node
{
	public:	
	Node(T _val=T()):val(_val), next(-1)
	{
	}
	T val;   // ��ǰ���洢��ֵ
	int next;  // ��һ�����������±� 
};

template<typename T>
class StaticList: public List<T>
{
    public:
    // 1. contructor
    StaticList(int _max_size);

    // 2. copy/move_controller
    StaticList(const StaticList<T> &other);
    StaticList<T> &operator=(const StaticList<T> &other);
    StaticList(StaticList<T> &&other);
    StaticList<T> &operator=(StaticList<T> &&other);

    // 3. methods
    bool get(int index, T &val) const override;      // ����ָ��λ�û�ȡԪ�� 
    bool insert(int index, T val) override;          // ����ָ��λ�ò���Ԫ��
    bool remove(int index, T &val) override;         // ����ָ��λ��ɾ��Ԫ��
    int length() const override;                     // ��ȡ����ĳ���
    void reverse() override;                         // ԭ�ط�ת��������
    T middle() const override;                       // ���������м����ֵ
    string toString() const override;                // �����ǰ���� 
    bool full() const;                               // �жϾ�̬�����Ƿ�Ϊ�� 
    bool empty() const;                              // �жϾ�̬�����Ƿ�Ϊ�� 
    virtual ~StaticList() override;                  // ���������� 

    private:
    // 4. domains
    Node<T> *data;    // �ײ㾲̬��������洢ָ�룬data[0]�̶��洢���������ͷ���ƽ�㣬data[1]�̶��洢���������ͷ���ƽ�� 
    int max_size;  // ��̬���������ʵ�ʳ��ȣ����������ô洢��Ԫ+2��
	int size;      // ��ǰ�洢��Ԫ�ظ��� 
	
	// 5. private functions
	int __malloc__();                 // ����һ�����鵥Ԫ 
	void __free__(int index);         // �ͷ�һ�����鵥Ԫ����ָ�������鵥Ԫ�ӹ���������ɾ��������������� 
};

/**
 * StaticList: ���캯��
 * param _max_size: �������󳤶�/Ԫ������ 
 */
template<typename T>
StaticList<T>::StaticList(int _max_size)
{
	max_size=_max_size+2;  
	size=0; 
	data=new Node<T>[max_size];    
	
	data[0].next=-1;     		   // ��ʼ����������
	for(int i=1;i<max_size-1;i++)  // ��ʼ���������� 
	{
		data[i].next=i+1;
	}
	data[max_size-1].next=-1;
}

/**
 * StaticList: �������캯�� 
 */
template<typename T>
StaticList<T>::StaticList(const StaticList &other)
{
	max_size=other.max_size;
	size=other.size;
	data=new Node<T>[max_size];
	
	for(int i=0;i<max_size;i++)
	{
		data[i].val=other.data[i].val;
		data[i].next=other.data[i].next;
	}
}

/**
 * operator=: ������ֵ����� 
 */
template<typename T>
StaticList<T> &StaticList<T>::operator= (const StaticList<T> &other)
{
	if(&other==this)
	return (*this);
	
	if(max_size!=other.max_size)
	{
		delete [] data;
		max_size=other.max_size;
		data=new Node<T>[max_size];
	}
	
	size=other.size;
	for(int i=0;i<max_size;i++)
	{
		data[i].val=other.data[i].val;
		data[i].next=other.data[i].next;
	}
}

/**
 * StaticList: �ƶ����캯�� 
 */
template<typename T>
StaticList<T>::StaticList(StaticList &&other)
{
	// 1. ������Դ����ĳ�Ա����ֵ��������ǰ����ĳ�Ա������ 
	data=other.data;
	size=other.size;
	max_size=other.max_size;  
	// 2. ������Դ����ĳ�Ա������ΪĬ��ֵ����Ĭ�Ϲ��캯���г�ʼ����ֵ��
	other.size=0; 
	other.data=new Node<T>[max_size];    
	
	other.data[0].next=-1;     		   // ��ʼ����������
	for(int i=1;i<max_size-1;i++)      // ��ʼ���������� 
	{
		other.data[i].next=i+1;
	}
	other.data[max_size-1].next=-1;
}

/** 
 * operator=: �ƶ���ֵ����� 
 */
template<typename T>
StaticList<T>& StaticList<T>::operator=(StaticList<T> &&other)
{
	// 1. �ж��Ƿ�Ϊ����ֵ
	if(&other==this)
	return (*this);
	// 2. �ͷ����������ʹ�õĶѿռ�
	delete [] data; 
	// 3. �ӿ���Դ����ĳ�Ա��������ֵ
	data=other.data;
	max_size=other.max_size;
	size=other.size;
	// 4. ���ÿ���Դ����ĳ�Ա����ֵΪĬ��ֵ��Ĭ�Ϲ��캯���еĳ�Ա����ȡֵ��
	other.size=0; 
	other.data=new Node<T>[max_size];     
	
	other.data[0].next=-1;     		   // ��ʼ����������
	for(int i=1;i<max_size-1;i++)      // ��ʼ���������� 
	{
		other.data[i].next=i+1;
	}
	other.data[max_size-1].next=-1;
	// 5. ���ص�ǰ���������
	return (*this);
}

/**
 * get: ��ȡָ���±�λ�õ�Ԫ��ֵ
 * param index: ��Ҫ��ȡֵ��λ�õ��±� 
 * param val: ����ȡ�ɹ�����洢ָ���±�λ�õ�Ԫ��ֵ 
 * return: ����ȡ�ɹ��򷵻�true�����򷵻�false 
 */
template<typename T>
bool StaticList<T>::get(int index, T &val) const
{
	if(index<0||index>=size)
	return false;
	else
	{
		int now=data[0].next;     // ��ʼ���α�ָ��
		for(int i=0;i<index;i++)  // �ƶ��α�ָ�뵽�߼�λ���±�index 
		{
			now=data[now].next;
		} 
		val=data[now].val;
		return true;
	}
}  

/**
 * __malloc__: ����һ��������ڴ洢Ԫ��
 * return: ���뵽�Ľ���±� 
 * note: ����������Ǵӿ���������ȡ��һ����㹩ʹ�� 
 */ 
template<typename T>
int StaticList<T>::__malloc__()
{
	if(data[1].next==-1)
	return -1;
	else
	{
		int res=data[1].next;
		data[1].next=data[res].next;
		return res;
	}
}
 
/**
 * __free__: �ͷ�һ��ָ�����
 * param index: ��Ҫ�ͷŵĽ����±�
 * note: �ͷŲ������ǽ�ָ���±�Ľ�����¼������������ 
 */
template<typename T>
void StaticList<T>::__free__(int index)
{
	if(index==-1)
	return;
	else
	{
		data[index].next=data[1].next;
		data[1].next=index; 	
	}
}

/**
 * insert: �������в���Ԫ��
 * param index: Ҫ������߼�λ��
 * param val: Ҫ�����Ԫ��ֵ 
 */ 
template<typename T>
bool StaticList<T>::insert(int index, T val) 
{
	if(index<0||index>size)
	return false;
	else
	{
		// ���Ҳ���λ�� 
		int now=0;
		for(int i=0;i<index;i++)  
		{
			now=data[now].next;
		}
		// ������н�� 
		int index=__malloc__();
		if(index==-1)
		return false;
		else
		{
			data[index].val=val;
			data[index].next=data[now].next;
			data[now].next=index;
			size+=1;
			return true;	
		}
	}
}

template<typename T>
bool StaticList<T>::remove(int index, T &val)  
{
	if(index<0||index>=size)
	return false;
	else
	{
		// ����ɾ��λ�� 
		int now=0;
		for(int i=0;i<index;i++)
		{
			now=data[now].next;
		}
		// �ӹ���������ɾ��ָ����� 
		int tar=data[now].next;
		val=data[tar].val;
		data[now].next=data[tar].next;
		// �ͷŸý��
		__free__(tar);
		size-=1;
		return true;
	}
}

/**
 * length: ���ؾ�̬����ĳ���
 * return: ��ǰ��̬����ĳ��� 
 */
template<typename T>
int StaticList<T>::length() const 
{
	return size;
}

/**
 * reverse: ��ת��̬����
 * note: ���ھ�̬����������ķ�ת��ʽ���Ƿ�תÿ�������֮���ָ�룬��һ���̿��Լ�ʹ��now��nowprev˫ָ��ʵ�֣������ͷ���ƽ���nextָ��ָ�����һ����㣨��ѭ������ʱ��nowprev���ɣ� 
 */
template<typename T>
void StaticList<T>::reverse()
{
	int nowprev=0;
	int now=data[0].next;
	
	while(now!=-1)
	{
		int temp=data[now].next;
		
		if(now==data[0].next)
		data[now].next=-1;
		else
		data[now].next=nowprev;
		
		nowprev=now;
		now=temp;
	}
	data[0].next=nowprev;
}

/**
 * middle: ���ؾ�̬������м��� 
 */
template<typename T>
T StaticList<T>::middle() const
{
	int fast=data[0].next;
	int slow=data[0].next;
	
	while(data[fast].next!=-1&&data[data[fast].next].next!=-1)
	{
		fast=data[data[fast].next].next;
		slow=data[slow].next;
	}
	
	return data[slow].val;
}

/**
 * full: �жϾ�̬�����Ƿ��Ѿ���
 * note: ֻҪ��̬�����еĿ���������û�п��еĽ�㣬����Ϊ��̬�����Ѿ��� 
 */ 
template<typename T>
bool StaticList<T>::full() const 
{
	if(data[1].next==-1)
	return true;
	else
	return false;
}

/**
 * empty: �жϾ�̬�����Ƿ�Ϊ��
 * note: ֻҪ��̬�����еĹ��������в����ڽ�㣬����Ϊ��̬����Ϊ�� 
 */
template<typename T>
bool StaticList<T>::empty() const
{
	if(data[0].next==-1)
	return true;
	else
	return false;
}

template<typename T>
string StaticList<T>::toString() const
{
	string res;
	int now=data[0].next;
	while(now!=-1)
	{
		if(now==data[0].next)
		res=res+to_string(data[now].val);
		else
		res=res+"->"+to_string(data[now].val);
		now=data[now].next;
	}
	return res;
}

template<typename T>
StaticList<T>::~StaticList()
{
	delete [] data;
}

#endif
