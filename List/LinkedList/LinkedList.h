#ifndef LINKED_LIST_H 
#define LINKED_LIST_H
#include <iostream>
#include <vector>
#include <string>      
#include "List.h"

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

/**
 * LinkedList : 单向链表类
 */
template<typename T>
class LinkedList: public List<T>
{
    public:
    // 1. constructor
    LinkedList();                             // 默认构造函数
    LinkedList(const T _data[], int _size);   // 从数组构造单向链表
    LinkedList(const vector<T> &_data);       // 从vector构造单向链表

    // 2. copy/move controller
    LinkedList(const LinkedList &other);                // 拷贝构造函数
    LinkedList &operator= (const LinkedList &other);     // 拷贝赋值运算符
    LinkedList(LinkedList &&other);                      // 移动构造函数
	LinkedList &operator= (LinkedList &&other);           // 移动赋值运算符 
    
    // 3. methods
    bool get(int index, T &val) const override;    // 链表指定位置获取元素
    bool insert(int index, T val) override;        // 链表指定位置插入元素
    bool remove(int index, T &val) override;       // 链表指定位置删除元素
    int length() const override;                   // 获取链表的长度
    void reverse() override;                       // 原地反转单向链表
    T middle() const override;                     // 返回链表中间结点的值
    string toString() const override;              // 输出当前链表 

    // 4. destructor
    ~LinkedList();

    private:
    ListNode<T> *head;
    int size;
};

/**
 * LinkedList: 默认构造函数
 */
template<typename T>
LinkedList<T>::LinkedList()
{
    head=new ListNode<T>(0);    // 创建链表头部哑结点
    size=0;                  // 初始化链表结点计数变量
}

/**
 * LinkedList: 从数组构造单向链表
 * param _data: 输入元素数组
 * param _size: 输入数组的长度
 */
template<typename T>
LinkedList<T>::LinkedList(const T _data[], int _size)
{
    // 初始化链表
    head=new ListNode<T>(0);
    size=_size;

    // 将数组元素依次插入链表末尾
    ListNode<T> *now=head;
    for(int i=0;i<_size;i++)
    {
        now->next=new ListNode<T>(_data[i]);
        now=now->next;
    }
}

/**
 * LinkedList: 从vector对象构造单向链表
 * param _data: 输入元素列表
 */
template<typename T>
LinkedList<T>::LinkedList(const vector<T> &_data)
{
    // 初始化链表
    head=new ListNode<T>(T());
    size=_data.size();

    // 将列表元素依次插入链表末尾
    ListNode<T> *now=head;
    for(int i=0;i<_data.size();i++)
    {
        now->next=new ListNode<T>(_data[i]);
        now=now->next;
    }
}

/**
 * List: 拷贝构造函数
 * other: 拷贝源链表
 */
template<typename T>
LinkedList<T>::LinkedList(const LinkedList &other)                
{
    // 初始化链表
    head=new ListNode<T>(T());
    size=other.size;

    // 将源链表中的结点依次拷贝到当前对象中
    ListNode<T> *othnow=other.head->next;
    ListNode<T> *now=head;

    while(othnow)
    {
        now->next=new ListNode<T>(othnow->val);
        now=now->next;
        othnow=othnow->next;
    }
}

/**
 * operator =: 拷贝赋值运算符
 * other: 赋值源链表
 * return: 当前对象引用
 */
template<typename T>
LinkedList<T> &LinkedList<T>::operator= (const LinkedList<T> &other)
{
    // 判断自身赋值
    if(this==&other) 
    return (*this);

    // 释放原链表中的所有结点
    ListNode<T> *now=head->next;
    head->next=NULL;
    while(now)
    {
        ListNode<T> *temp=now;
        now=now->next;
        delete temp;
    }

    // 拷贝源链表中的所有结点
    now=head;
    ListNode<T> *othnow=other.head->next;
    while(othnow)
    {
        now->next=new ListNode<T>(othnow->val);
        now=now->next;
        othnow=othnow->next;
    }
    size=other.size;
    return (*this);
}

/**
 * LinkedList: 移动构造函数 
 */
template<typename T>
LinkedList<T>::LinkedList(LinkedList &&other)
{
	// 1. 从拷贝源对象拷贝成员变量值
	head=other.head;
	size=other.size;
	// 2. 将拷贝源对象的成员变量设置为默认值
	other.head=new ListNode<T>(0);
	other.size=0;
}

/**
 * operator=: 移动赋值运算符  
 */
template<typename T>
LinkedList<T> &LinkedList<T>::operator= (LinkedList &&other)
{
	// 1. 判断是否为自身赋值
	if(&other==this)
	return (*this);
	// 2. 释放当前对象所使用的堆空间
	ListNode<T> *now=head; 
	while(now)
	{
		ListNode<T> *temp=now;
		now=now->next;
		delete temp;
	}
	// 3. 从拷贝源对象拷贝成员变量值
	head=other.head;
	size=other.size;
	// 4. 将拷贝源对象的成员变量设置为默认值
	other.head=new ListNode<T>(0);
	other.size=0;
	// 5. 返回当前对象的左值引用
	return (*this); 
}
    
/**
 * get: 链表指定位置获取元素
 * param index: 要获取的元素的位置索引（从0开始索引）
 * param val: 所获取的元素值
 * return: 若位置合法获取元素值成功，则返回true；否则返回false
 */
template<typename T>
bool LinkedList<T>::get(int index, T &val) const
{
    if(index<0||index>=size)
    return false;

    ListNode<T> *now=head;
    for(int i=0;i<=index;i++)
    {
        now=now->next;
    }
    val=now->val;
    return true;
}

/**
 * insert: 链表指定位置插入元素
 * param index: 要插入元素的位置索引
 * param val: 要插入的元素值
 * return: 若插入成功，则返回true；否则返回false
 */
template<typename T>
bool LinkedList<T>::insert(int index, T val)
{
    if(index<0||index>size)
    return false;

    ListNode<T> *now=head;
    ListNode<T> *newnode=new ListNode<T>(val);
    for(int i=0;i<index;i++)
    {
        now=now->next;
    }
    newnode->next=now->next;
    now->next=newnode;
    size+=1;
    return true;
}

/**
 * remove: 链表指定位置删除元素
 * param index: 待删除的位置下标
 * param val: 所删除的值
 */
template<typename T>
bool LinkedList<T>::remove(int index, T &val)
{
    if(index<0||index>=size)
    return false;

    ListNode<T> *now=head;
    for(int i=0;i<index;i++)
    {
        now=now->next;
    }
    ListNode<T> *temp=now->next;
    now->next=now->next->next;
    val=temp->val;
    delete temp;
    size-=1;
    return true;
}

/**
 * size: 获取链表的长度/元素个数
 */
template<typename T>
int LinkedList<T>::length() const
{
    return size;
}

/**
 * reverse: 原地反转链表
 * note: 原地反转链表存在两种算法：
 *       1. 顺序遍历从第二个结点开始的后续每个结点，将访问到的每个结点从原位置删除，然后插入到头部哑结点之后
 *       2. 顺序遍历每个结点，将每个结点的next指针反向指向当前结点的前一个元素（第一个结点则反向指向NULL），最后将头部哑结点的next指针指向最后一个访问的结点 
 */
template<typename T>
void LinkedList<T>::reverse()
{
	// 算法1版本
	if(!head->next)
	return;
	
    ListNode<T> *nowprev=head->next;
    ListNode<T> *now=head->next->next;
    
    while(now)
    {
        nowprev->next=now->next;   // 将当前结点now从原位置删除
        now->next=head->next;
        head->next=now;            // 将当前结点now插入到头部哑结点之后
        now=nowprev->next;         // 更新游标指针now和nowprev，因为now从原位置被删除，因此nowprev不变，now更新为nowprev->next
    }
    
    /*
    // 算法2版本
    ListNode *nowprev=NULL;        // 注意首结点逆转后变为尾结点，因此其前驱结点应当是NULL而非头部哑结点，这里若写成head则会产生环 
    ListNode *now=head->next;
    
    while(now)
    {
        ListNode *temp=now->next;
        now->next=nowprev;         // 反转各个结点的指针指向
        nowprev=now;               // 更新游标指针now和nowprev
        now=temp;
    }
    head->next=nowprev;            // 将头部哑结点的next指针指向原来的最后一个结点nowprev(注意不是now，now==nowprev->next==NULL) 
    */
}

/**
 * middle: 返回链表中间结点的值 
 * return: 链表中间结点的值
 * note: 查找链表的中间结点一般使用快慢双指针法
 */ 
template<typename T>
T LinkedList<T>::middle() const
{
    ListNode<T> *fast=head->next;
    ListNode<T> *slow=head->next;

    while(fast&&fast->next)
    {
        fast=fast->next->next;
        slow=slow->next;
    }

    return slow->val;
}


/**
 * ~toString: 输出当前链表 
 */
template<typename T>
string LinkedList<T>::toString() const
{
	string res;
	ListNode<T> *now=head->next;
	
	while(now)
	{
		res=res+((now==head->next)?"":"->")+to_string(now->val);	
		now=now->next;
	}
	
	return res;
}

/**
 * ~LinkedList: 析构函数
 */
template<typename T>
LinkedList<T>::~LinkedList() 
{
    ListNode<T> *now=head;

    while(now)
    {
        ListNode<T> *temp=now;
        now=now->next;
        delete temp;
    }
}

#endif
