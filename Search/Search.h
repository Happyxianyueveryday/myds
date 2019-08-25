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
 * linear_search: ���Բ����㷨 
 * param data: �����ҵ��б� 
 * param size: �������б��Ԫ�ظ��� 
 * param val: ���ҵ�Ŀ��ֵ
 * return: Ŀ��ֵ���ڵ��±꣬�����Ҳ���Ŀ��ֵ�򷵻�-1 
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
 * binary_search: ���ֲ����㷨 
 * param data: �����ҵ������б� 
 * param size: �������б��Ԫ�ظ��� 
 * param val: ���ҵ�Ŀ��ֵ
 * return: Ŀ��ֵ���ڵ��±꣬�����Ҳ���Ŀ��ֵ�򷵻�-1 
 */
int Search::binary_search(int data[], int size, int val)
{
	int begin=0, end=size-1;    // ��ǰ����Ƭ�ε��±귶Χ 
	while(begin<=end)
	{
		int mid=(begin+end)/2;  // �����м�Ԫ�ص��±� 
		
		if(val<data[mid])       // ��Ŀ��ֵС���м�Ԫ�أ������������벿�ֲ��� 
		end=mid-1;
		else if(val>data[mid])  // ��Ŀ��ֵ�����м�Ԫ�أ�����������Ұ벿�ֲ��� 
		begin=mid+1;
		else    // Ŀ��ֵ�����м�Ԫ�أ�ֱ�ӷ����±�mid 
		return mid;
	}
	return -1;
}

#endif
