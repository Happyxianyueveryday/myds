#ifndef STATICLIST_H
#define STATICLIST_H
#include <iostream>
#include <string>
#include "List.h" 

using namespace std;

struct Node
{
	public:	
	Node(int _val=0):val(_val), next(-1)
	{
	}
	int val;   // 当前结点存储的值
	int next;  // 下一个结点的数组下标 
};

class StaticList: public List
{
    public:
    // 1. contructor
    StaticList(int _max_size);

    // 2. copy_controller
    StaticList(const StaticList &other);
    StaticList & operator= (const StaticList &other);

    // 3. methods
    bool get(int index, int &val) const override;    // 链表指定位置获取元素 
    bool insert(int index, int val) override;        // 链表指定位置插入元素
    bool remove(int index, int &val) override;       // 链表指定位置删除元素
    int length() const override;                     // 获取链表的长度
    void reverse() override;                         // 原地反转单向链表
    int middle() const override;                     // 返回链表中间结点的值
    string toString() const override;                // 输出当前链表 
    bool full() const;                               // 判断静态链表是否为空 
    bool empty() const;                              // 判断静态链表是否为满 
    virtual ~StaticList() override;                  // 虚析构函数 

    private:
    // 4. domains
    Node *data;    // 底层静态链表数组存储指针，data[0]固定存储工作链表的头部哑结点，data[1]固定存储空闲链表的头部哑结点 
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
StaticList::StaticList(int _max_size)
{
	max_size=_max_size+2;  
	size=0; 
	data=new Node[max_size];    
	
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
StaticList::StaticList(const StaticList &other)
{
	max_size=other.max_size;
	size=other.size;
	data=new Node[max_size];
	
	for(int i=0;i<max_size;i++)
	{
		data[i].val=other.data[i].val;
		data[i].next=other.data[i].next;
	}
}

/**
 * operator=: 拷贝赋值运算符 
 */
StaticList & StaticList::operator= (const StaticList &other)
{
	if(&other==this)
	return (*this);
	
	if(max_size!=other.max_size)
	{
		delete [] data;
		max_size=other.max_size;
		data=new Node[max_size];
	}
	
	size=other.size;
	for(int i=0;i<max_size;i++)
	{
		data[i].val=other.data[i].val;
		data[i].next=other.data[i].next;
	}
}

/**
 * get: 获取指定下标位置的元素值
 * param index: 需要获取值的位置的下标 
 * param val: 若获取成功，则存储指定下标位置的元素值 
 * return: 若获取成功则返回true，否则返回false 
 */
bool StaticList::get(int index, int &val) const
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
int StaticList::__malloc__()
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
void StaticList::__free__(int index)
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
bool StaticList::insert(int index, int val) 
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

bool StaticList::remove(int index, int &val)  
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
int StaticList::length() const 
{
	return size;
}

/**
 * reverse: 反转静态链表
 * note: 对于静态链表而言最方便的反转方式就是反转每两个结点之间的指针，这一过程可以简单使用now和nowprev双指针实现，最后令头部哑结点的next指针指向最后一个结点（即循环结束时的nowprev即可） 
 */
void StaticList::reverse()
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
int StaticList::middle() const
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
bool StaticList::full() const 
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
bool StaticList::empty() const
{
	if(data[0].next==-1)
	return true;
	else
	return false;
}

string StaticList::toString() const
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

StaticList::~StaticList()
{
	delete [] data;
}

#endif
