#include <iostream>
#include <string>
#include "Queue.h"

using namespace std;

/**
 * ArrayQueue: ����ջ 
 */
class ArrayQueue: public Queue
{
    public:   
    // 1. public constructor
    static ArrayQueue *ArrayQueueFactory(int max_size);    // ���캯��

    // 2. copy_controller
    ArrayQueue(const ArrayQueue &other);                   // �������캯��
    ArrayQueue & operator = (const ArrayQueue &other);     // ������ֵ�����
    ArrayQueue(ArrayQueue &&other);                        // �ƶ����캯��
	ArrayQueue &operator= (ArrayQueue &&other);            // �ƶ���ֵ����� 

    // 3. methods
    bool push(int val) override;            // ������Ӳ���
    bool pop(int &val) override;            // ���г��Ӳ���
    bool frontval(int &val) const override; // ��ȡ����Ԫ��
    int length() const override;            // ������г��ȣ��������е�Ԫ�ظ���

    // 4. destructor
    ~ArrayQueue();

	private:
    int max_size;    // ��ǰ���д洢����Ĵ�С
    int *data;       // ջ����洢
    // �ж϶����Ƿ�Ϊ�յķ���������ʹ�û����������洢����Ԫ�أ����ҷ�������һ����Ԫ���������ֶӿպͶ������������������˵�front==end��������Ϊ�գ���(end+1)%max_size==beginʱ��������Ϊ��
    int front;       // ����Ԫ���±�
    int end;         // ��βԪ�ص�β��Ԫ�ص��±�

    // 5. private constructor
    ArrayQueue(int _max_size);
};

ArrayQueue *ArrayQueue::ArrayQueueFactory(int _max_size) 
{
    if(_max_size<0)
    return NULL;
    else
    return new ArrayQueue(_max_size+1);    // �����ܹ����_max_size��Ԫ�صĶ��У���Ӧ�Ĵ洢���鳤����Ҫ��_max_size+1
}

ArrayQueue::ArrayQueue(int _max_size)
{
    max_size=_max_size;
    data=new int [max_size];
    front=0;   // ��ʼ�Ķ���Ԫ���±�Ϊ0
    end=0;     // ��ʼ�Ķ�βԪ�ص�β��Ԫ���±�Ϊ0
}

ArrayQueue::ArrayQueue(const ArrayQueue &other)
{
    max_size=other.max_size;
    data=new int [max_size];
    front=other.front;
    end=other.end;

    for(int i=0;i<max_size;i++)
    {
        data[i]=other.data[i];
    }
}

ArrayQueue & ArrayQueue::operator = (const ArrayQueue &other)
{
    if(this==&other)
    return (*this);

    if(max_size!=other.max_size)
    {
        max_size=other.max_size;
        delete [] data;
        data=new int [max_size];
    }

    front=other.front;
    end=other.end;
    for(int i=0;i<max_size;i++)
    {
        data[i]=other.data[i];
    }

    return (*this);
}

ArrayQueue::ArrayQueue(ArrayQueue &&other)
{
	max_size=other.max_size;
    data=other.data;
    front=other.front;
    end=other.end;

    other.data=new int [max_size];
    other.front=0;   // ��ʼ�Ķ���Ԫ���±�Ϊ0
    other.end=0;     // ��ʼ�Ķ�βԪ�ص�β��Ԫ���±�Ϊ0
}

ArrayQueue &ArrayQueue::operator= (ArrayQueue &&other)
{
	if(&other==this)
	return (*this);
	
	delete [] data;
	
	max_size=other.max_size;
    data=other.data;
    front=other.front;
    end=other.end;

    other.data=new int [max_size];
    other.front=0;   // ��ʼ�Ķ���Ԫ���±�Ϊ0
    other.end=0;     // ��ʼ�Ķ�βԪ�ص�β��Ԫ���±�Ϊ0
    
    return (*this);
}

bool ArrayQueue::push(int val)
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

bool ArrayQueue::pop(int &val)
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

bool ArrayQueue::frontval(int &val) const 
{
    if(front==end)   // ȡ����Ԫ�صĲ��������ͳ��Ӳ�����ͬ
    return false;
    else
    {
        val=data[front];
        return true;
    }
}

int ArrayQueue::length() const
{
    // ���������Ԫ�ظ����ı�׼��ʽ���ǣ�(end-front+max_size)%max_size���ټ����������ӿ����Ƶ��õ� 
    return (end-front+max_size)%max_size;
}

ArrayQueue::~ArrayQueue()
{
    delete [] data;
}
