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

/**
 * ZipHashSet: 拉链法实现的哈希集合
 * note: 首先明确哈希集合的拷贝问题，涉及到深浅拷贝的问题均在各个方法中已经标记 
 */
class ZipHashSet: public HashSet
{
    public:
    // 1. constructor
    ZipHashSet();                                          // 默认构造函数
    ZipHashSet(const vector<HashElement *> &data);         // 从数组构造哈希表

    // 2. copy/move_controller
    ZipHashSet(const ZipHashSet &other);                   // 拷贝构造函数（深拷贝） 
    ZipHashSet &operator= (const ZipHashSet &other);       // 拷贝赋值运算符（深拷贝） 
    ZipHashSet(ZipHashSet &&other);                        // 移动构造函数 （浅拷贝/移动）
	ZipHashSet &operator= (ZipHashSet &&other);            // 移动赋值运算符（浅拷贝/移动） 

    // 3. methods
    void insert(const HashElement *value) override;        // 向哈希表中插入指定值
    void remove(const HashElement *value) override;        // 从哈希表中移除指定值
    bool contain(const HashElement *value) const override; // 判断哈希表中是否包含指定值
    vector<const HashElement *> values() const override;   // 获得哈希表中所有值的列表
    int length() const override;                           // 获取哈希表的元素个数 
	string toString() const override;                      // 输出哈希表
    bool operator== (const ZipHashSet &other);             // 相等判断运算符

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

/**
 * ZipHashSet: 从数组构造哈希集合 
 * param data: 用于构造的原始输入数组 
 * note: 考虑到执行效率，该方法对输入对象进行浅拷贝，用户创建的HashElement派生类对象将会直接加入到哈希表中，这些加入的对象由当前的ZipHashSet类在析构函数进行释放 
 */
ZipHashSet::ZipHashSet(const vector<HashElement *> &_data)
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
	
	for(int i=0;i<_data.size();i++)
	{
		this->insert(_data[i]);
	}
}

/**
 * ZipHashSet: 拷贝构造函数 
 * note: 考虑到容器中存放的元素为对象指针，因此拷贝构造函数使用深拷贝 
 */
ZipHashSet::ZipHashSet(const ZipHashSet &other)
{
	size=other.size;    									
	capacity=other.capacity;        						
	load_factor=other.load_factor;   						
	threshold=capacity*load_factor;
	data=new ListNode* [capacity];     		
	
	for(int i=0;i<capacity;i++)
	{
		data[i]=new ListNode(NULL);
		ListNode *now=data[i], *othnow=other.data[i]->next;
		while(othnow)
		{
			now->next=new ListNode(othnow->val->clone());   // 使用拷贝构造函数或者拷贝赋值运算符时必须深拷贝哈希表元素 
			now=now->next;
			othnow=othnow->next;
		}
	}
}

/**
 * operator=: 拷贝赋值运算符 
 * note: 考虑到容器中存放的指针为对象指针，因此拷贝赋值运算符使用深拷贝 
 */
ZipHashSet &ZipHashSet::operator= (const ZipHashSet &other)
{
	if(this==&other)
	return (*this);
	
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
	delete data;
	
	size=other.size;    									
	capacity=other.capacity;        						
	load_factor=other.load_factor;   						
	threshold=capacity*load_factor;
	data=new ListNode* [capacity];     		
	
	for(int i=0;i<capacity;i++)
	{
		data[i]=new ListNode(NULL);
		ListNode *now=data[i], *othnow=other.data[i]->next;
		while(othnow)
		{
			now->next=new ListNode(othnow->val->clone());   // 使用拷贝构造函数或者拷贝赋值运算符时必须深拷贝哈希表元素 
			now=now->next;
			othnow=othnow->next;
		}
	}
	
	return (*this);
}

/**
 * ZipHashSet: 移动构造函数 
 */
ZipHashSet::ZipHashSet(ZipHashSet &&other)
{
	// 1. 从拷贝源对象浅拷贝成员变量的值到当前变量 
	size=other.size;           // 哈希表元素个数 
	capacity=other.capacity;   // 哈希表桶个数
	load_factor=other.load_factor;   // 装载因子
	threshold=capacity*load_factor;  // 扩容阈值 
	data=other.data;                 // 底层存储结构指针
	
	// 2. 将拷贝源对象的成员变量的值设定为默认值（即默认构造函数中的取值）
	other.size=0;    								
	other.capacity=16;        					
	other.load_factor=0.75;   					
	other.threshold=capacity*load_factor;        		
	other.data=new ListNode* [capacity];     			
	
	for(int i=0;i<capacity;i++)
	{
		other.data[i]=new ListNode(NULL);
	}
}

ZipHashSet &ZipHashSet::operator= (ZipHashSet &&other)
{
	// 1. 判断是否为自身赋值
	if(this==&other)
	return (*this);
	
	// 2. 释放自身对象所使用的堆空间资源
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
	
	// 3. 从拷贝源对象浅拷贝成员变量的值到当前变量 
	size=other.size;           // 哈希表元素个数 
	capacity=other.capacity;   // 哈希表桶个数
	load_factor=other.load_factor;   // 装载因子
	threshold=capacity*load_factor;  // 扩容阈值 
	data=other.data;                 // 底层存储结构指针
	
	// 4. 将拷贝源对象的成员变量的值设定为默认值（即默认构造函数中的取值）
	other.size=0;    								
	other.capacity=16;         	 				
	other.load_factor=0.75;   					
	other.threshold=capacity*load_factor;        		
	other.data=new ListNode* [capacity];     			
	
	for(int i=0;i<capacity;i++)
	{
		other.data[i]=new ListNode(NULL);
	}
	
	// 5. 返回当前对象的引用
	return (*this);
}

/**
 * insert: 向哈希集合中插入元素值
 * note 1: 若插入的元素值在哈希集合中已经存在重复，则不会进行插入 
 */
void ZipHashSet::insert(const HashElement *value) 
{
	// 1. 传入指针判空，若传入指针为空，或者传入的值已经存在于哈希集合中，则无需进行插入 
	if(!value||this->contain(value))
	return;
	// 2. 计算应当插入的桶位置
	int index=(value->hashCode())%capacity;
	// 4. 将对象插入到对应的桶中
	ListNode *now=data[index];
	ListNode *newnode=new ListNode(value->clone());
	newnode->next=now->next;
	now->next=newnode;
	// 5. 增加元素计数，判断是否需要扩容，若元素数量size大于阈值threshold，则调用resize方法进行扩容
	size+=1;
	if(size>threshold)
	resize();
	
	return; 
}

/**
 * remove: 从哈希集合中删除指定值的元素
 * note: 若哈希集合中不存在该值，则实际上不会进行删除 
 */
void ZipHashSet::remove(const HashElement *value) 
{
	// 1. 传入指针判空，若传入指针为空，则无需进行删除
	if(!value)
	return; 
	// 2. 计算待删除的值在哈希表中的位置
	int index=(value->hashCode())%capacity; 
	// 3. 遍历该桶中的链表，查找目标值的哈希表元素，前置双指针法进行删除 
	ListNode *nowprev=data[index];   
	ListNode *now=data[index]->next;
	while(now)
	{
		// 比较时使用和插入相同的算法，先使用hashCode方法比较，若相等则再调用equals方法比较，若不相等则直接认为比较的两个元素不相等 
		if(now->val->hashCode()==value->hashCode()&&now->val->equals(value))  
		{
			nowprev->next=now->next;
			delete now;
			size-=1;
			break;
		}	
		else
		{
			nowprev=now;
			now=now->next;
		}
	}
	return;
}

/**
 * contain: 判断给定值是否在哈希表中
 * note: 若给定值在哈希表中则返回true，否则返回false 
 */
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

/**
 * values: 获取哈希集合中的所有值的列表
 * return: 哈希集合中的所有元素的底层const指针
 * note: 返回底层const的指针主要是为了保护哈希表中的数据不被用户自行修改 
 */
vector<const HashElement *> ZipHashSet::values() const
{
	vector<const HashElement *> res;
	for(int i=0;i<capacity;i++)
	{
		ListNode *now=data[i]->next;
		while(now)
		{
			res.push_back(now->val);
			now=now->next;
		}
	}
	return res;
}

/**
 * length: 获取哈希表的元素个数 
 */
int ZipHashSet::length() const
{
	return size;
}

/**
 * toString: 生成哈希表的输出字符串 
 */
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

/** 
 * operator==: 判断两个哈希集合是否相等
 * note: 判断两个拉链法哈希表是否相等的算法存在很大的优化空间，需要进行深度的优化而不能随便设计。同时需要提醒的是：因为插入删除等操作的顺序不相同，并不能通过直接比较两个哈希表的结构来比较两个哈希表是否相等
 * note: 因此这里使用的比较算法如下：
 *       1. 首先判断传入的other指针地址是否和this指针相等，若相等，则直接返回true；否则进入步骤2
 *		 2. 然后判断传入的哈希集合中的元素数量是否和当前哈希集合相等，若不相等，则直接返回true；否则进入步骤3
 *       3. 最后，依次判断当前哈希集合中的每一个元素是否在哈希集合other中，若均存在，则直接返回true，否则返回false		 
 */ 
bool ZipHashSet::operator== (const ZipHashSet &other)
{
	if(&other==this)
	return true;
	else if(this->length()!=other.length())
	return false;
	for(int i=0;i<capacity;i++)
	{
		ListNode *now=data[i]->next;
		while(now)
		{
			if(this->contain(now->val))
			now=now->next;
			else
			return false;
		}
	}
	return true;
}

/**
 * resize: 哈希扩容方法
 * note 1: 何时发生哈希扩容？
 *         答：只要在执行插入操作后，哈希表中的元素数量size大于桶的数量capacity乘以一个负载因子系数(load_factor)时就发生哈希扩容，即发生条件为: size>capacity*load_factor 
 * note 2: 哈希扩容具体算法步骤： 
 *         答：1. 将桶的数量(capacity)扩容为原先的两倍，即: capacity=2*capacity
 *			   2. 重新计算阈值，即: threshoud=capacity*load_factor，其中load_factor为负载因子，固定为0.75 
 *			   3. 创建新的桶数组
 *			   4. 将旧桶数组中的链表按照与之前相同算法重新计算哈希值和插入位置，并使用浅拷贝移动到新桶数组，即: index=(element->hashCode())%capacity 
 *			   5. 释放旧桶数组，新的桶数组作为当前哈希表的桶数组 
 */
void ZipHashSet::resize() 
{
	// 1. 将桶数量capacity加倍
	int old_capacity=capacity;
	capacity*=2;
	// 2. 重新计算阈值threshoud
	threshold=capacity*load_factor;
	// 3. 创建新的桶数组，并且将原桶数组中的元素依次使用与原来相同的哈希算法插入到新的桶数组中
	ListNode **new_data=new ListNode* [capacity];
	for(int i=0;i<capacity;i++)
	{
		new_data[i]=new ListNode(NULL);
	}
	for(int i=0;i<old_capacity;i++)
	{
		if(data[i]->next)
		{
			int index=(data[i]->next->val->hashCode())%capacity;   // 因为在一个桶中的元素原先的哈希值模桶数量都是相等的，进行扩容后也是相等的，因此只需要计算第一个元素的哈希值
			delete new_data[index];
			new_data[index]=data[i];
		}
	}
	data=new_data;
}

/**
 * ~ZipHashSet: 虚析构函数 
 */
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
	delete data;
}

#endif
