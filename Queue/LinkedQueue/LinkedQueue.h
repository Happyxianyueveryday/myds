#include <iostream> 
#include <string>
#include "Queue.h" 

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
    ListNode<T> *next;
};

template<typename T> 
class LinkedQueue: public Queue<T>
{
    public:   
    // 1. public constructor
    LinkedQueue<T>();

    // 2. copy_controller
    LinkedQueue(const LinkedQueue<T> &other);                  // 拷贝构造函数
    LinkedQueue<T> &operator= (const LinkedQueue<T> &other);   // 拷贝赋值运算符
    LinkedQueue(LinkedQueue<T> &&other);                       // 移动构造函数 
    LinkedQueue<T> &operator= (LinkedQueue<T> &&other);        // 移动赋值运算符 

    // 3. methods
    bool push(T val);            // 队列入队操作
    bool pop(T &val);            // 队列出队操作
    bool frontval(T &val) const; // 获取队首元素
    int length() const;            // 计算队列长度，即队列中的元素个数

    // 4. destructor
    ~LinkedQueue();

	private:
    ListNode<T> *front;      // 队首元素指针
    ListNode<T> *end;        // 队尾元素指针
    int size;             // 队列元素个数
};

template<typename T> 
LinkedQueue<T>::LinkedQueue()
{
    front=new ListNode<T>(0);   // 链表头部哑结点
    end=front;
    size=0;
}

template<typename T> 
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T> &other)
{
    front=new ListNode<T>(0);
    
    ListNode<T> *now=front;
    ListNode<T> *othnow=other.front->next;
    while(othnow)
    {
    	now->next=new ListNode<T>(othnow->val);
    	now=now->next;
    	othnow=othnow->next;
	}
	
	end=now;
	size=other.size;
}

template<typename T> 
LinkedQueue<T> & LinkedQueue<T>::operator= (const LinkedQueue<T> &other)
{
	if(this==&other)
	return (*this);
	
	ListNode<T> *now=front;
    while(now)
    {
        ListNode<T> *temp=now;
        now=now->next;
        delete temp;
    }
    
    front=new ListNode<T>(0);
    now=front;
    ListNode<T> *othnow=other.front->next;
    while(othnow)
    {
    	now->next=new ListNode<T>(othnow->val);
    	now=now->next;
    	othnow=othnow->next;
	}
	end=now;
	size=other.size;
	
	return (*this);
}

template<typename T> 
LinkedQueue<T>::LinkedQueue(LinkedQueue<T> &&other)
{
	front=other.front; 
	end=other.end; 
	size=other.size;
	
	other.front=new ListNode<T>(0);   // 链表头部哑结点
    other.end=front;
    other.size=0;
}

template<typename T> 
LinkedQueue<T> &LinkedQueue<T>::operator= (LinkedQueue<T> &&other)
{
	if(&other==this)
	return (*this);
	
	ListNode<T> *now=front;
	while(now)
	{
		ListNode<T> *temp=now;
		now=now->next;
		delete temp;
	}
	
	front=other.front;
	end=other.end;
	size=other.size;
	
	other.front=new ListNode<T>(0);   // 链表头部哑结点
    other.end=front;
    other.size=0;
    
    return (*this);
} 

template<typename T> 
bool LinkedQueue<T>::push(T val)
{
    ListNode<T> *newnode=new ListNode<T>(val);
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

template<typename T> 
bool LinkedQueue<T>::pop(T &val)
{
    if(!size)
    return false;
    else
    {
        ListNode<T> *temp=front->next;
        front->next=temp->next;
        val=temp->val;
        
        if(temp==end)   // 注意，删除最后一个元素时end指针也要手动更新 
        end=front;
        
        delete temp;
        size-=1;
        return true;
    }
}

template<typename T> 
bool LinkedQueue<T>::frontval(T &val) const
{
    if(!size)
    return false;
    else
    {
        val=front->next->val;
        return true;
    }
}

template<typename T> 
int LinkedQueue<T>::length() const
{
    return size;
}

template<typename T> 
LinkedQueue<T>::~LinkedQueue()
{
    ListNode<T> *now=front;
    while(now)
    {
        ListNode<T> *temp=now;
        now=now->next;
        delete temp;
    }
}
