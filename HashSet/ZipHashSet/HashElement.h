#ifndef HASHELEMENT_H
#define HASHELEMENT_H
#include <iostream>
#include <string> 

using namespace std;

/**
 * HashElement: 哈希元素接口抽象基类
 * note 1: 所有使用哈希集合或者哈希映射表存储的元素都必须继承该接口的抽象基类，并实现其中的hashCode和运算符=，并且必须重写拷贝函数，即实现clone方法
 */ 
class HashElement
{
    public:
    virtual int hashCode() const = 0;                               // 计算当前元素的哈希值 
    virtual bool operator== (const HashElement *other) const = 0;   // 相等运算符
    virtual HashElement *clone(const HashElement *other);           // 虚拷贝函数，虚拷贝函数传入一个基类指针，要求返回一个深拷贝对象的基类指针，编写该方法时必须要进行向下转型 
    virtual ~HashElement() {};                                      // 虚析构函数
};

#endif
