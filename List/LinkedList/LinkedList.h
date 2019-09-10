#ifndef LINKED_LIST_H 
#define LINKED_LIST_H
#include <iostream>
#include <vector>
#include <string>      
#include "List.h"

using namespace std;

template<typename T>
struct ListNode
{
    // 1. methods
    ListNode(T _val):val(_val), next(NULL)
    {
    }
    
    // 2. domains
    T val;
    ListNode *next;
};

/**
 * LinkedList : ����������
 */
template<typename T>
class LinkedList: public List<T>
{
    public:
    // 1. constructor
    LinkedList();                             // Ĭ�Ϲ��캯��
    LinkedList(const T _data[], int _size);   // �����鹹�쵥������
    LinkedList(const vector<T> &_data);       // ��vector���쵥������

    // 2. copy/move controller
    LinkedList(const LinkedList &other);                // �������캯��
    LinkedList &operator= (const LinkedList &other);     // ������ֵ�����
    LinkedList(LinkedList &&other);                      // �ƶ����캯��
	LinkedList &operator= (LinkedList &&other);           // �ƶ���ֵ����� 
    
    // 3. methods
    bool get(int index, T &val) const override;    // ����ָ��λ�û�ȡԪ��
    bool insert(int index, T val) override;        // ����ָ��λ�ò���Ԫ��
    bool remove(int index, T &val) override;       // ����ָ��λ��ɾ��Ԫ��
    int length() const override;                   // ��ȡ����ĳ���
    void reverse() override;                       // ԭ�ط�ת��������
    T middle() const override;                     // ���������м����ֵ
    string toString() const override;              // �����ǰ���� 

    // 4. destructor
    ~LinkedList();

    private:
    ListNode<T> *head;
    int size;
};

/**
 * LinkedList: Ĭ�Ϲ��캯��
 */
template<typename T>
LinkedList<T>::LinkedList()
{
    head=new ListNode<T>(0);    // ��������ͷ���ƽ��
    size=0;                  // ��ʼ���������������
}

/**
 * LinkedList: �����鹹�쵥������
 * param _data: ����Ԫ������
 * param _size: ��������ĳ���
 */
template<typename T>
LinkedList<T>::LinkedList(const T _data[], int _size)
{
    // ��ʼ������
    head=new ListNode<T>(0);
    size=_size;

    // ������Ԫ�����β�������ĩβ
    ListNode<T> *now=head;
    for(int i=0;i<_size;i++)
    {
        now->next=new ListNode<T>(_data[i]);
        now=now->next;
    }
}

/**
 * LinkedList: ��vector�����쵥������
 * param _data: ����Ԫ���б�
 */
template<typename T>
LinkedList<T>::LinkedList(const vector<T> &_data)
{
    // ��ʼ������
    head=new ListNode<T>(T());
    size=_data.size();

    // ���б�Ԫ�����β�������ĩβ
    ListNode<T> *now=head;
    for(int i=0;i<_data.size();i++)
    {
        now->next=new ListNode<T>(_data[i]);
        now=now->next;
    }
}

/**
 * List: �������캯��
 * other: ����Դ����
 */
template<typename T>
LinkedList<T>::LinkedList(const LinkedList &other)                
{
    // ��ʼ������
    head=new ListNode<T>(T());
    size=other.size;

    // ��Դ�����еĽ�����ο�������ǰ������
    ListNode<T> *othnow=other.head->next;
    ListNode<T> *now=head;

    while(othnow)
    {
        now->next=new ListNode<T>(othnow->val);
        now=now->next;
        othnow=othnow->next;
    }
}

/**
 * operator =: ������ֵ�����
 * other: ��ֵԴ����
 * return: ��ǰ��������
 */
template<typename T>
LinkedList<T> &LinkedList<T>::operator= (const LinkedList<T> &other)
{
    // �ж�����ֵ
    if(this==&other) 
    return (*this);

    // �ͷ�ԭ�����е����н��
    ListNode<T> *now=head->next;
    head->next=NULL;
    while(now)
    {
        ListNode<T> *temp=now;
        now=now->next;
        delete temp;
    }

    // ����Դ�����е����н��
    now=head;
    ListNode<T> *othnow=other.head->next;
    while(othnow)
    {
        now->next=new ListNode<T>(othnow->val);
        now=now->next;
        othnow=othnow->next;
    }
    size=other.size;
    return (*this);
}

/**
 * LinkedList: �ƶ����캯�� 
 */
template<typename T>
LinkedList<T>::LinkedList(LinkedList &&other)
{
	// 1. �ӿ���Դ���󿽱���Ա����ֵ
	head=other.head;
	size=other.size;
	// 2. ������Դ����ĳ�Ա��������ΪĬ��ֵ
	other.head=new ListNode<T>(0);
	other.size=0;
}

/**
 * operator=: �ƶ���ֵ�����  
 */
template<typename T>
LinkedList<T> &LinkedList<T>::operator= (LinkedList &&other)
{
	// 1. �ж��Ƿ�Ϊ����ֵ
	if(&other==this)
	return (*this);
	// 2. �ͷŵ�ǰ������ʹ�õĶѿռ�
	ListNode<T> *now=head; 
	while(now)
	{
		ListNode<T> *temp=now;
		now=now->next;
		delete temp;
	}
	// 3. �ӿ���Դ���󿽱���Ա����ֵ
	head=other.head;
	size=other.size;
	// 4. ������Դ����ĳ�Ա��������ΪĬ��ֵ
	other.head=new ListNode<T>(0);
	other.size=0;
	// 5. ���ص�ǰ�������ֵ����
	return (*this); 
}
    
/**
 * get: ����ָ��λ�û�ȡԪ��
 * param index: Ҫ��ȡ��Ԫ�ص�λ����������0��ʼ������
 * param val: ����ȡ��Ԫ��ֵ
 * return: ��λ�úϷ���ȡԪ��ֵ�ɹ����򷵻�true�����򷵻�false
 */
template<typename T>
bool LinkedList<T>::get(int index, T &val) const
{
    if(index<0||index>=size)
    return false;

    ListNode<T> *now=head;
    for(int i=0;i<=index;i++)
    {
        now=now->next;
    }
    val=now->val;
    return true;
}

/**
 * insert: ����ָ��λ�ò���Ԫ��
 * param index: Ҫ����Ԫ�ص�λ������
 * param val: Ҫ�����Ԫ��ֵ
 * return: ������ɹ����򷵻�true�����򷵻�false
 */
template<typename T>
bool LinkedList<T>::insert(int index, T val)
{
    if(index<0||index>size)
    return false;

    ListNode<T> *now=head;
    ListNode<T> *newnode=new ListNode<T>(val);
    for(int i=0;i<index;i++)
    {
        now=now->next;
    }
    newnode->next=now->next;
    now->next=newnode;
    size+=1;
    return true;
}

/**
 * remove: ����ָ��λ��ɾ��Ԫ��
 * param index: ��ɾ����λ���±�
 * param val: ��ɾ����ֵ
 */
template<typename T>
bool LinkedList<T>::remove(int index, T &val)
{
    if(index<0||index>=size)
    return false;

    ListNode<T> *now=head;
    for(int i=0;i<index;i++)
    {
        now=now->next;
    }
    ListNode<T> *temp=now->next;
    now->next=now->next->next;
    val=temp->val;
    delete temp;
    size-=1;
    return true;
}

/**
 * size: ��ȡ����ĳ���/Ԫ�ظ���
 */
template<typename T>
int LinkedList<T>::length() const
{
    return size;
}

/**
 * reverse: ԭ�ط�ת����
 * note: ԭ�ط�ת������������㷨��
 *       1. ˳������ӵڶ�����㿪ʼ�ĺ���ÿ����㣬�����ʵ���ÿ������ԭλ��ɾ����Ȼ����뵽ͷ���ƽ��֮��
 *       2. ˳�����ÿ����㣬��ÿ������nextָ�뷴��ָ��ǰ����ǰһ��Ԫ�أ���һ���������ָ��NULL�������ͷ���ƽ���nextָ��ָ�����һ�����ʵĽ�� 
 */
template<typename T>
void LinkedList<T>::reverse()
{
	// �㷨1�汾
	if(!head->next)
	return;
	
    ListNode<T> *nowprev=head->next;
    ListNode<T> *now=head->next->next;
    
    while(now)
    {
        nowprev->next=now->next;   // ����ǰ���now��ԭλ��ɾ��
        now->next=head->next;
        head->next=now;            // ����ǰ���now���뵽ͷ���ƽ��֮��
        now=nowprev->next;         // �����α�ָ��now��nowprev����Ϊnow��ԭλ�ñ�ɾ�������nowprev���䣬now����Ϊnowprev->next
    }
    
    /*
    // �㷨2�汾
    ListNode *nowprev=NULL;        // ע���׽����ת���Ϊβ��㣬�����ǰ�����Ӧ����NULL����ͷ���ƽ�㣬������д��head�������� 
    ListNode *now=head->next;
    
    while(now)
    {
        ListNode *temp=now->next;
        now->next=nowprev;         // ��ת��������ָ��ָ��
        nowprev=now;               // �����α�ָ��now��nowprev
        now=temp;
    }
    head->next=nowprev;            // ��ͷ���ƽ���nextָ��ָ��ԭ�������һ�����nowprev(ע�ⲻ��now��now==nowprev->next==NULL) 
    */
}

/**
 * middle: ���������м����ֵ 
 * return: �����м����ֵ
 * note: ����������м���һ��ʹ�ÿ���˫ָ�뷨
 */ 
template<typename T>
T LinkedList<T>::middle() const
{
    ListNode<T> *fast=head->next;
    ListNode<T> *slow=head->next;

    while(fast&&fast->next)
    {
        fast=fast->next->next;
        slow=slow->next;
    }

    return slow->val;
}


/**
 * ~toString: �����ǰ���� 
 */
template<typename T>
string LinkedList<T>::toString() const
{
	string res;
	ListNode<T> *now=head->next;
	
	while(now)
	{
		res=res+((now==head->next)?"":"->")+to_string(now->val);	
		now=now->next;
	}
	
	return res;
}

/**
 * ~LinkedList: ��������
 */
template<typename T>
LinkedList<T>::~LinkedList() 
{
    ListNode<T> *now=head;

    while(now)
    {
        ListNode<T> *temp=now;
        now=now->next;
        delete temp;
    }
}

#endif
