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
 * note 3: 插入排序实际上写起来很容易出错，因此建议熟练记下来写法，尤其是下标操作部分如何保证不溢出边界 
 */
void Sort::insert_sort(int data[], int size)
{
	for(int i=0;i<size;i++) // 依次将0,1,...,i位置的元素插入到其前面的元素序列的合适位置上 
	{
		// 现在要将下标i的元素插入到该元素之前的有序序列的合适位置 
		int target=data[i];
		int k=i-1;          // 从下标i-1开始，依次向前查找到第一个小于data[i]的位置k，目标值就插入到位置k之后，即下标(k+1)处 
		while(k>=0&&data[k]>=target)
		{
			data[k+1]=data[k];
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

/**
 * quick_sort: 快速排序
 * note: 快速排序的核心思想是，首先选择一个数组元素作为主元，将数组中小于主元的元素移动到主元位置之前，大于主元的元素移动到主元位置之后，接着递归地对主元之前和主元之后地数组片段进行快速排序 
 * note: 具体而言，选择数组第一个元素作为主元，选择0为最后一个比主元小的序列位置下标last_small，然后从第二个元素开始依次扫描整个数组，若当前元素小于主元，则先将last_small自增1，然后交换当前元素和last_small位置的元素；最后，遍历结束后，交换和主元和last_small所指向位置的元素。然后递归快速排序主元之前的序列和主元之后的序列即可 
 */
void Sort::quick_sort(int data[], int size)
{
	real_quick(data, 0, size-1);
}

void Sort::real_quick(int data[], int begin, int end)
{
	if(begin>=end)
	return;
	
	int pos=begin;           // 最后一个小于主元的元素组成的序列位置的下标 
	int pivot=data[begin];   // 主元的值 
	
	for(int i=begin+1;i<=end;i++)
	{ 
		if(data[i]<=pivot)    // 若当前元素的值小于等于主元，则交换当前元素和data[++begin] 
		{
			pos+=1;
			int temp=data[i];
			data[i]=data[pos];
			data[pos]=temp;
		}
	} 
	int temp=data[begin];     // 交换主元和最后位置下标的元素 
	data[begin]=data[pos];
	data[pos]=temp;
	
	real_quick(data, begin, pos-1);  // 递归排序主元位置之前和之后的序列 
	real_quick(data, pos+1, end);    
} 

/**
 * heap_sort: 进行基于大根堆的排序
 * note: 堆排序的过程较为简单，循环进行以下步骤直到堆为空为止：
 *       1. 交换大根堆的堆顶元素（下标为0）和下标为i（i依次取size-1,size-2,...,0）的元素
 *       2. 重新调整堆为大根堆，调整方法就是从交换后的堆顶元素target开始，依次将该结点和该结点的左右子结点比较，若某个子结点大于根结点，则交换子结点和当前根结点 
 *       3. 追踪target的位置，循环进行步骤2，直到target不存在子结点或者大于两个子结点位置 
 */
void Sort::heap_sort(int data[], int size)
{
	Sort::build_heap(data, size);
	
	for(int i=size-1;i>0;i--)   // 依次将大根堆堆顶元素和最大值位置，次大值位置，...，进行交换 
	{
		int temp=data[0];   // 交换data[i]和data[0] 
		data[0]=data[i];
		data[i]=temp;
		
		int pos=0;
		while(pos<i)        // 重新调整data[0]的位置维持大根堆的性质，注意i以及i之后的数组元素是从堆顶取出的，已经不再属于堆，无需进行调整 
		{
			int left=(pos*2+1<i)?data[pos*2+1]:INT_MIN;
			int right=(pos*2+2<i)?data[pos*2+2]:INT_MIN;
			
			if(left>right&&left>data[pos])
			{
				data[2*pos+1]=data[pos];
				data[pos]=left;
				pos=2*pos+1;    // 追踪原堆顶元素位置 
			}
			else if(right>left&&right>data[pos])   // 右子结点最大，交换当前结点和右子结点 
			{
				data[2*pos+2]=data[pos];
				data[pos]=right;
				pos=pos*2+2;
			}
			else if(data[pos]>left&&data[pos]>right)    // 当前结点大于左子结点和右子结点，退出循环 
			break;
		}
	}
}

/**
 * build_heap: 创建大根堆
 * note: 创建堆的算法较为简单: 
 *		1. 以原始数组作为树，从最后一个非叶子结点（下标size/2-1）开始倒序向前遍历每个非叶子结点
 *		2. 对于遍历到的每个非叶子结点，将其结点和其左右子结点的值比较，若左右子结点的较大值大于当前结点值，则交换子结点中的较大值和当前结点值 
 */
void Sort::build_heap(int data[], int size)
{
	for(int i=size/2-1;i>=0;i--)
	{
		int left=(2*i+1<size)?data[2*i+1]:INT_MIN;   // 左子结点的值，注意判断左右子结点是否确实存在 
		int right=(2*i+2<size)?data[2*i+2]:INT_MIN;  // 右子结点的值
		
		if(left>right&&left>data[i])    // 左子结点大于当前结点和右子结点，则交换当前结点和左子结点的值 
		{
			data[2*i+1]=data[i];
			data[i]=left;
		}
		if(right>left&&right>data[i])   // 右子结点大于当前结点和左子结点，则交换当前结点和右子结点的值 
		{
			data[2*i+2]=data[i];
			data[i]=right;
		}
	} 
}

/*
 * shell_sort: 希尔排序
 * note: 希尔排序就是使用了步长的插入排序，从第一个元素开始，每次的步长step分别取size/2,size/4,...,1，每次排序的数组的起始下标分别为0,1,2,...,step-1 
 */
void Sort::shell_sort(int data[], int size)
{
	int step=size/2;
	while(step>=1)
	{
		for(int i=0;i<step;i++)    // 待排序的序列的起始下标 
		{
			// 依次将i,i+step,i+2*step,...处的元素插入到其前面的有序序列中 
			for(int k=i;k<size;k+=step)
			{
				// 现在要将k处的位置插入到其之前的有序序列中 
				int pos=k-step, val=data[k]; 
				while(pos>=i&&data[pos]>=val)    // 首先从下标k的序列中前一个元素k-step开始，从后向前查找第一个小于目标值的元素，当前元素就插入到该位置之后 
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
