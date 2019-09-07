#include <iostream>

using namespace std;   
 
/**
 * Stack: 栈的抽象基类 
 */
template<typename T>
class Stack
{
	public:
	virtual bool push(T val) = 0;    	     // 入栈操作
    virtual bool pop(T &val) = 0;          // 出栈操作
    virtual bool top(T &val) const = 0;    // 获取栈顶元素操作
    virtual int length() const = 0;          // 获取栈的元素个数 
    virtual ~Stack()                         // 虚析构函数 
	{
	}
};
