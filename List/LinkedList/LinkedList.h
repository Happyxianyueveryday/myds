#include <iostream>
#include <vector>
#include <string>
#include "List.h"

using namespace std;

struct ListNode
{
    // 1. methods
    ListNode(int _val):val(_val), next(NULL)
    {
    }
    
    // 2. domains
    int val;
    ListNode *next;
};

/**
 * LinkedList : ����������
 */
class LinkedList: public List
{
    public:
    // 1. constructor
    LinkedList ();                           // Ĭ�Ϲ��캯��
    LinkedList (const int _data[], int _size); // �����鹹�쵥������
    LinkedList (const vector<int> &_data);    // ��vector���쵥������

    // 2. copy controller
    LinkedList (const LinkedList  &other);                // �������캯��
    LinkedList  & operator = (const LinkedList &other);  // ������ֵ�����
    
    // 3. methods
    bool get(int index, int &val) const override;    // ����ָ��λ�û�ȡԪ��
    bool insert(int index, int val) override;        // ����ָ��λ�ò���Ԫ��
    bool remove(int index, int &val) override;       // ����ָ��λ��ɾ��Ԫ��
    int length() const override;                     // ��ȡ����ĳ���
    void reverse() override;                         // ԭ�ط�ת��������
    int middle() const override;                     // ���������м����ֵ
    string toString() const override;                // �����ǰ���� 

    // 4. destructor
    ~LinkedList();

    private:
    ListNode *head;
    int size;
};

/**
 * LinkedList: Ĭ�Ϲ��캯��
 */
LinkedList::LinkedList()
{
    head=new ListNode(0);    // ��������ͷ���ƽ��
    size=0;                  // ��ʼ���������������
}

/**
 * LinkedList: �����鹹�쵥������
 * param _data: ����Ԫ������
 * param _size: ��������ĳ���
 */
LinkedList::LinkedList(const int _data[], int _size)
{
    // ��ʼ������
    head=new ListNode(0);
    size=_size;

    // ������Ԫ�����β�������ĩβ
    ListNode *now=head;
    for(int i=0;i<_size;i++)
    {
        now->next=new ListNode(_data[i]);
        now=now->next;
    }
}

/**
 * LinkedList: ��vector�����쵥������
 * param _data: ����Ԫ���б�
 */
LinkedList::LinkedList(const vector<int> &_data)
{
    // ��ʼ������
    head=new ListNode(0);
    size=_data.size();

    // ���б�Ԫ�����β�������ĩβ
    ListNode *now=head;
    for(int i=0;i<_data.size();i++)
    {
        now->next=new ListNode(_data[i]);
        now=now->next;
    }
}

/**
 * List: �������캯��
 * other: ����Դ����
 */
LinkedList::LinkedList(const LinkedList &other)                
{
    // ��ʼ������
    head=new ListNode(0);
    size=other.size;

    // ��Դ�����еĽ�����ο�������ǰ������
    ListNode *othnow=other.head->next;
    ListNode *now=head;

    while(othnow)
    {
        now->next=new ListNode(othnow->val);
        now=now->next;
        othnow=othnow->next;
    }
}

/**
 * operator =: ������ֵ�����
 * other: ��ֵԴ����
 * return: ��ǰ��������
 */
LinkedList & LinkedList::operator = (const LinkedList &other)
{
    // �ж�����ֵ
    if(this==&other) 
    return (*this);

    // �ͷ�ԭ�����е����н��
    ListNode *now=head->next;
    head->next=NULL;
    while(now)
    {
        ListNode *temp=now;
        now=now->next;
        delete temp;
    }

    // ����Դ�����е����н��
    now=head;
    ListNode *othnow=other.head->next;
    while(othnow)
    {
        now->next=new ListNode(othnow->val);
        now=now->next;
        othnow=othnow->next;
    }
    size=other.size;
    return (*this);
}
    
/**
 * get: ����ָ��λ�û�ȡԪ��
 * param index: Ҫ��ȡ��Ԫ�ص�λ����������0��ʼ������
 * param val: ����ȡ��Ԫ��ֵ
 * return: ��λ�úϷ���ȡԪ��ֵ�ɹ����򷵻�true�����򷵻�false
 */
bool LinkedList::get(int index, int &val) const
{
    if(index<0||index>=size)
    return false;

    ListNode *now=head;
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
bool LinkedList::insert(int index, int val)
{
    if(index<0||index>size)
    return false;

    ListNode *now=head;
    ListNode *newnode=new ListNode(val);
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
bool LinkedList::remove(int index, int &val)
{
    if(index<0||index>=size)
    return false;

    ListNode *now=head;
    for(int i=0;i<index;i++)
    {
        now=now->next;
    }
    ListNode *temp=now->next;
    now->next=now->next->next;
    val=temp->val;
    delete temp;
    size-=1;
    return true;
}

/**
 * size: ��ȡ����ĳ���/Ԫ�ظ���
 */
int LinkedList::length() const
{
    return size;
}

/**
 * reverse: ԭ�ط�ת����
 * note: ԭ�ط�ת������������㷨��
 *       1. ˳������ӵڶ�����㿪ʼ�ĺ���ÿ����㣬�����ʵ���ÿ������ԭλ��ɾ����Ȼ����뵽ͷ���ƽ��֮��
 *       2. ˳�����ÿ����㣬��ÿ������nextָ�뷴��ָ��ǰ����ǰһ��Ԫ�أ���һ���������ָ��NULL�������ͷ���ƽ���nextָ��ָ�����һ�����ʵĽ�� 
 */
void LinkedList::reverse()
{
	// �㷨1�汾
	if(!head->next)
	return;
	
    ListNode *nowprev=head->next;
    ListNode *now=head->next->next;
    
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
int LinkedList::middle() const
{
    ListNode *fast=head->next;
    ListNode *slow=head->next;

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
string LinkedList::toString() const
{
	string res;
	ListNode *now=head->next;
	
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
LinkedList::~LinkedList() 
{
    ListNode *now=head;

    while(now)
    {
        ListNode *temp=now;
        now=now->next;
        delete temp;
    }
}
