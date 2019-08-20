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

#endif
