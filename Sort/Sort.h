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
    static void build_heap(int data[], int size);
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
 * note 3: ��������ʵ����д���������׳�����˽�������������д�����������±����������α�֤������߽� 
 */
void Sort::insert_sort(int data[], int size)
{
	for(int i=0;i<size;i++) // ���ν�0,1,...,iλ�õ�Ԫ�ز��뵽��ǰ���Ԫ�����еĺ���λ���� 
	{
		// ����Ҫ���±�i��Ԫ�ز��뵽��Ԫ��֮ǰ���������еĺ���λ�� 
		int target=data[i];
		int k=i-1;          // ���±�i-1��ʼ��������ǰ���ҵ���һ��С��data[i]��λ��k��Ŀ��ֵ�Ͳ��뵽λ��k֮�󣬼��±�(k+1)�� 
		while(k>=0&&data[k]>=target)
		{
			data[k+1]=data[k];
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

/**
 * quick_sort: ��������
 * note: ��������ĺ���˼���ǣ�����ѡ��һ������Ԫ����Ϊ��Ԫ����������С����Ԫ��Ԫ���ƶ�����Ԫλ��֮ǰ��������Ԫ��Ԫ���ƶ�����Ԫλ��֮�󣬽��ŵݹ�ض���Ԫ֮ǰ����Ԫ֮�������Ƭ�ν��п������� 
 * note: ������ԣ�ѡ�������һ��Ԫ����Ϊ��Ԫ��ѡ��0Ϊ���һ������ԪС������λ���±�last_small��Ȼ��ӵڶ���Ԫ�ؿ�ʼ����ɨ���������飬����ǰԪ��С����Ԫ�����Ƚ�last_small����1��Ȼ�󽻻���ǰԪ�غ�last_smallλ�õ�Ԫ�أ���󣬱��������󣬽�������Ԫ��last_small��ָ��λ�õ�Ԫ�ء�Ȼ��ݹ����������Ԫ֮ǰ�����к���Ԫ֮������м��� 
 */
void Sort::quick_sort(int data[], int size)
{
	real_quick(data, 0, size-1);
}

void Sort::real_quick(int data[], int begin, int end)
{
	if(begin>=end)
	return;
	
	int pos=begin;           // ���һ��С����Ԫ��Ԫ����ɵ�����λ�õ��±� 
	int pivot=data[begin];   // ��Ԫ��ֵ 
	
	for(int i=begin+1;i<=end;i++)
	{ 
		if(data[i]<=pivot)    // ����ǰԪ�ص�ֵС�ڵ�����Ԫ���򽻻���ǰԪ�غ�data[++begin] 
		{
			pos+=1;
			int temp=data[i];
			data[i]=data[pos];
			data[pos]=temp;
		}
	} 
	int temp=data[begin];     // ������Ԫ�����λ���±��Ԫ�� 
	data[begin]=data[pos];
	data[pos]=temp;
	
	real_quick(data, begin, pos-1);  // �ݹ�������Ԫλ��֮ǰ��֮������� 
	real_quick(data, pos+1, end);    
} 

/**
 * heap_sort: ���л��ڴ���ѵ�����
 * note: ������Ĺ��̽�Ϊ�򵥣�ѭ���������²���ֱ����Ϊ��Ϊֹ��
 *       1. ��������ѵĶѶ�Ԫ�أ��±�Ϊ0�����±�Ϊi��i����ȡsize-1,size-2,...,0����Ԫ��
 *       2. ���µ�����Ϊ����ѣ������������Ǵӽ�����ĶѶ�Ԫ��target��ʼ�����ν��ý��͸ý��������ӽ��Ƚϣ���ĳ���ӽ����ڸ���㣬�򽻻��ӽ��͵�ǰ����� 
 *       3. ׷��target��λ�ã�ѭ�����в���2��ֱ��target�������ӽ����ߴ��������ӽ��λ�� 
 */
void Sort::heap_sort(int data[], int size)
{
	Sort::build_heap(data, size);
	
	for(int i=size-1;i>0;i--)   // ���ν�����ѶѶ�Ԫ�غ����ֵλ�ã��δ�ֵλ�ã�...�����н��� 
	{
		int temp=data[0];   // ����data[i]��data[0] 
		data[0]=data[i];
		data[i]=temp;
		
		int pos=0;
		while(pos<i)        // ���µ���data[0]��λ��ά�ִ���ѵ����ʣ�ע��i�Լ�i֮�������Ԫ���ǴӶѶ�ȡ���ģ��Ѿ��������ڶѣ�������е��� 
		{
			int left=(pos*2+1<i)?data[pos*2+1]:INT_MIN;
			int right=(pos*2+2<i)?data[pos*2+2]:INT_MIN;
			
			if(left>right&&left>data[pos])
			{
				data[2*pos+1]=data[pos];
				data[pos]=left;
				pos=2*pos+1;    // ׷��ԭ�Ѷ�Ԫ��λ�� 
			}
			else if(right>left&&right>data[pos])   // ���ӽ����󣬽�����ǰ�������ӽ�� 
			{
				data[2*pos+2]=data[pos];
				data[pos]=right;
				pos=pos*2+2;
			}
			else if(data[pos]>left&&data[pos]>right)    // ��ǰ���������ӽ������ӽ�㣬�˳�ѭ�� 
			break;
		}
	}
}

/**
 * build_heap: ���������
 * note: �����ѵ��㷨��Ϊ��: 
 *		1. ��ԭʼ������Ϊ���������һ����Ҷ�ӽ�㣨�±�size/2-1����ʼ������ǰ����ÿ����Ҷ�ӽ��
 *		2. ���ڱ�������ÿ����Ҷ�ӽ�㣬��������������ӽ���ֵ�Ƚϣ��������ӽ��Ľϴ�ֵ���ڵ�ǰ���ֵ���򽻻��ӽ���еĽϴ�ֵ�͵�ǰ���ֵ 
 */
void Sort::build_heap(int data[], int size)
{
	for(int i=size/2-1;i>=0;i--)
	{
		int left=(2*i+1<size)?data[2*i+1]:INT_MIN;   // ���ӽ���ֵ��ע���ж������ӽ���Ƿ�ȷʵ���� 
		int right=(2*i+2<size)?data[2*i+2]:INT_MIN;  // ���ӽ���ֵ
		
		if(left>right&&left>data[i])    // ���ӽ����ڵ�ǰ�������ӽ�㣬�򽻻���ǰ�������ӽ���ֵ 
		{
			data[2*i+1]=data[i];
			data[i]=left;
		}
		if(right>left&&right>data[i])   // ���ӽ����ڵ�ǰ�������ӽ�㣬�򽻻���ǰ�������ӽ���ֵ 
		{
			data[2*i+2]=data[i];
			data[i]=right;
		}
	} 
}

/*
 * shell_sort: ϣ������
 * note: ϣ���������ʹ���˲����Ĳ������򣬴ӵ�һ��Ԫ�ؿ�ʼ��ÿ�εĲ���step�ֱ�ȡsize/2,size/4,...,1��ÿ��������������ʼ�±�ֱ�Ϊ0,1,2,...,step-1 
 */
void Sort::shell_sort(int data[], int size)
{
	int step=size/2;
	while(step>=1)
	{
		for(int i=0;i<step;i++)    // ����������е���ʼ�±� 
		{
			// ���ν�i,i+step,i+2*step,...����Ԫ�ز��뵽��ǰ������������� 
			for(int k=i;k<size;k+=step)
			{
				// ����Ҫ��k����λ�ò��뵽��֮ǰ������������ 
				int pos=k-step, val=data[k]; 
				while(pos>=i&&data[pos]>=val)    // ���ȴ��±�k��������ǰһ��Ԫ��k-step��ʼ���Ӻ���ǰ���ҵ�һ��С��Ŀ��ֵ��Ԫ�أ���ǰԪ�ؾͲ��뵽��λ��֮�� 
				{
					data[pos+step]=data[pos];
					pos-=step;
				}
				data[pos+step]=val;				
			}
		}
		step/=2;
	}
}

#endif
