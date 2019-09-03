/*
 * Hashtable.h
 *
 *  Created on: 2019年5月24日
 *      Author: PZH
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_


#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class HashTable
{
    public:
    // 1. constructor
    HashTable(int _max_size, string _mode);
    HashTable(int _data [], int _size, int _max_size, string _mode);

    // 2. copy controller
    HashTable(const HashTable &other);
    HashTable & operator = (const HashTable &other);

    // 3. methods
    bool insert(int key);
    bool remove(int key);
    int getindex(int key);
    string toString();

    // 4. destructor
    ~HashTable();

    private:
    int *data;      // 哈希表底层存储数组
    bool *dic;      // 标记哈希表数组单元是否被使用的数组
    int max_size;   // 哈希表的最大元素个数
    string mode;    // 哈希表使用的解决冲突的方式，规定为三种经典开放寻址法中的一种——线性探查法，二次探查法和再哈希法

    int hash(int key);       // 所选用的哈希函数
    int rehash(int key);     // 再哈希法中所选用的第二个哈希函数
};

/**
 * HashTable: 构建一个空的哈希表
 * param _max_size:哈希表的最大元素单元个数
 * param _mode: 哈希表的解决冲突所使用的算法，"linear"指定为线性探查法，"square"指定为二次探查法，"rehash"指定为再哈希法，其他不合法输入将默认重置为线性探查法
 */
HashTable::HashTable(int _max_size, string _mode)
{
	max_size=_max_size;

	data=new int [max_size];
	dic=new bool [max_size];

	for(int i=0;i<max_size;i++)
	{
		dic[i]=false;
	}

	if(_mode=="linear"||_mode=="square"||_mode=="rehash")
		mode=_mode;
	else
		mode="linear";
}

/**
 * HashTable: 从数组构建对应的哈希表
 * param _data: 输入的数组
 * param _max_size:哈希表的最大元素单元个数
 * param _mode: 哈希表的解决冲突所使用的算法，"linear"指定为线性探查法，"square"指定为二次探查法，"rehash"指定为再哈希法，其他不合法输入将默认重置为线性探查法
 */
HashTable::HashTable(int _data [], int _size, int _max_size, string _mode)
{
	max_size=_max_size;
	data=new int [max_size];
	dic=new bool [max_size];

	for(int i=0;i<max_size;i++)
	{
		dic[i]=false;
	}

	if(_mode=="linear"||_mode=="square"||_mode=="rehash")
			mode=_mode;
		else
			mode="linear";

	for(int i=0;i<_size;i++)
	{
		this->insert(_data[i]);
	}
}

/**
 * HashTable: 拷贝构造函数
 */
HashTable::HashTable(const HashTable &other)
{
	max_size=other.max_size;
	data=new int [max_size];
	dic=new bool [max_size];
	mode=other.mode;

	for(int i=0;i<max_size;i++)
	{
		data[i]=other.data[i];
		dic[i]=other.dic[i];
	}
}

/**
 * operator =: 拷贝赋值运算符
 */
HashTable & HashTable::operator = (const HashTable &other)
{
	if(&other==this)
		return (*this);

	delete [] data;
	delete [] dic;

	max_size=other.max_size;
	data=new int [max_size];
	dic=new bool [max_size];
	mode=other.mode;

	for(int i=0;i<max_size;i++)
	{
		data[i]=other.data[i];
		dic[i]=other.dic[i];
	}

	return (*this);
}

/**
 * insert: 向哈希表中插入新的给定值
 * param key: 待插入的新值
 * return: 若成功插入新值则返回true，否则返回false
 */
bool HashTable::insert(int key)
{
	// 1. 根据哈希函数计算该值应该插入的位置
	int index=this->hash(key);

	// 2 判断该位置是否已经被使用，若未被使用，则将输入值插入到该位置，并返回true表示插入成功
	if(dic[index]==false)
	{
		data[index]=key;
		dic[index]=true;
		return true;
	}

	// 3. 若该位置已经被使用，则根据创建对象时所指定的解决冲突的算法探查下一个未被使用的位置，并尝试进行插入
	else
	{
		// 3.1 使用线性探查法时，依次探查下标位置pos=(index+1)%max_size, (index+2)%max_size, ...,(index+max_size-1)%max_size，若探查到未被使用的位置则进行插入并返回true，若结束探查后仍然没有找到未被使用的位置则插入失败，返回false
		// note: 线性探查法的优点在于当哈希表中存在未被使用的单元时，最多探查(max_size-1)次一定能够探查到；缺点在于容易产生堆积现象
		if(mode=="linear")
		{
			for(int i=1;i<max_size;i++)
			{
				int pos=(index+i)%max_size;

				if(dic[pos]==false)
				{
					data[pos]=key;
					dic[pos]=true;
					return true;
				}
			}
		}

		// 3.2 使用二次探查法时，依次探查下标位置pos=(index+1^2)%max_size, (index+2^2)%max_size, (index+3^2)%max_size, ..., (index+(max_size/2)^2)%max_size，若探查到未被使用的位置则进行插入并返回true，若结束探查后仍然没有找到未被使用的位置则插入失败，返回false
		// note: 二次探查法总共探查(max_size/2)次，优点在于不会产生堆积现象；缺点在于最多只能探查到一半的未被使用的单元
		else if(mode=="square")
		{
			for(int i=1;i<=max_size/2;i++)
			{
				int pos=(index+i*i)%max_size;

				if(dic[pos]==false)
				{
					data[pos]=key;
					dic[pos]=true;
					return true;
				}
			}
		}

		// 3.3 使用再哈希法时，依次探查下标位置pos=(index+i*rehash(key))%max_size，其中i=1,2,3,...,max_size-1，若探查到未被使用的位置则进行插入并返回true，若结束探查后仍然没有找到未被使用的位置则插入失败，返回false
		// note: 再哈希法的优点在于当哈希表中存在未被使用的单元时一定能够在(max_size-1)次探查内被探查到，并且不会产生堆积现象，是实际实现中最常用的开放定址法
		else
		{
			for(int i=1;i<=max_size/2;i++)
			{
				int pos=(index+i*rehash(key))%max_size;

				if(dic[pos]==false)
				{
					data[pos]=key;
					dic[pos]=true;
					return true;
				}
			}
		}

		return false;
	}
}

/**
 * remove: 从哈希表中删除给定值
 * param key: 待删除的值
 * return: 若删除该值成功则返回true，否则返回false
 */
bool HashTable::remove(int key)
{
	// 1. 计算该值在哈希表中的位置
	int index=this->getindex(key);

	// 2. 若该位置已经被占用且该位置的值和待删除的值相同，则删除该值，并返回true表示删除成功
	if(index!=-1&&dic[index]==true)
	{
		dic[index]=false;
		return true;
	}

	// 3. 否则哈希表中不存在该值，删除失败
	else
		return false;
}

/**
 * getindex: 获取哈希表中给定值在数组中的存储下标
 * param key: 待查找的值
 * return: 给定值的下标，若该值在哈希表中不存在，则返回下标-1
 * note: 获取值的下标和插入值的步骤大同小异，不过需要同时检查当前位置是否被使用和当前位置的值是否和给定值相等
 */
int HashTable::getindex(int key)
{
	int index=hash(key);

	if(dic[index]==true&&data[index]==key)
		return index;
	else
	{
		if(mode=="linear")
		{
			for(int i=1;i<max_size;i++)
			{
				int pos=(index+i)%max_size;
				if(dic[pos]==true&&data[pos]==key)
					return pos;
			}
		}
		else if(mode=="square")
		{
			for(int i=1;i<=max_size/2;i++)
			{
				int pos=(index+i*i)%max_size;
				if(dic[pos]==true&&data[pos]==key)
					return pos;
			}
		}
		else
		{
			for(int i=1;i<max_size;i++)
			{
				int pos=(index+i*rehash(key))%max_size;
				if(dic[pos]==true&&data[pos]==key)
					return pos;
			}
		}
		return -1;
	}
}

/**
 * hash: 所选用的哈希函数1，哈希函数存在很多选择，这里选择了最基础的取余哈希函数
 * param key: 要计算哈希值的键
 * return: 输入的键所对应的哈希值
 */
int HashTable::hash(int key)
{
	return key%max_size;
}

/**
 * hash: 再哈希法中所选用的哈希函数2，这里选取和哈希函数1相同的取余哈希函数
 * param key: 要计算哈希值的键
 * return: 输入的键所对应的哈希值
 */
int HashTable::rehash(int key)
{
	return key%max_size;
}

/**
 * toString: 将哈希表格式化为字符串输出
 * return: 输出字符串
*/
string HashTable::toString()
{
	string res;

	for(int i=0;i<max_size;i++)
	{
		if(dic[i]==true)
		{
			char str[100];
			itoa(data[i],str,10);
			res=res+string(str)+" ";
		}
		else
			res=res+"#"+" ";
	}
	return res;
}

/**
 * ~HashTable: 析构函数
 */
HashTable::~HashTable()
{
	delete [] dic;
	delete [] data;
}


#endif /* HASHTABLE_H_ */
