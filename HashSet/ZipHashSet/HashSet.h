#ifndef HASHSET_H   
#define HASHSET_H 
#include <iostream>   
#include <string> 
#include <vector>

using namespace std;

/** 
 * HashSet: 哈希集合接口抽象基类  
 */
template <typename T>
class HashSet
{    
	public:    
	virtual void insert(T value) = 0;               // 向哈希表中插入指定值        
	virtual void remove(T value) = 0;               // 从哈希表中移除指定值    
	virtual bool contain(T value) const = 0;        // 判断哈希表中是否包含指定值    
	virtual vector<T> values() const = 0;           // 获得哈希表中所有值的列表  
	virtual int length() const = 0;                 // 获取哈希表的长度 
	virtual string toString() const = 0;            // 输出哈希表    
	virtual ~HashSet() {}                           // 哈希表抽象基类虚析构函数
};

#endif
