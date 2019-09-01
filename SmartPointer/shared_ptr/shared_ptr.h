#ifndef SHARED_PTR_H
#define SHARED_PTR_H
#include <iostream>
#include <string>

using namespace std;

/**
 * shared_ptr: 智能指针类模板 
 */
template<class T> class shared_ptr
{
	public: 
	// 1. constructor
	shared_ptr();     			       // 默认构造函数
	
	// 2. copy/move controller
	shared_ptr(shared_ptr &other);                     // 拷贝构造函数 
	shared_ptr<T> &operator= (shared_ptr &other);         // 拷贝赋值运算符 
	shared_ptr(shared_ptr &&other) = delete;                 // shared_ptr类的智能指针禁用移动构造函数 
	shared_ptr<T> &operator= (shared_ptr && other) = delete;     // shared_ptr类的智能指针禁用移动赋值运算符 
	
	// 3. methods
	T &operator* () const;            // 解引用运算符：解引用运算符应当始终返回当前对象的引用 
	T *operator-> () const;           // 箭头运算符：箭头运算符应当始终返回指向当前对象的指针，即this指针 
	bool unique() const;              // 判断所指向对象的智能指针是否唯一 
	
	// 4. destructor
	~shared_ptr();                    // 析构函数 
	
	private:
	// 5. domain
	T *data;                          // 智能指针所指向的对象的裸指针 
	int *count;                       // 对象的引用计数 
};

/**
 * shared_ptr: 初始化一个智能指针指向对应类型的新对象 
 */
template<typename T>
shared_ptr<T>::shared_ptr()
{
	data=new T();       // 初始化对象指针 
	count=new int(1);   // 初始化引用计数（注意必须使用计数的指针，原因很好理解，这里不再解析 
}
	
/** 
 * shared_ptr: 拷贝构造函数 
 * note: 拷贝构造函数首先将源指针的引用计数加1, 然后浅拷贝（重要）源指针的对象指针和引用计数指针。因为拷贝源指针所指向的对象的引用数增加了1 
 */
template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr &other)
{
	// 1. 将源指针引用计数增加1 
	*(other.count)+=1;
	// 2. 浅拷贝源指针的对象指针和引用计数指针
	data=other.data; 
	count=other.count;
}

/**
 * operator=: 拷贝赋值运算符  
 * note: 因为赋值操作是将等号右侧的值赋值给左边，因此：
 *       1. 拷贝赋值运算符首先将源指针所指向对象的引用计数增加1，然后将当前指针所指向对象的引用计数减小1
 *	     2. 若减小1后等于0，则释放当前指针指向的对象
 *       3. 最后从源指针浅拷贝成员 
 */
template<typename T>
shared_ptr<T> &shared_ptr<T>::operator= (shared_ptr &other)  
{
	// 1. 判断是否为自身引用 
	if(&other==this)
	return (*this);
	// 2. 将源指针所指向对象的引用计数加1，将当前指针所指向对象的引用计数减1 
	*(other.count)+=1;
	*count-=1;
	// 3. 若减小1后当前指针指向对象引用计数为0，则析构所指向的对象 
	if(*count==0)
	delete data; 
	// 4. 从源对象浅拷贝源对象指针和引用计数指针 
	data=other.data;
	count=other.count;
	// 5. 返回当前指针
	return (*this);
}

/**
 * operator*: 解引用运算符
 * note: 解引用运算符直接返回当前对象的引用即可 
 */ 
template<typename T>
T &shared_ptr<T>::operator* () const
{
	return *data;
}

/**
 * operator->: 箭头运算符 
 * note: 箭头运算符直接返回当前指针所指向的对象的指针即可 
 */ 
template<typename T>
T *shared_ptr<T>::operator-> () const
{
	return data;
}

/**
 * unique: 判断当前指针指向对象的引用计数是否等于1 
 */
template<typename T>
bool shared_ptr<T>::unique() const
{
	if(*count==1)
	return true;
	else
	return false;
}

/**
 * ~shared_ptr: 析构函数 
 * note: 析构函数首先将引用计数减小1，若减小后值为0则释放对象，否则不释放对象 
 */
template<typename T>
shared_ptr<T>::~shared_ptr()
{
	*count-=1;
	if(*count==0)
	{
		delete data;
		delete count;
	}
}

#endif
