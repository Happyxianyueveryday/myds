#include <iostream>

using namespace std;
 
/**
 * Stack: ջ�ĳ������ 
 */
class Stack
{
	public:
	virtual bool push(int val) = 0;    	     // ��ջ����
    virtual bool pop(int &val) = 0;          // ��ջ����
    virtual bool top(int &val) const = 0;    // ��ȡջ��Ԫ�ز���
    virtual int length() const = 0;          // ��ȡջ��Ԫ�ظ��� 
    virtual ~Stack()                         // ���������� 
	{
	}
};
