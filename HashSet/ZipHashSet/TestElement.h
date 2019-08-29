#ifndef TESTELEMENT_H
#define TESTELEMENT_H
#include "HashElement.h"
#include <string>
#include <iostream>

using namespace std;

/**
 * TestElement: 继承HashElement的派生类，测试所使用的哈希表元素类型 
 */
class TestElement: public HashElement
{
	public:
	TestElement(int _val);                              		 // 默认构造函数 
	int hashCode() const override;                               // 计算当前元素的哈希值 
    bool operator== (const HashElement *other) const override;   // 相等运算符
    HashElement *clone(const HashElement *other) const override; // 虚拷贝函数，虚拷贝函数传入一个基类指针，要求返回一个深拷贝对象的基类指针，编写该方法时必须要进行向下转型 
    string toString() const override;                            // 字符串输出当前元素 
    ~TestElement() override;                                     // 虚析构函数
    
    private:
    int val;    // 实际存储的值，测试元素类型实际上就是简单封装的一个int值 
};

TestElement::TestElement(int _val)
{
	val=_val;
}

int TestElement::hashCode() const
{
	
}

bool TestElement::operator== (const HashElement *other) const
{
	
}

HashElement *TestElement::clone(const HashElement *other) const
{
	
}

string TestElement::toString() const
{
	return to_string(val);
}

TestElement::~TestElement() 
{
	
}                                 

#endif
