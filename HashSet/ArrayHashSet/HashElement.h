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
    virtual bool equals(const HashElement *other) const = 0;   	    // 相等运算符
    virtual HashElement *clone() const = 0;                         // 虚拷贝函数，虚拷贝函数拷贝自身对象 
    virtual string toString() const = 0;                            // 字符串输出当前元素 
    virtual ~HashElement() {};                                      // 虚析构函数
};

#endif
