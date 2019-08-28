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
    ListNode(HashElement *_val):val(_val), next(NULL)
    {
    }

    HashElement *val;   // 当前结点存储的哈希元素对象
    ListNode *next;     // 指向链表下一个结点的指针
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
    bool operator== (const HashElement &other);            // 相等判断运算符

    // 3. methods
    void insert(const HashElement *value) override;        // 向哈希表中插入指定值
    void remove(const HashElement *value) override;        // 从哈希表中移除指定值
    bool contain(const HashElement *value) const override; // 判断哈希表中是否包含指定值
    vector<HashElement *> values() const override;         // 获得哈希表中所有值的列表
    string toString() const override;                      // 输出哈希表 

    // 4. destructor 
    ~ZipHashSet();                                         // 哈希表抽象基类虚析构函数

    private: 
    // 5. domains
    ListNode *data;      // 哈希表数组结构
    int capacity;        // 哈希表桶（数组）长度
    int threshold;       // 哈希表扩容阈值，阈值=桶长度*负载因子，通常的拉链法哈希表的扩容策略是：在执行insert方法插入元素后，检查哈希表中的元素个数size是否大于阈值threshold，若大于，则调用resize方法进行扩容，具体的扩容方法请参见resize方法 
    int load_factor;     // 哈希表负载因子
    int size;            // 当前哈希表中的元素个数 
    
    // 6. private functions
    void resize();       // 哈希表扩容方法 
};

/**
 * ZipHashSet: 初始化空哈希集合
 */
ZipHashSet::ZipHashSet()
{
    capacity=16;     // 哈希表初始数组长度（哈希位）为16

}

void ZipHashSet::insert(const HashElement *value) 
{

}

void ZipHashSet::remove(const HashElement *value) 
{

}

bool ZipHashSet::contain(const HashElement *value) const 
{

}

vector<HashElement *> ZipHashSet::values() const 
{

}

string ZipHashSet::toString() const
{
    
}

ZipHashSet::~ZipHashSet()
{

}

#endif
