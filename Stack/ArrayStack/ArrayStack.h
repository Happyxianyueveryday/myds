#include <iostream>
#include <string>
#include "Stack.h" 

using namespace std;  

/**
 * ArrayStack: 数组栈
 */
template<typename T>
class ArrayStack: public Stack<T>
{
    public:   
    // 1. public constructor
    static ArrayStack<T> *arrayStackFactory(int max_size);

    // 2. copy/move_controller
    ArrayStack(const ArrayStack<T> &other);
    ArrayStack<T> &operator= (const ArrayStack<T> &other);
    ArrayStack(ArrayStack<T> &&other);
    ArrayStack<T> &operator= (ArrayStack<T> &&other);

    // 3. methods
    bool push(T val);
    bool pop(T &val);
    bool top(T &val) const;
    int length() const;

    // 4. destructor
    ~ArrayStack();

    int size;         // 当前栈中元素个数
    int max_size;     // 当前栈的最大可容纳元素个数
    T *data;          // 栈数组存储
    int pos;          // 栈顶指针位置

    // 5. private constructor
    ArrayStack(int _max_size);
};

template<typename T>
ArrayStack<T> *ArrayStack<T>::arrayStackFactory(int max_size)
{
    if(max_size<0)
    return NULL;
    else
    return new ArrayStack<T>(max_size);
}

template<typename T>
ArrayStack<T>::ArrayStack(int _max_size)
{
    size=0;
    max_size=_max_size;
    data=new T [max_size];
    pos=-1;
}

template<typename T>
ArrayStack<T>::ArrayStack(const ArrayStack<T> &other)
{
    size=other.size;
    max_size=other.max_size;
    data=new T [max_size];
    pos=other.pos;

    for(int i=0;i<pos;i++)
    {
        data[i]=other.data[i];
    }
}

template<typename T>
ArrayStack<T> & ArrayStack<T>::operator= (const ArrayStack<T> &other)
{
    if(this==&other)
    return (*this);

    if(max_size!=other.max_size)
    {
        delete [] data;
        data=new T [other.max_size];
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

template<typename T>
ArrayStack<T>::ArrayStack(ArrayStack &&other)
{
	size=other.size;
    max_size=other.max_size;
    data=other.data;
    pos=other.pos;
    
    other.size=0;
    other.data=new T [other.max_size];
    other.pos=-1;
}

template<typename T>
ArrayStack<T> &ArrayStack<T>::operator= (ArrayStack<T> &&other)
{
	if(&other==this)
	return (*this);
	
	delete [] data;
	
	size=other.size;
    max_size=other.max_size;
    data=other.data;
    pos=other.pos;
    
    other.size=0;
    other.data=new T [other.max_size];
    other.pos=-1;
    
    return (*this);
}

template<typename T>
bool ArrayStack<T>::push(T val)  
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

template<typename T>
bool ArrayStack<T>::pop(T &val)
{
    if(pos==-1)  // 或者使用条件size==0
    return false;
    else
    {
        val=data[pos];
        pos-=1;
        size-=1;
        return true;
    }
}

template<typename T>
bool ArrayStack<T>::top(T &val) const
{
    if(pos==-1)  // 或者使用条件size==0
    return false;
    else
    {
    	val=data[pos];
    	return true;
	}
}

template<typename T>
int ArrayStack<T>::length() const
{
    return size;
}

template<typename T>
ArrayStack<T>::~ArrayStack()
{
    delete data;
}
