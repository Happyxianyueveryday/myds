#ifndef HASHSET_H
#define HASHSET_h
#include "HashElement.h" 
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * HashSet: 哈希集合接口抽象基类 
 * note 1: 这里详细说明哈希表对于元素的复制策略，哈希表接口中的参数都使用了元素基类HashElement的指针，在实际插入时使用深拷贝，插入一个与输入指针对象相等的新对象，返回列表时返回的也是新对象，需要用户来进行资源的释放
 * note 2: 只要使用指针参数的函数重写时都必须仔细判空，且注意NULL和nullptr的区别  
 */
class HashSet
{
    public:
    virtual void insert(const HashElement *value) = 0 ;       // 向哈希表中插入指定值 
    virtual void remove(const HashElement *value) = 0;        // 从哈希表中移除指定值
    virtual bool contain(const HashElement *value) const = 0; // 判断哈希表中是否包含指定值
    virtual vector<HashElement *> values() const = 0;         // 获得哈希表中所有值的列表
    virtual string toString() const = 0;                      // 输出哈希表
    virtual ~HashSet() {}                                     // 哈希表抽象基类虚析构函数
};

#endif
