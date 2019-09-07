#include <iostream>

using namespace std;   
 
/**
 * Stack: ջ�ĳ������ 
 */
template<typename T>
class Stack
{
	public:
	virtual bool push(T val) = 0;    	     // ��ջ����
    virtual bool pop(T &val) = 0;          // ��ջ����
    virtual bool top(T &val) const = 0;    // ��ȡջ��Ԫ�ز���
    virtual int length() const = 0;          // ��ȡջ��Ԫ�ظ��� 
    virtual ~Stack()                         // ���������� 
	{
	}
};
