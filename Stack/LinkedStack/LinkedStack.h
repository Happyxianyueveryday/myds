#include <iostream>
#include "Stack.h"

using namespace std;

struct ListNode
{
    // 1. methods
    ListNode(int _val):val(_val), next(NULL)
    {
    }
    
    // 2. domains
    int val;
    ListNode *next;
};

class LinkedStack: public Stack
{
    public: 
    // 1. constructor
    LinkedStack();       // 默认构造函数

    // 2. copy controller
    LinkedStack(const LinkedStack &other);                  // 拷贝构造函数
    LinkedStack &operator = (const LinkedStack &other);     // 拷贝赋值运算符

    // 3. methods
    void push(int val);    // 入栈操作
    bool pop(int &val);    // 出栈操作
    bool top(int &val) const;    // 获取栈顶元素操作
    int length() const;

    // 4. destructor
    ~LinkedStack();        // 析构函数

    // 5. domain
    ListNode *pos;         // 栈顶元素结点指针
    int size;              // 栈的元素个数
};

LinkedStack::LinkedStack()
{
    pos=NULL;
    size=0;
}

LinkedStack::LinkedStack(const LinkedStack &other)
{
	size=other.size;
	pos=NULL;     // 拷贝构造函数中成员变量并未初始化 
	if(other.pos)
	{
		pos=new ListNode(other.pos->val);
		ListNode *now=pos, *othnow=other.pos->next;
		while(othnow)
		{
			now->next=new ListNode(othnow->val);
			now=now->next;
			othnow=othnow->next;
		}
	}
}

LinkedStack & LinkedStack::operator = (const LinkedStack &other)
{
	if(this==&other)
	return (*this); 
	
	ListNode *now=pos;
	while(now)
	{
		ListNode *temp=now;
		now=now->next;
		delete temp;
	}
	
	size=other.size;
	if(other.pos)
	{
		pos=new ListNode(other.pos->val);

		ListNode *now=pos, *othnow=other.pos->next;
		while(othnow)
		{
			now->next=new ListNode(othnow->val);
			now=now->next;
			othnow=othnow->next;
		}
	}
}

void LinkedStack::push(int val)
{
    ListNode *newnode=new ListNode(val);
    newnode->next=pos;
    pos=newnode;
    size+=1;
}

bool LinkedStack::pop(int &val)
{
    if(!pos)
    return false;
    else
    {
        ListNode *temp=pos;
        val=pos->val;
        pos=pos->next;
        size-=1;
        delete temp;
    }
}

bool LinkedStack::top(int &val) const
{
    if(!pos)
    return false;
    else
    {
        val=pos->val;
        return true;
    }
    
}

int LinkedStack::length() const
{
    return size;
}

LinkedStack::~LinkedStack()
{
	ListNode *now=pos;
	while(now)
	{
		ListNode *temp=now;
		now=now->next;
		delete temp;
	}
}
