#include <iostream>
#include "Stack.h"

using namespace std;

template<typename T>
struct ListNode
{
    // 1. methods
    ListNode(T _val):val(_val), next(NULL)
    {
    }
    
    // 2. domains
    T val;
    ListNode *next;
};

template<typename T>
class LinkedStack: public Stack<T>
{
    public: 
    // 1. constructor
    LinkedStack();       // 默认构造函数

    // 2. copy/move controller
    LinkedStack(const LinkedStack<T> &other);                  // 拷贝构造函数
    LinkedStack<T> & operator= (const LinkedStack<T> &other);     // 拷贝赋值运算符
    LinkedStack(LinkedStack<T> &&other);                       // 移动构造函数 
    LinkedStack<T> & operator= (LinkedStack<T> &&other);     		// 移动赋值运算符 

    // 3. methods
    void push(T val);    // 入栈操作
    bool pop(T &val);    // 出栈操作
    bool top(T &val) const;    // 获取栈顶元素操作
    int length() const;  // 获取栈的长度操作 

    // 4. destructor
    ~LinkedStack();        // 析构函数

    // 5. domain
    ListNode<T> *pos;         // 栈顶元素结点指针
    int size;              // 栈的元素个数
};

template<typename T>
LinkedStack<T>::LinkedStack()
{
    pos=NULL;
    size=0;
}

template<typename T>
LinkedStack<T>::LinkedStack(const LinkedStack<T> &other)
{
	size=other.size;
	pos=NULL;     // 拷贝构造函数中成员变量并未初始化 
	if(other.pos)
	{
		pos=new ListNode<T>(other.pos->val);
		ListNode<T> *now=pos, *othnow=other.pos->next;
		while(othnow)
		{
			now->next=new ListNode<T>(othnow->val);
			now=now->next;
			othnow=othnow->next;
		}
	}
}

template<typename T>
LinkedStack<T> & LinkedStack<T>::operator= (const LinkedStack<T> &other)
{
	if(this==&other)
	return (*this); 
	
	ListNode<T> *now=pos;
	while(now)
	{
		ListNode<T> *temp=now;
		now=now->next;
		delete temp;
	}
	
	size=other.size;
	if(other.pos)
	{
		pos=new ListNode<T>(other.pos->val);

		ListNode<T> *now=pos, *othnow=other.pos->next;
		while(othnow)
		{
			now->next=new ListNode<T>(othnow->val);
			now=now->next;
			othnow=othnow->next;
		}
	}
}

template<typename T>
LinkedStack<T>::LinkedStack(LinkedStack<T> &&other)
{
	pos=other.pos;
	size=other.size;
	
	other.pos=NULL;
	other.size=0;
} 

template<typename T>
LinkedStack<T> & LinkedStack<T>::operator= (LinkedStack<T> &&other) 
{
	if(&other==this)
	return (*this);
	
	ListNode<T> *now=pos;
	while(now)
	{
		ListNode<T> *temp=now;
		now=now->next;
		delete temp;
	}
	
	pos=other.pos;
	size=other.size;
	
	other.pos=NULL;
	other.size=0;
	
	return (*this);
}

template<typename T>
void LinkedStack<T>::push(T val)
{
    ListNode<T> *newnode=new ListNode<T>(val);
    newnode->next=pos;
    pos=newnode;
    size+=1;
}

template<typename T>
bool LinkedStack<T>::pop(T &val)
{
    if(!pos)
    return false;
    else
    {
        ListNode<T> *temp=pos;
        val=pos->val;
        pos=pos->next;
        size-=1;
        delete temp;
    }
}

template<typename T>
bool LinkedStack<T>::top(T &val) const
{
    if(!pos)
    return false;
    else
    {
        val=pos->val;
        return true;       
    }
    
}

template<typename T>
int LinkedStack<T>::length() const
{
    return size;
}

template<typename T>
LinkedStack<T>::~LinkedStack()
{
	ListNode<T> *now=pos;
	while(now)
	{
		ListNode<T> *temp=now;
		now=now->next;
		delete temp;
	}
}
