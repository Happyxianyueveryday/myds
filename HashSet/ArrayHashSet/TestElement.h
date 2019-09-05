#ifndef TESTELEMENT_H
#define TESTELEMENT_H
#include "HashElement.h" 
#include <string>  
#include <iostream>

using namespace std;  

/**
 * TestElement: 继承HashElement的派生类，测试所使用的哈希表元素类型  
 * note: 本派生类提供了一个应当如何继承HashElement并重写其中的方法，来支持使用HashSet，ZipHashSet等 
 */
class TestElement: public HashElement
{
	public:
	TestElement(int _val);                              		 // 默认构造函数 
	int hashCode() const override;                               // 计算当前元素的哈希值 
    bool equals (const HashElement *other) const override;       // 相等运算符，相等运算符中必须要使用dynamic_cast 
    HashElement *clone() const override; 					     // 虚拷贝函数
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
	return val;
}

bool TestElement::equals(const HashElement *other) const
{
	const TestElement *other_cast=dynamic_cast<const TestElement *>(other);   // dynamic_cast用于类的向上转型和向下转型，类的向上转型和向下转型使用 
	if(!other_cast)                    // 如果dynamic_cast失败，这时输入的指针不是TestElement类对象，因此返回false 
	return false;
	else if(this->val==other_cast->val)// 如果dynamic_cast成功，且两者的值相等，则两个对象相等，返回true 
	return true;
	else                               // 其他情况，则两个对象不相等 
	return false;
}

HashElement *TestElement::clone() const
{
	return new TestElement(val);
}

string TestElement::toString() const
{
	return to_string(val);
}

TestElement::~TestElement() 
{
	//cout<<"TestElement的析构函数被调用"<<endl; 
}                                 

#endif
