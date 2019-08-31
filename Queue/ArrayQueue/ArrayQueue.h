#include <iostream>
#include <string>
#include "Queue.h"

using namespace std;

/**
 * ArrayQueue: 数组栈 
 */
class ArrayQueue: public Queue
{
    public:   
    // 1. public constructor
    static ArrayQueue *ArrayQueueFactory(int max_size);    // 构造函数

    // 2. copy_controller
    ArrayQueue(const ArrayQueue &other);                   // 拷贝构造函数
    ArrayQueue & operator = (const ArrayQueue &other);     // 拷贝赋值运算符
    ArrayQueue(ArrayQueue &&other);                        // 移动构造函数
	ArrayQueue &operator= (ArrayQueue &&other);            // 移动赋值运算符 

    // 3. methods
    bool push(int val) override;            // 队列入队操作
    bool pop(int &val) override;            // 队列出队操作
    bool frontval(int &val) const override; // 获取队首元素
    int length() const override;            // 计算队列长度，即队列中的元素个数

    // 4. destructor
    ~ArrayQueue();

	private:
    int max_size;    // 当前队列存储数组的大小
    int *data;       // 栈数组存储
    // 判断队列是否为空的方法：这里使用环形数组来存储队列元素，并且放弃其中一个单元不用来区分队空和队满两种特殊情况，因此当front==end表明队列为空，当(end+1)%max_size==begin时表明队列为满
    int front;       // 队首元素下标
    int end;         // 队尾元素的尾后元素的下标

    // 5. private constructor
    ArrayQueue(int _max_size);
};

ArrayQueue *ArrayQueue::ArrayQueueFactory(int _max_size) 
{
    if(_max_size<0)
    return NULL;
    else
    return new ArrayQueue(_max_size+1);    // 创建能够存放_max_size个元素的队列，对应的存储数组长度需要是_max_size+1
}

ArrayQueue::ArrayQueue(int _max_size)
{
    max_size=_max_size;
    data=new int [max_size];
    front=0;   // 初始的队首元素下标为0
    end=0;     // 初始的队尾元素的尾后元素下标为0
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
    other.front=0;   // 初始的队首元素下标为0
    other.end=0;     // 初始的队尾元素的尾后元素下标为0
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
    other.front=0;   // 初始的队首元素下标为0
    other.end=0;     // 初始的队尾元素的尾后元素下标为0
    
    return (*this);
}

bool ArrayQueue::push(int val)
{
    if((end+1)%max_size==front)    // 入队前需要首先判断队列是否已满，front指向队首，end指向队尾的尾后元素，因此end的下一个元素就是front时，即(end+1)%max_size==front时队满
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
    if(front==end)    // 出队前首先需要判断队列是否已空，当front==end时就表明队空
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
    if(front==end)   // 取队首元素的操作基本和出队操作相同
    return false;
    else
    {
        val=data[front];
        return true;
    }
}

int ArrayQueue::length() const
{
    // 计算队列中元素个数的标准公式就是：(end-front+max_size)%max_size，举几个常见例子可以推导得到 
    return (end-front+max_size)%max_size;
}

ArrayQueue::~ArrayQueue()
{
    delete [] data;
}
