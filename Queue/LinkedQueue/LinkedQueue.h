#include <iostream>
#include <string>
#include "Queue.h" 

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

class LinkedQueue: public Queue
{
    public:   
    // 1. public constructor
    LinkedQueue();

    // 2. copy_controller
    LinkedQueue(const LinkedQueue &other);                  // 拷贝构造函数
    LinkedQueue &operator= (const LinkedQueue &other);      // 拷贝赋值运算符
    LinkedQueue(LinkedQueue &&other);                       // 移动构造函数 
    LinkedQueue &operator= (LinkedQueue &&other);           // 移动赋值运算符 

    // 3. methods
    bool push(int val);            // 队列入队操作
    bool pop(int &val);            // 队列出队操作
    bool frontval(int &val) const; // 获取队首元素
    int length() const;            // 计算队列长度，即队列中的元素个数

    // 4. destructor
    ~LinkedQueue();

	private:
    ListNode *front;      // 队首元素指针
    ListNode *end;        // 队尾元素指针
    int size;             // 队列元素个数
};

LinkedQueue::LinkedQueue()
{
    front=new ListNode(0);   // 链表头部哑结点
    end=front;
    size=0;
}

LinkedQueue::LinkedQueue(const LinkedQueue &other)
{
    front=new ListNode(0);
    
    ListNode *now=front;
    ListNode *othnow=other.front->next;
    while(othnow)
    {
    	now->next=new ListNode(othnow->val);
    	now=now->next;
    	othnow=othnow->next;
	}
	
	end=now;
	size=other.size;
}

LinkedQueue & LinkedQueue::operator= (const LinkedQueue &other)
{
	if(this==&other)
	return (*this);
	
	ListNode *now=front;
    while(now)
    {
        ListNode *temp=now;
        now=now->next;
        delete temp;
    }
    
    front=new ListNode(0);
    now=front;
    ListNode *othnow=other.front->next;
    while(othnow)
    {
    	now->next=new ListNode(othnow->val);
    	now=now->next;
    	othnow=othnow->next;
	}
	end=now;
	size=other.size;
	
	return (*this);
}

LinkedQueue::LinkedQueue(LinkedQueue &&other)
{
	front=other.front; 
	end=other.end; 
	size=other.size;
	
	other.front=new ListNode(0);   // 链表头部哑结点
    other.end=front;
    other.size=0;
}
 
LinkedQueue &LinkedQueue::operator= (LinkedQueue &&other)
{
	if(&other==this)
	return (*this);
	
	ListNode *now=front;
	while(now)
	{
		ListNode *temp=now;
		now=now->next;
		delete temp;
	}
	
	front=other.front;
	end=other.end;
	size=other.size;
	
	other.front=new ListNode(0);   // 链表头部哑结点
    other.end=front;
    other.size=0;
    
    return (*this);
} 

bool LinkedQueue::push(int val)
{
    ListNode *newnode=new ListNode(val);
    if(newnode)
    {
        end->next=newnode;
        end=end->next;
        size+=1;
        return true;
    }
    else
    return false;
}

bool LinkedQueue::pop(int &val)
{
    if(!size)
    return false;
    else
    {
        ListNode *temp=front->next;
        front->next=temp->next;
        val=temp->val;
        
        if(temp==end)   // 注意，删除最后一个元素时end指针也要手动更新 
        end=front;
        
        delete temp;
        size-=1;
        return true;
    }
}

bool LinkedQueue::frontval(int &val) const
{
    if(!size)
    return false;
    else
    {
        val=front->next->val;
        return true;
    }
}

int LinkedQueue::length() const
{
    return size;
}

LinkedQueue::~LinkedQueue()
{
    ListNode *now=front;
    while(now)
    {
        ListNode *temp=now;
        now=now->next;
        delete temp;
    }
}
