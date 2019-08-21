#ifndef SORT_H
#define SORT_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Sort
{
    public:
    static void bubble_sort(int data[], int size);
    static void insert_sort(int data[], int size);
    static void swap_sort(int data[], int size);
    static void merge_sort(int data[], int size);
    static void quick_sort(int data[], int size);
    static void heap_sort(int data[], int size);
    static void shell_sort(int data[],int size);
    
    private:
    static void real_merge(int data[], int begin, int end);
    static void real_quick(int data[], int begin, int end);
};

/**
 * bubble_sort: 冒泡排序
 * note: 冒泡排序从数组的最后一个位置开始，依次将数组的第1, 第2, 第3, ...,的值放在数组的倒数第1, 第2, 第3, ...个位置上，每次将最大值放到末尾都是采用两两相邻比较，在右侧的值较小时交换两个相邻数组元素
 */
void Sort::bubble_sort(int data[], int size) 
{
    for(int i=size-1;i>=0;i--)  // 目标排序的位置
    {
        for(int k=0;k<i;k++)    // 遍历目标排序位置之前的位置
        {
            if(data[k]>data[k+1])
            {
                int temp=data[k];
                data[k]=data[k+1];
                data[k+1]=temp;
            }
        }
    }
}

/**
 * insert_sort: 插入排序
 * note 1: 插入排序依次处理位置0,1,2,...i,的元素，将该位置下标为i的元素插入到前(i-1)个元素中的合适位置上
 * note 2: 具体插入过程中，使用倒序来查找合适位置速度更快，效率更高，步骤更简化 
 */
void Sort::insert_sort(int data[], int size)
{
	for(int i=0;i<size;i++) // 依次将0,1,...,i位置的元素插入到其前面的元素序列的合适位置上 
	{
		int target=data[i];
		int k=i;     // 从下标i开始，依次向前查找到第一个小于data[i]的位置k，目标值就插入到位置k之后，即下标(k+1)处 
		while(k>=0&&data[k]>=target)
		{
			data[k]=data[k-1];
			k-=1;
		}
		data[k+1]=target;
	}
} 

/**
 * swap_sort: 交换排序
 * note: 实现起来最简单的排序，首先从整个数组中找出最小值，然后和下标0的元素交换；然后，从后(size-1)个元素中找出最小值，和下标1的元素交换；以此类推，从后(size-i)个元素中找出最小值，和位置i的元素交换 
 */
void Sort::swap_sort(int data[], int size)
{
	for(int i=0;i<size;i++)    // 要交换的元素的下标 
	{
		int index=i, min=data[i];   // 后(size-i)个元素中的最小值和所在下标 
		for(int k=i;k<size;k++)
		{
			if(data[k]<min)
			{
				index=k;
				min=data[k];
			}
		}
		int temp=data[i];        // 交换后(size-i)个元素中的最小值元素和位置i的元素 
		data[i]=min;
		data[index]=temp;
	}
}

/**
 * merge_sort: 归并排序 
 * note: 归并排序首先将数组从中间等分为前后两段，然后分别递归地归并排序前半部分数组和后半部分数组，最后使用两个游标遍历前后两段数组，依次比较并将其中较小的元素放入结果数组中，并且移动较小元素对应的游标 
 */
void Sort::merge_sort(int data[], int size)
{
	Sort::real_merge(data, 0, size-1);
}

void Sort::real_merge(int data[], int begin, int end)
{
	if(begin>=end)
	return;
	else
	{
		int mid=(begin+end)/2;
		real_merge(data, begin, mid);
		real_merge(data, mid+1, end);
		
		vector<int> res;
		int pos1=begin, pos2=mid+1;
		
		while(pos1<=mid&&pos2<=end)
		{
			if(data[pos1]<data[pos2])
			{
				res.push_back(data[pos1]);
				pos1+=1;
			}
			else
			{
				res.push_back(data[pos2]);
				pos2+=1;
			}
		}
		while(pos1<=mid)
		{
			res.push_back(data[pos1]);
			pos1+=1;
		}
		while(pos2<=end) 
		{
			res.push_back(data[pos2]);
			pos2+=1;
		}
		
		for(int i=0;i<res.size();i++)
		{
			data[begin+i]=res[i];  
		}
	}
}

#endif
