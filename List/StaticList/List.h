#ifndef LIST_H
#define LIST_H
#include <string>

using namespace std; 

class List  
{
	public:
	virtual bool get(int index, int &val) const = 0;    // 链表指定位置获取元素 
    virtual bool insert(int index, int val) = 0;        // 链表指定位置插入元素
    virtual bool remove(int index, int &val) = 0;       // 链表指定位置删除元素
    virtual int length() const = 0;                     // 获取链表的长度
    virtual void reverse() = 0;                         // 原地反转单向链表
    virtual int middle() const = 0;                     // 返回链表中间结点的值
    virtual string toString() const = 0;                // 输出当前链表 
	virtual ~List() {};                                 // 虚析构函数 
};

#endif 
