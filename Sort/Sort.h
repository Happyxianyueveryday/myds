#ifndef SORT_H
#define SORT_H
#include <iostream>
#include <string>

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

#endif
