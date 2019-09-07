#include <iostream>
#include <string>
#include "Queue.h"

using namespace std;

/**
 * ArrayQueue: ����ջ 
 */
template<typename T>
class ArrayQueue: public Queue<T>
{
    public:   
    // 1. public constructor
    static ArrayQueue<T> *ArrayQueueFactory(int max_size);    // ���캯��

    // 2. copy_controller
    ArrayQueue(const ArrayQueue<T> &other);                   // �������캯��
    ArrayQueue<T> & operator = (const ArrayQueue<T> &other);  // ������ֵ�����
    ArrayQueue(ArrayQueue<T> &&other);                        // �ƶ����캯��
	ArrayQueue<T> &operator= (ArrayQueue<T> &&other);         // �ƶ���ֵ����� 

    // 3. methods
    bool push(T val) override;            // ������Ӳ���
    bool pop(T &val) override;            // ���г��Ӳ���
    bool frontval(T &val) const override; // ��ȡ����Ԫ��
    int length() const override;            // ������г��ȣ��������е�Ԫ�ظ���

    // 4. destructor
    ~ArrayQueue();

	private:
    int max_size;    // ��ǰ���д洢����Ĵ�С
    T *data;       // ջ����洢
    // �ж϶����Ƿ�Ϊ�յķ���������ʹ�û����������洢����Ԫ�أ����ҷ�������һ����Ԫ���������ֶӿպͶ������������������˵�front==end��������Ϊ�գ���(end+1)%max_size==beginʱ��������Ϊ��
    int front;       // ����Ԫ���±�
    int end;         // ��βԪ�ص�β��Ԫ�ص��±�

    // 5. private constructor
    ArrayQueue(int _max_size);
};

template<typename T>
ArrayQueue<T> *ArrayQueue<T>::ArrayQueueFactory(int _max_size) 
{
    if(_max_size<0)
    return NULL;
    else
    return new ArrayQueue<T>(_max_size+1);    // �����ܹ����_max_size��Ԫ�صĶ��У���Ӧ�Ĵ洢���鳤����Ҫ��_max_size+1
}

template<typename T>
ArrayQueue<T>::ArrayQueue(int _max_size)
{
    max_size=_max_size;
    data=new T [max_size];
    front=0;   // ��ʼ�Ķ���Ԫ���±�Ϊ0
    end=0;     // ��ʼ�Ķ�βԪ�ص�β��Ԫ���±�Ϊ0
}

template<typename T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue<T> &other)
{
    max_size=other.max_size;
    data=new T [max_size];
    front=other.front;
    end=other.end;

    for(int i=0;i<max_size;i++)
    {
        data[i]=other.data[i];
    }
}

template<typename T>
ArrayQueue<T> & ArrayQueue<T>::operator = (const ArrayQueue<T> &other)
{
    if(this==&other)
    return (*this);

    if(max_size!=other.max_size)
    {
        max_size=other.max_size;
        delete [] data;
        data=new T [max_size];
    }

    front=other.front;
    end=other.end;
    for(int i=0;i<max_size;i++)
    {
        data[i]=other.data[i];
    }

    return (*this);
}

template<typename T>
ArrayQueue<T>::ArrayQueue(ArrayQueue<T> &&other)
{
	max_size=other.max_size;
    data=other.data;
    front=other.front;
    end=other.end;

    other.data=new T [max_size];
    other.front=0;   // ��ʼ�Ķ���Ԫ���±�Ϊ0
    other.end=0;     // ��ʼ�Ķ�βԪ�ص�β��Ԫ���±�Ϊ0
}

template<typename T>
ArrayQueue<T> &ArrayQueue<T>::operator= (ArrayQueue<T> &&other)
{
	if(&other==this)
	return (*this);
	
	delete [] data;
	
	max_size=other.max_size;
    data=other.data;
    front=other.front;
    end=other.end;

    other.data=new T [max_size];
    other.front=0;   // ��ʼ�Ķ���Ԫ���±�Ϊ0
    other.end=0;     // ��ʼ�Ķ�βԪ�ص�β��Ԫ���±�Ϊ0
    
    return (*this);
}

template<typename T>
bool ArrayQueue<T>::push(T val)
{
    if((end+1)%max_size==front)    // ���ǰ��Ҫ�����ж϶����Ƿ�������frontָ����ף�endָ���β��β��Ԫ�أ����end����һ��Ԫ�ؾ���frontʱ����(end+1)%max_size==frontʱ����
    return false;
    else
    {
        data[end]=val;
        end=(end+1)%max_size;
        return true;
    }
}

template<typename T>
bool ArrayQueue<T>::pop(T &val)
{
    if(front==end)    // ����ǰ������Ҫ�ж϶����Ƿ��ѿգ���front==endʱ�ͱ����ӿ�
    return false;
    else
    {
        val=data[front];
        front=(front+1)%max_size;
        return true;
    }
}

template<typename T>
bool ArrayQueue<T>::frontval(T &val) const  
{
    if(front==end)   // ȡ����Ԫ�صĲ��������ͳ��Ӳ�����ͬ
    return false;
    else
    {
        val=data[front];
        return true;
    }
}

template<typename T>
int ArrayQueue<T>::length() const
{
    // ���������Ԫ�ظ����ı�׼��ʽ���ǣ�(end-front+max_size)%max_size���ټ����������ӿ����Ƶ��õ� 
    return (end-front+max_size)%max_size;
}

template<typename T>
ArrayQueue<T>::~ArrayQueue()
{
    delete [] data;
}
