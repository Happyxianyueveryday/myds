#include <iostream>
#include <vector>
#include <string>

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
 * List: ����������
 */
class List 
{
    public:
    // 1. constructor
    List();                           // Ĭ�Ϲ��캯��
    List(const int _data[], int _size); // �����鹹�쵥������
    List(const vector<int> &_data);    // ��vector���쵥������

    // 2. copy controller
    List(const List &other);                // �������캯��
    List & operator = (const List &other);  // ������ֵ�����
    
    // 3. methods
    bool get(int index, int &val) const;    // ����ָ��λ�û�ȡԪ��
    bool insert(int index, int val);        // ����ָ��λ�ò���Ԫ��
    bool remove(int index, int &val);       // ����ָ��λ��ɾ��Ԫ��
    int length() const;                     // ��ȡ����ĳ���
    void reverse();                         // ԭ�ط�ת��������
    int middle() const;                     // ���������м����ֵ
    string toString() const;                // �����ǰ���� 

    // 4. destructor
    ~List();

    private:
    ListNode *head;
    int size;
};

/**
 * List: Ĭ�Ϲ��캯��
 */
List::List()
{
    head=new ListNode(0);    // ��������ͷ���ƽ��
    size=0;                  // ��ʼ���������������
}

/**
 * List: �����鹹�쵥������
 * param _data: ����Ԫ������
 * param _size: ��������ĳ���
 */
List::List(const int _data[], int _size)
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
 * List: ��vector�����쵥������
 * param _data: ����Ԫ���б�
 */
List::List(const vector<int> &_data)
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
List::List(const List &other)                
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
List & List::operator = (const List &other)
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
bool List::get(int index, int &val) const
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
bool List::insert(int index, int val)
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
bool List::remove(int index, int &val)
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
int List::length() const
{
    return size;
}

/**
 * reverse: ԭ�ط�ת����
 * note: ԭ�ط�ת������������㷨��
 *       1. ˳������ӵڶ�����㿪ʼ�ĺ���ÿ����㣬�����ʵ���ÿ������ԭλ��ɾ����Ȼ����뵽ͷ���ƽ��֮��
 *       2. ˳�����ÿ����㣬��ÿ������nextָ�뷴��ָ��ǰ����ǰһ��Ԫ�أ���һ���������ָ��NULL�������ͷ���ƽ���nextָ��ָ�����һ�����ʵĽ�� 
 */
void List::reverse()
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
int List::middle() const
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
string List::toString() const
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
 * ~List: ��������
 */
List::~List()
{
    ListNode *now=head;

    while(now)
    {
        ListNode *temp=now;
        now=now->next;
        delete temp;
    }
}
