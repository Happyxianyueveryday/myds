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
	T val;   // 当前结点存储的值
	int next;  // 下一个结点的数组下标 
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
    bool get(int index, T &val) const override;      // 链表指定位置获取元素 
    bool insert(int index, T val) override;          // 链表指定位置插入元素
    bool remove(int index, T &val) override;         // 链表指定位置删除元素
    int length() const override;                     // 获取链表的长度
    void reverse() override;                         // 原地反转单向链表
    T middle() const override;                       // 返回链表中间结点的值
    string toString() const override;                // 输出当前链表 
    bool full() const;                               // 判断静态链表是否为空 
    bool empty() const;                              // 判断静态链表是否为满 
    virtual ~StaticList() override;                  // 虚析构函数 

    private:
    // 4. domains
    Node<T> *data;    // 底层静态链表数组存储指针，data[0]固定存储工作链表的头部哑结点，data[1]固定存储空闲链表的头部哑结点 
    int max_size;  // 静态链表数组的实际长度（等于最大可用存储单元+2）
	int size;      // 当前存储的元素个数 
	
	// 5. private functions
	int __malloc__();                 // 申请一个数组单元 
	void __free__(int index);         // 释放一个数组单元：将指定的数组单元从工作链表中删除并加入空闲链表 
};

/**
 * StaticList: 构造函数
 * param _max_size: 链表的最大长度/元素数量 
 */
template<typename T>
StaticList<T>::StaticList(int _max_size)
{
	max_size=_max_size+2;  
	size=0; 
	data=new Node<T>[max_size];    
	
	data[0].next=-1;     		   // 初始化工作链表
	for(int i=1;i<max_size-1;i++)  // 初始化空闲链表 
	{
		data[i].next=i+1;
	}
	data[max_size-1].next=-1;
}

/**
 * StaticList: 拷贝构造函数 
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
 * operator=: 拷贝赋值运算符 
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
 * StaticList: 移动构造函数 
 */
template<typename T>
StaticList<T>::StaticList(StaticList &&other)
{
	// 1. 将拷贝源对象的成员变量值拷贝到当前对象的成员变量上 
	data=other.data;
	size=other.size;
	max_size=other.max_size;  
	// 2. 将拷贝源对象的成员变量设为默认值（即默认构造函数中初始化的值）
	other.size=0; 
	other.data=new Node<T>[max_size];    
	
	other.data[0].next=-1;     		   // 初始化工作链表
	for(int i=1;i<max_size-1;i++)      // 初始化空闲链表 
	{
		other.data[i].next=i+1;
	}
	other.data[max_size-1].next=-1;
}

/** 
 * operator=: 移动赋值运算符 
 */
template<typename T>
StaticList<T>& StaticList<T>::operator=(StaticList<T> &&other)
{
	// 1. 判断是否为自身赋值
	if(&other==this)
	return (*this);
	// 2. 释放自身对象所使用的堆空间
	delete [] data; 
	// 3. 从拷贝源对象的成员变量拷贝值
	data=other.data;
	max_size=other.max_size;
	size=other.size;
	// 4. 重置拷贝源对象的成员变量值为默认值（默认构造函数中的成员变量取值）
	other.size=0; 
	other.data=new Node<T>[max_size];     
	
	other.data[0].next=-1;     		   // 初始化工作链表
	for(int i=1;i<max_size-1;i++)      // 初始化空闲链表 
	{
		other.data[i].next=i+1;
	}
	other.data[max_size-1].next=-1;
	// 5. 返回当前对象的引用
	return (*this);
}

/**
 * get: 获取指定下标位置的元素值
 * param index: 需要获取值的位置的下标 
 * param val: 若获取成功，则存储指定下标位置的元素值 
 * return: 若获取成功则返回true，否则返回false 
 */
template<typename T>
bool StaticList<T>::get(int index, T &val) const
{
	if(index<0||index>=size)
	return false;
	else
	{
		int now=data[0].next;     // 初始化游标指针
		for(int i=0;i<index;i++)  // 移动游标指针到逻辑位置下标index 
		{
			now=data[now].next;
		} 
		val=data[now].val;
		return true;
	}
}  

/**
 * __malloc__: 申请一个结点用于存储元素
 * return: 申请到的结点下标 
 * note: 申请操作就是从空闲链表中取出一个结点供使用 
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
 * __free__: 释放一个指定结点
 * param index: 需要释放的结点的下标
 * note: 释放操作就是将指定下标的结点重新加入空闲链表中 
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
 * insert: 向链表中插入元素
 * param index: 要插入的逻辑位置
 * param val: 要插入的元素值 
 */ 
template<typename T>
bool StaticList<T>::insert(int index, T val) 
{
	if(index<0||index>size)
	return false;
	else
	{
		// 查找插入位置 
		int now=0;
		for(int i=0;i<index;i++)  
		{
			now=data[now].next;
		}
		// 申请空闲结点 
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
		// 查找删除位置 
		int now=0;
		for(int i=0;i<index;i++)
		{
			now=data[now].next;
		}
		// 从工作链表中删除指定结点 
		int tar=data[now].next;
		val=data[tar].val;
		data[now].next=data[tar].next;
		// 释放该结点
		__free__(tar);
		size-=1;
		return true;
	}
}

/**
 * length: 返回静态链表的长度
 * return: 当前静态链表的长度 
 */
template<typename T>
int StaticList<T>::length() const 
{
	return size;
}

/**
 * reverse: 反转静态链表
 * note: 对于静态链表而言最方便的反转方式就是反转每两个结点之间的指针，这一过程可以简单使用now和nowprev双指针实现，最后令头部哑结点的next指针指向最后一个结点（即循环结束时的nowprev即可） 
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
 * middle: 返回静态链表的中间结点 
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
 * full: 判断静态链表是否已经满
 * note: 只要静态链表中的空闲链表中没有空闲的结点，就认为静态链表已经满 
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
 * empty: 判断静态链表是否为空
 * note: 只要静态链表中的工作链表中不存在结点，就认为静态链表为空 
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
