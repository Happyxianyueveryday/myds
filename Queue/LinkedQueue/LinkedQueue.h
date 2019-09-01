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
    LinkedQueue(const LinkedQueue &other);                  // �������캯��
    LinkedQueue &operator= (const LinkedQueue &other);      // ������ֵ�����
    LinkedQueue(LinkedQueue &&other);                       // �ƶ����캯�� 
    LinkedQueue &operator= (LinkedQueue &&other);           // �ƶ���ֵ����� 

    // 3. methods
    bool push(int val);            // ������Ӳ���
    bool pop(int &val);            // ���г��Ӳ���
    bool frontval(int &val) const; // ��ȡ����Ԫ��
    int length() const;            // ������г��ȣ��������е�Ԫ�ظ���

    // 4. destructor
    ~LinkedQueue();

	private:
    ListNode *front;      // ����Ԫ��ָ��
    ListNode *end;        // ��βԪ��ָ��
    int size;             // ����Ԫ�ظ���
};

LinkedQueue::LinkedQueue()
{
    front=new ListNode(0);   // ����ͷ���ƽ��
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
	
	other.front=new ListNode(0);   // ����ͷ���ƽ��
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
	
	other.front=new ListNode(0);   // ����ͷ���ƽ��
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
        
        if(temp==end)   // ע�⣬ɾ�����һ��Ԫ��ʱendָ��ҲҪ�ֶ����� 
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
