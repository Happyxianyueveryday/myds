#ifndef SEARCH_H
#define SEARCH_H
#include <iostream>
#include <string>

using namespace std;

class Search
{
	public:
	static int linear_search(int data[], int size, int val);
	static int binary_search(int data[], int size, int val); 
};

/**
 * linear_search: 线性查找算法 
 * param data: 待查找的列表 
 * param size: 待查找列表的元素个数 
 * param val: 查找的目标值
 * return: 目标值所在的下标，若查找不到目标值则返回-1 
 */
int Search::linear_search(int data[], int size, int val)
{
	for(int i=0;i<size;i++)
	{
		if(data[i]==val)
		return i;
	}
	return -1;
}

/**
 * binary_search: 二分查找算法 
 * param data: 待查找的有序列表 
 * param size: 待查找列表的元素个数 
 * param val: 查找的目标值
 * return: 目标值所在的下标，若查找不到目标值则返回-1 
 */
int Search::binary_search(int data[], int size, int val)
{
	int begin=0, end=size-1;    // 当前查找片段的下标范围 
	while(begin<=end)
	{
		int mid=(begin+end)/2;  // 计算中间元素的下标 
		
		if(val<data[mid])       // 若目标值小于中间元素，则在数组的左半部分查找 
		end=mid-1;
		else if(val>data[mid])  // 若目标值大于中间元素，则在数组的右半部分查找 
		begin=mid+1;
		else    // 目标值等于中间元素，直接返回下标mid 
		return mid;
	}
	return -1;
}

#endif
