#ifndef ZIPHASHSET_H
#define ZIPHASHSET_H
#include "HashSet.h"
#include "HashElement.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct ListNode
{
    ListNode(const HashElement *_val=NULL):val(_val), next(NULL)
    {
    }
    
    ~ListNode()
    {
    	if(val)         // 注意指针判空后再析构 
    	delete val;
	}
	 
    const HashElement *val;   // 当前结点存储的哈希元素对象，哈希表不提供修改对象的功能，因此将资源指针设置为顶层const 
    ListNode *next;     	  // 指向链表下一个结点的指针
};

class ZipHashSet: public HashSet
{
    public:
    // 1. constructor
    ZipHashSet();                                          // 默认构造函数
    ZipHashSet(const vector<HashElement *> &data);         // 从数组构造哈希表

    // 2. copy_controller
    ZipHashSet(const ZipHashSet &other);                   // 拷贝构造函数
    ZipHashSet &operator= (const ZipHashSet &other);       // 拷贝赋值运算符

    // 3. methods
    void insert(const HashElement *value) override;        // 向哈希表中插入指定值
    void remove(const HashElement *value) override;        // 从哈希表中移除指定值
    bool contain(const HashElement *value) const override; // 判断哈希表中是否包含指定值
    vector<const HashElement *> values() const override;   // 获得哈希表中所有值的列表
	string toString() const override;                      // 输出哈希表
    bool operator== (const HashElement &other);            // 相等判断运算符

    // 4. destructor
    ~ZipHashSet();                                         // 哈希表抽象基类虚析构函数

    private:
    // 5. domains
    ListNode **data;     // 哈希表数组结构
    int capacity;        // 哈希表桶的数量（即数组的长度），拉链法中，获取到元素的哈希值后将哈希值模桶数量，就可以得到具体的存放的桶的下标位置
    double load_factor;  // 哈希表负载因子
    int threshold;       // 哈希表扩容阈值，阈值=桶长度*负载因子，通常的拉链法哈希表的扩容策略是：在执行insert方法插入元素后，检查哈希表中的元素个数size是否大于阈值threshold，若大于，则调用resize方法进行扩容，具体的扩容方法请参见resize方法
    int size;            // 当前哈希表中的元素个数

    // 6. private functions
    void resize();       // 哈希表扩容方法
};

/**
 * ZipHashSet: 默认构造函数
 */
ZipHashSet::ZipHashSet()
{
	size=0;    									// 初始化元素个数为0
	capacity=16;        						// 默认桶的数量初始值为16
	load_factor=0.75;   						// 默认的负载因子初始值为0.75
	threshold=capacity*load_factor;        		// 哈希表扩容阈值，其值始终等于桶数量乘以负载因子
	data=new ListNode* [capacity];     			// 初始化桶，其中每个桶中的链表具有一个头部哑结点
	
	for(int i=0;i<capacity;i++)
	{
		data[i]=new ListNode(NULL);
	}
}

ZipHashSet::ZipHashSet(const vector<HashElement *> &data)
{
	 
}

ZipHashSet::ZipHashSet(const ZipHashSet &other)
{

}

ZipHashSet &ZipHashSet::operator= (const ZipHashSet &other)
{

}

void ZipHashSet::insert(const HashElement *value)
{
	// 1. 传入指针判空，若传入指针为空，或者传入的值已经存在于哈希集合中，则无需进行插入 
	if(!value||this->contain(value))
	return;
	// 2. 计算应当插入的桶位置
	int index=(value->hashCode())%capacity;
	// 4. 将对象插入到对应的桶中
	ListNode *now=data[index];
	ListNode *newnode=new ListNode(value);
	newnode->next=now->next;
	now->next=newnode;
	// 5. 增加元素计数，判断是否需要扩容，若元素数量size大于阈值threshold，则调用resize方法进行扩容
	size+=1;
	if(size>threshold)
	resize();
	
	return; 
}

void ZipHashSet::remove(const HashElement *value) 
{
	
}

bool ZipHashSet::contain(const HashElement *value) const 
{
	// 1. 输入指针判空
	if(!value)
	return false;
	// 2. 计算应该所在的桶位置
	int index=(value->hashCode())%capacity;
	// 3. 从该桶的第一个链表结点开始依次进行比较
	// note: 比较算法是：首先调用hashCode对两个对象进行比较，若hashCode值相等，则调用==运算符进行进一步比较判断是否相等；若hashCode不相等，则直接认为两个对象不相等 
	ListNode *now=data[index]->next;
	while(now)
	{
		if(now->val->hashCode()==value->hashCode()&&now->val->equals(value))
		return true;
		else
		now=now->next;
	}
	return false;
}

vector<const HashElement *> ZipHashSet::values() const
{

}

string ZipHashSet::toString() const
{
    string res;
    for(int i=0;i<capacity;i++)
    {
    	if(i==0)
    	res+="*";
    	else
    	res+="\n*";
    	
    	const ListNode *now=data[i]->next;
    	while(now)
    	{
    		res=res+"->"+now->val->toString();
    		now=now->next;
		}
		res=res+"->NULL";
	}
	return res;
}

bool ZipHashSet::operator== (const HashElement &other)
{
	
}

void ZipHashSet::resize()
{
	
}

ZipHashSet::~ZipHashSet()
{
	for(int i=0;i<capacity;i++)
	{
		ListNode *now=data[i];
		while(now)
		{
			ListNode *temp=now;
			now=now->next;
			delete temp;
		}
	}
}

#endif
