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
    LinkedStack();       // Ĭ�Ϲ��캯��

    // 2. copy/move controller
    LinkedStack(const LinkedStack<T> &other);                  // �������캯��
    LinkedStack<T> & operator= (const LinkedStack<T> &other);     // ������ֵ�����
    LinkedStack(LinkedStack<T> &&other);                       // �ƶ����캯�� 
    LinkedStack<T> & operator= (LinkedStack<T> &&other);     		// �ƶ���ֵ����� 

    // 3. methods
    void push(T val);    // ��ջ����
    bool pop(T &val);    // ��ջ����
    bool top(T &val) const;    // ��ȡջ��Ԫ�ز���
    int length() const;  // ��ȡջ�ĳ��Ȳ��� 

    // 4. destructor
    ~LinkedStack();        // ��������

    // 5. domain
    ListNode<T> *pos;         // ջ��Ԫ�ؽ��ָ��
    int size;              // ջ��Ԫ�ظ���
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
	pos=NULL;     // �������캯���г�Ա������δ��ʼ�� 
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
