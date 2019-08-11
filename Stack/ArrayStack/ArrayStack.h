#include <iostream>
#include <string>

using namespace std;

/**
 * ArrayStack: ����ջ
 */
class ArrayStack 
{
    public:   
    // 1. public constructor
    static ArrayStack *arrayStackFactory(int max_size);

    // 2. copy_controller
    ArrayStack(const ArrayStack &other);
    ArrayStack & operator = (const ArrayStack &other);

    // 3. methods
    bool push(int val);
    bool pop(int &val);
    bool top(int &val) const;
    int length() const;

    // 4. destructor
    ~ArrayStack();

    int size;        // ��ǰջ��Ԫ�ظ���
    int max_size;   // ��ǰջ����������Ԫ�ظ���
    int *data;       // ջ����洢
    int pos;         // ջ��ָ��λ��

    // 5. private constructor
    ArrayStack(int _max_size);
};

ArrayStack *ArrayStack::arrayStackFactory(int max_size)
{
    if(max_size<0)
    return NULL;
    else
    return new ArrayStack(max_size);
}

ArrayStack::ArrayStack(int _max_size)
{
    size=0;
    max_size=_max_size;
    data=new int [max_size];
    pos=-1;
}

ArrayStack::ArrayStack(const ArrayStack &other)
{
    size=other.size;
    max_size=other.max_size;
    data=new int [max_size];
    pos=other.pos;

    for(int i=0;i<pos;i++)
    {
        data[i]=other.data[i];
    }
}

ArrayStack & ArrayStack::operator = (const ArrayStack &other)
{
    if(this==&other)
    return (*this);

    if(max_size!=other.max_size)
    {
        delete [] data;
        data=new int [other.max_size];
    }

    size=other.size;
    max_size=other.max_size;
    pos=other.pos;
    for(int i=0;i<=pos;i++)
    {
        data[i]=other.data[i];
    }
    return (*this);
}

bool ArrayStack::push(int val)
{
    if(size>=max_size)
    return false;
    else
    {
        pos+=1;
        data[pos]=val;
        size+=1;
        return true;
    }
}

bool ArrayStack::pop(int &val)
{
    if(pos==-1)  // ����ʹ������size==0
    return false;
    else
    {
        val=data[pos];
        pos-=1;
        size-=1;
        return true;
    }
}

bool ArrayStack::top(int &val) const
{
    if(pos==-1)  // ����ʹ������size==0
    return false;
    else
    {
    	val=data[pos];
    	return true;
	}
}

int ArrayStack::length() const
{
    return size;
}

ArrayStack::~ArrayStack()
{
    delete data;
}
