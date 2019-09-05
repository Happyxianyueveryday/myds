#ifndef ARRAYHASHSET_H   
#define ARRAYHASHSET_H
#include "HashElement.h"    
#include "HashSet.h"

using namespace std;

class ArrayHashSet: public HashSet
{
	public:
	// 1. constructor
	ArrayHashSet(string mode, const int (*_rehash)(const HashElement *value)=nullptr);  // 构造函数 
	
	// 2. copy/move controller
	ArrayHashSet(const ArrayHashSet &other);   			   // 拷贝构造函数
	ArrayHashSet &operator= (const ArrayHashSet &other);   // 拷贝赋值运算符 
	ArrayHashSet(ArrayHashSet &&other);                    // 移动构造函数
	ArrayHashSet &operator= (ArrayHashSet &&other);        // 移动赋值运算符 
	
	// 3. methods
	void insert(const HashElement *value) override;        // 向哈希表中插入指定值     
	void remove(const HashElement *value) override;        // 从哈希表中移除指定值    
	bool contain(const HashElement *value) const override; // 判断哈希表中是否包含指定值    
	vector<const HashElement *> values() const override;   // 获得哈希表中所有值的列表  
	int length() const override;                           // 获取哈希表的长度 
	string toString() const override;                      // 输出哈希表
	
	// 4. destructor
	~ArrayHashSet();                  // 哈希表抽象基类虚析构函数
	
	private:
	// 5. domain
	const HashElement **data;// 哈希元素存储数组 
	bool *sign;              // 哈希元素删除标志数组
	string mode;             // 选用的模式  
	int size;                // 哈希表中的元素数量 
	int max_size;            // 哈希表的桶数量
	const int (*rehash)(const HashElement *value);    // 再哈希法使用的再哈希法函数指针 
	
	// 6. private functions
	void resize();           // 哈希扩容方法 
};

/** 
 * ArrayHashSet: 构造函数
 * param _mode: 使用的开放定址法的种类 
 * param _rehash: 再哈希法中使用的再哈希函数，如果不使用再哈希法，不必提供此参数；如果使用再哈希法但是不提供参数，将使用原来的哈希函数做再哈希 
 */
ArrayHashSet::ArrayHashSet(string _mode, const int (*_rehash)(const HashElement *value))
{
	size=0;
	max_size=13;    // 默认的初始桶数量为13 
	data=new const HashElement* [max_size];
	sign=new bool [max_size];
	rehash=_rehash;
	for(int i=0;i<max_size;i++)
	{
		sign[i]=true;      // 初始状态下表中不存在元素，因此对应的标记为已删除，即true 
		data[i]=nullptr;
	}
	
	if(_mode=="linear"||_mode=="square"||_mode=="rehash")   // linear: 线性探查法，square: 二次探查法，rehash:再哈希法 
	mode=_mode;
	else
	mode="linear";     // 用户输入不合法模式则默认使用线性探查法
}

/**
 * ArrayHashSet: 拷贝构造函数 
 * note: 拷贝构造函数对哈希表进行深拷贝 
 */
ArrayHashSet::ArrayHashSet(const ArrayHashSet &other)
{
	// 1. 深拷贝源对象成员 
	size=other.size;
	max_size=other.max_size;
	mode=other.mode;
	rehash=other.rehash;
	data=new const HashElement* [max_size];
	sign=new bool [max_size];
	for(int i=0;i<max_size;i++)
	{
		if(other.data[i])
		data[i]=other.data[i]->clone();
		else
		data[i]=nullptr;
		sign[i]=other.sign[i];
	}
}

/**
 * operator=: 拷贝赋值运算符 
 * note: 拷贝构造函数对哈希表进行深拷贝 
 */
ArrayHashSet &ArrayHashSet::operator= (const ArrayHashSet &other)
{
	// 1. 判断是否自身赋值 
	if(&other==this)
	return (*this);
	// 2. 释放自身所使用的堆资源 
	if(max_size!=other.max_size)
	{
		for(int i=0;i<max_size;i++)
		{
			if(data[i])
			delete data[i];
		}
		delete [] data;
		delete [] sign;
		data=new const HashElement* [max_size];
		sign=new bool [max_size];
	}
	// 3. 深拷贝源对象成员 
	size=other.size;
	max_size=other.max_size;
	mode=other.mode;
	rehash=other.rehash;
	for(int i=0;i<max_size;i++)
	{
		if(other.data[i])
		data[i]=other.data[i]->clone();
		else
		data[i]=nullptr;
		sign[i]=other.sign[i];
	}
	// 4. 返回当前对象引用 
	return (*this);
}

/**
 * ArrayHashSet: 移动构造函数 
 */ 
ArrayHashSet::ArrayHashSet(ArrayHashSet &&other)
{
	// 1. 浅拷贝源对象的成员 
	size=other.size;
	max_size=other.max_size;
	data=other.data;
	mode=other.mode;
	sign=other.sign;
	rehash=other.rehash;
	// 2. 重置源对象成员为默认值
	other.size=0;
	other.data=new const HashElement* [other.max_size];
	other.sign=new bool [other.max_size];
	for(int i=0;i<other.max_size;i++)
	{
		other.data[i]=nullptr;
		other.sign[i]=true;      // 初始状态下表中不存在元素，因此对应的标记为已删除，即true 
	}
}

/** 
 * operator=: 移动赋值运算符 
 */
ArrayHashSet &ArrayHashSet::operator= (ArrayHashSet &&other)
{
	// 1. 处理自身赋值 
	if(&other==this)
	return (*this);
	// 2. 释放自身所使用的堆资源 
	for(int i=0;i<max_size;i++)
	{
		if(data[i])
		delete data[i];
	}
	delete [] data;
	delete [] sign; 
	// 3. 浅拷贝源对象的成员 
	size=other.size;
	max_size=other.max_size;
	data=other.data;
	mode=other.mode;
	sign=other.sign;
	rehash=other.rehash;
	// 4. 重置源对象成员为默认值 
	other.size=0;
	other.data=new const HashElement* [other.max_size];
	other.sign=new bool [other.max_size];
	for(int i=0;i<other.max_size;i++)
	{
		other.data[i]=nullptr;
		other.sign[i]=true;
	}
	// 5. 返回当前对象的引用 
	return (*this);
}

/**
 * insert: 向哈希表中插入给定值 
 * note 1: 插入的值是输入的哈希元素的深拷贝 
 * note 2: 删除的算法总结如下：首先根据哈希值和选择的解决冲突的模式依次访问各个桶，若当前桶的删除标记为已删除(true)，则首先释放当前桶中的元素（如果有的话），然后将待插入元素插入到此处 
 * note 3: 最后，在插入过程完成后，需要检查是否需要进行哈希扩容 
 */
void ArrayHashSet::insert(const HashElement *value)
{
	// 0. 输入元素判空 
	if(!value)
	return;
	// 1. 若插入前对象已经满，或者哈希表中已经存在相同值，则插入失败 
	if(size==max_size||this->contain(value))
	return;
	// 2. 计算元素插入桶的初始位置下标
	int index=(value->hashCode())%max_size;
	// 3. 从初始位置下标开始查找元素的插入位置下标，根据用户选择的模式不同，使用线性探查法，二次探查法或者再哈希法 
	int search_time=(mode=="linear"||mode=="rehash")?max_size:(max_size/2);   // 最大探查次数：线性探查法和再哈希法的最多只需要max_size次探查，二次探查法则需要max_size/2次 
	for(int i=0;i<search_time;i++)
	{
		// 计算当前探查的位置 
		int now=0;
		if(mode=="linear")
		now=(index+i)%max_size;     // 线性探查法依次探查(index+0)%max_size, (index+1)%max_size, (index+2)%max_size, ...,最多探查max_size次 
		else if(mode=="square")
		now=(index+i*i)%max_size;   // 二次探查法依次探查(index+0^2)%max_size, (index+1^2)%max_size, (index+2^2)%max_size, (index+3^2)%max_size,...,最多探查max_size/2次 
		else
		now=(index+i*((rehash==nullptr)?value->hashCode():rehash(value)))%max_size;// 再哈希法依次探查(index+0*rehash(value))%max_size, (index+1*rehash(value))%max_size, (index+2*rehash(value))%max_size, ...,最多探查max_size次
		
		// 探查到可以插入的位置时，先判断该桶中是否有懒惰删除的元素，有则进行真删除，最后将待插入元素插入到此并标记该桶为未删除 
		if(sign[now])     
		{
			if(data[now])
			delete data[now];
			data[now]=value->clone();
			sign[now]=false;
			break;
		}
	}
	size+=1;   // 增加元素的计数器 
	// 4. 检查是否需要哈希扩容 
	int threshold=max_size*0.75;    // 当元素数量大于桶数量乘以0.75时，进行哈希表的扩容 
	if(size>threshold)
	resize();
	return;
}

/**
 * remove: 从哈希表中移除值 
 * note: 在开放定址法的哈希表实现中，最主要的是懒惰删除技术，关于懒惰删除主要提以下几点： 
 * 		 1. 为什么需要懒惰删除？
 *		 因为哈希表的查找某个值的算法中，不论使用哪种开放定址冲突解决方法，一旦访问到空的桶位置，就认为哈希表中不存在该元素，这是哈希表的查找快于线性表的原因。而如果进行真删除，则删除某个元素为空可能导致查找不到后续的元素，因为一旦访问到空桶就认为查找结束了。 
 *		 2. 懒惰删除如何进行？
 *	     在需要删除某个桶中元素时，仅标记该元素的对应的标记变量即可，不删除元素。 
 *       3. 懒惰删除下的哈希查找算法？ 
 *       (1) 在查找过程中，只有遇到桶为空的情况下才认为哈希表中不存在待查找元素，若桶不为空但是删除标记为真，以及其他情况，会继续查找过程。
 *       (2) 在插入过程中，只要遇到标记变量标记为"已删除"的桶就进行插入。 
 *       (3) 在删除过程中，只有遇到标记变量标记为"未删除"且桶中的元素和待删除相等的情况才进行删除。 
 *       4. 如何处理懒惰删除后遗留下的占用空间的元素？
 *       占用空间的懒惰删除的元素是在哈希表扩容时被清理的，哈希表在扩容时会自动清理这些元素。 
 * 
 */
void ArrayHashSet::remove(const HashElement *value) 
{
	// 1. 输入判空和当前哈希表判空 
	if(!value||!size)
	return;
	// 2. 使用对应的开放定址法进行查找待删除元素的操作 
	int search_time=(mode=="linear"||mode=="rehash")?max_size:(max_size/2);
	int index=(value->hashCode())%max_size;
	for(int i=0;i<search_time;i++)
	{
		int now=0;
		if(mode=="linear")
		now=(index+i)%max_size;
		else if(mode=="square")
		now=(index+i*i)%max_size;
		else
		now=(index+i*((rehash==nullptr)?value->hashCode():rehash(value)))%max_size;
		
		if(!sign[now])    
		{
			if(data[now]->hashCode()==value->hashCode()&data[now]->equals(value))  // 查找到待删除元素，待删除元素首先其标记应为未删除的，其次值应该与输入相等 
			sign[now]=true;   // 进行懒惰删除 
			break;
		}
		else if(sign[now]&&!data[now])   // 遇到标记为已删除，且桶中的元素为空，则说明哈希表中不存在该元素，直接返回即可 
		return;
		else    // 否则当前结点为懒惰删除的结点，继续进行查找待删除元素 
		continue;  
	}
	size-=1;
}

/**
 * contain: 判断某个值是否在哈希表中 
 * note 1: 本方法就相当于哈希表的搜索算法，搜索算法如下：使用哈希值计算目标元素所在的桶位置，并使用对应的冲突姐姐方法不断访问后续的桶，若当前桶的元素和目标元素相等且标记为未删除，则返回true；否则，如果访问到标记为已经删除的桶且桶中的元素为空，则说明目标元素不在哈希表中，返回false 
 * note 2: 判断目标元素和当前桶中的元素是否相等时，使用java中的标准：首先比较hashCode()方法得到的哈希值是否相等，若哈希值不等，则元素不相等；若哈希值相等，则进一步调用equals()方法确定两个元素是否完全相等 
 */
bool ArrayHashSet::contain(const HashElement *value) const 
{
	// 1. 输入判空和当前哈希表判空 
	if(!value||!size)
	return false;	
	// 2. 使用对应的开放定址法进行查找目标元素的操作 
	int search_time=(mode=="linear"||mode=="rehash")?max_size:(max_size/2);
	int index=(value->hashCode())%max_size;
	for(int i=0;i<search_time;i++)
	{
		int now=0;
		if(mode=="linear")
		now=(index+i)%max_size;
		else if(mode=="square")
		now=(index+i*i)%max_size;
		else
		now=(index+i*((rehash==nullptr)?value->hashCode():rehash(value)))%max_size;
		
		if(!sign[now])                   // 遇到标记为未删除的桶，检查桶中元素和目标值是否相等 
		{
			if(data[now]->hashCode()==value->hashCode()&data[now]->equals(value))
			return true;
		}
		else if(sign[now]&&!data[now])   // 遇到标记为已删除，且桶中的元素为空，则说明哈希表中不存在该元素，直接返回false
		return false;
		else    // 否则当前结点为懒惰删除的结点，继续进行查找
		continue;  
	}
	return false;
}

/** 
 * value: 遍历哈希表 
 */
vector<const HashElement *> ArrayHashSet::values() const
{
	vector<const HashElement *> res;
	for(int i=0;i<max_size;i++)
	{
		if(!sign[i])
		res.push_back(data[i]);
	}
	return res;
}

/** 
 * length: 返回哈希表的元素个数 
 */
int ArrayHashSet::length() const
{
	return size;
}

/**
 * toString: 输出哈希表 
 */
string ArrayHashSet::toString() const
{
	string res;
	for(int i=0;i<max_size;i++) 
	{
		if(!sign[i])
		res=res+data[i]->toString()+" ";
		else
		res=res+"X"+" "; 
	}
	return res;
}

/**
 * resize: 哈希表扩容函数 
 * note 1: 何时进行扩容？
 *		   当哈希表中的元素数量大于桶数量乘以0.75时，就进行自动扩容 
 * note 2: 如何进行哈希扩容？
 *         (1) 创建新的桶数组，新桶数组的大小扩容为旧桶数组的两倍 
 *         (2) 将旧桶数组中的未删除元素重新按照相同的哈希算法插入到新桶数组中，旧桶数组中标记为已删除的懒惰删除的元素进行清理，不再插入到新的哈希表中 
 *         (3) 析构原始桶数组，新桶数组作为当前哈希表的桶数组 
 * note 3: 基于开放定址法的哈希表扩容的意义？
 *         (1) 提高查找效率，减少哈希冲突 
 *         (2) 及时清理已经懒惰删除的哈希表元素 
 */
void ArrayHashSet::resize()
{
	// 1. 创建新的桶数组 
	int old_size=max_size;
	const HashElement **old_data=data;
	bool *old_sign=sign;
	
	max_size*=2;
	size=0;
	data=new const HashElement* [max_size];
	sign=new bool [max_size];
	for(int i=0;i<max_size;i++)
	{
		data[i]=nullptr;
		sign[i]=true;
	}
	
	// 2. 将旧桶数组中标记为未删除的元素按照相同的方法插入到新的桶数组中，已经懒惰删除的元素则进行清理 
	for(int i=0;i<old_size;i++)
	{
		if(!old_sign[i])
		this->insert(old_data[i]);
	}
	
	// 3. 释放旧的桶数组中的所有元素 
	for(int i=0;i<old_size;i++)
	{
		if(old_data[i])
		delete old_data[i];
	}
	delete [] old_data;
	delete [] old_sign;
}

/** 
 * ~ArrayHashSet: 哈希表析构函数 
 */
ArrayHashSet::~ArrayHashSet()
{
	for(int i=0;i<max_size;i++)
	{
		if(data[i])
		delete data[i];
	}
	delete [] data;
	delete [] sign;
}


#endif


