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
 * bubble_sort: ð������
 * note: ð���������������һ��λ�ÿ�ʼ�����ν�����ĵ�1, ��2, ��3, ...,��ֵ��������ĵ�����1, ��2, ��3, ...��λ���ϣ�ÿ�ν����ֵ�ŵ�ĩβ���ǲ����������ڱȽϣ����Ҳ��ֵ��Сʱ����������������Ԫ��
 */
void Sort::bubble_sort(int data[], int size) 
{
    for(int i=size-1;i>=0;i--)  // Ŀ�������λ��
    {
        for(int k=0;k<i;k++)    // ����Ŀ������λ��֮ǰ��λ��
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
 * insert_sort: ��������
 * note 1: �����������δ���λ��0,1,2,...i,��Ԫ�أ�����λ���±�Ϊi��Ԫ�ز��뵽ǰ(i-1)��Ԫ���еĺ���λ����
 * note 2: �����������У�ʹ�õ��������Һ���λ���ٶȸ��죬Ч�ʸ��ߣ�������� 
 */
void Sort::insert_sort(int data[], int size)
{
	for(int i=0;i<size;i++) // ���ν�0,1,...,iλ�õ�Ԫ�ز��뵽��ǰ���Ԫ�����еĺ���λ���� 
	{
		int target=data[i];
		int k=i;     // ���±�i��ʼ��������ǰ���ҵ���һ��С��data[i]��λ��k��Ŀ��ֵ�Ͳ��뵽λ��k֮�󣬼��±�(k+1)�� 
		while(k>=0&&data[k]>=target)
		{
			data[k]=data[k-1];
			k-=1;
		}
		data[k+1]=target;
	}
} 

/**
 * swap_sort: ��������
 * note: ʵ��������򵥵��������ȴ������������ҳ���Сֵ��Ȼ����±�0��Ԫ�ؽ�����Ȼ�󣬴Ӻ�(size-1)��Ԫ�����ҳ���Сֵ�����±�1��Ԫ�ؽ������Դ����ƣ��Ӻ�(size-i)��Ԫ�����ҳ���Сֵ����λ��i��Ԫ�ؽ��� 
 */
void Sort::swap_sort(int data[], int size)
{
	for(int i=0;i<size;i++)    // Ҫ������Ԫ�ص��±� 
	{
		int index=i, min=data[i];   // ��(size-i)��Ԫ���е���Сֵ�������±� 
		for(int k=i;k<size;k++)
		{
			if(data[k]<min)
			{
				index=k;
				min=data[k];
			}
		}
		int temp=data[i];        // ������(size-i)��Ԫ���е���СֵԪ�غ�λ��i��Ԫ�� 
		data[i]=min;
		data[index]=temp;
	}
}

/**
 * merge_sort: �鲢���� 
 * note: �鲢�������Ƚ�������м�ȷ�Ϊǰ�����Σ�Ȼ��ֱ�ݹ�ع鲢����ǰ�벿������ͺ�벿�����飬���ʹ�������α����ǰ���������飬���αȽϲ������н�С��Ԫ�ط����������У������ƶ���СԪ�ض�Ӧ���α� 
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
