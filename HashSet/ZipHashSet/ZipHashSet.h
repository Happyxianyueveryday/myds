#ifndef ZIPHASHSET_H 
#define ZIPHASHSET_H
#include "HashSet.h"
#include <iostream>
#include <string>
#include <vector> 

using namespace std;

template <typename T>
struct ListNode
{
    ListNode(T _val=T()):val(_val), next(NULL)
    {
    }
    const T val;        // ��ǰ���洢�Ĺ�ϣԪ�ض��󣬹�ϣ���ṩ�޸Ķ���Ĺ��ܣ���˽��ֵ����Ϊconst 
    ListNode *next;     // ָ��������һ������ָ��
};

/**
 * ZipHashSet: ������ʵ�ֵĹ�ϣ���� 
 */
template<typename T>
class ZipHashSet: public HashSet<T> 
{
    public:
    // 1. constructor
    ZipHashSet();                              // Ĭ�Ϲ��캯��
    ZipHashSet(const vector<T> &data);         // �����鹹���ϣ��

    // 2. copy/move_controller
    ZipHashSet(const ZipHashSet &other);                   // �������캯��������� 
    ZipHashSet &operator= (const ZipHashSet &other);       // ������ֵ������������ 
    ZipHashSet(ZipHashSet &&other);                        // �ƶ����캯�� ��ǳ����/�ƶ���
	ZipHashSet &operator= (ZipHashSet &&other);            // �ƶ���ֵ�������ǳ����/�ƶ��� 

    // 3. methods
    void insert(T value) override;              // ���ϣ���в���ָ��ֵ
    void remove(T value) override;              // �ӹ�ϣ�����Ƴ�ָ��ֵ
    bool contain(T value) const override;       // �жϹ�ϣ�����Ƿ����ָ��ֵ
    vector<T> values() const override;          // ��ù�ϣ��������ֵ���б�
    int length() const override;                // ��ȡ��ϣ���Ԫ�ظ��� 
	string toString() const override;                      // �����ϣ��
    bool operator== (const ZipHashSet &other);             // ����ж������

    // 4. destructor
    ~ZipHashSet();                                         // ��ϣ������������������

    private:
    // 5. domains
    ListNode<T> **data;     // ��ϣ������ṹ
    int capacity;        // ��ϣ��Ͱ��������������ĳ��ȣ����������У���ȡ��Ԫ�صĹ�ϣֵ�󽫹�ϣֵģͰ�������Ϳ��Եõ�����Ĵ�ŵ�Ͱ���±�λ��
    double load_factor;  // ��ϣ��������
    int threshold;       // ��ϣ��������ֵ����ֵ=Ͱ����*�������ӣ�ͨ������������ϣ������ݲ����ǣ���ִ��insert��������Ԫ�غ󣬼���ϣ���е�Ԫ�ظ���size�Ƿ������ֵthreshold�������ڣ������resize�����������ݣ���������ݷ�����μ�resize����
    int size;            // ��ǰ��ϣ���е�Ԫ�ظ���

    // 6. private functions
    void resize();       // ��ϣ�����ݷ���
};

/**
 * ZipHashSet: Ĭ�Ϲ��캯��
 */
template<typename T>
ZipHashSet<T>::ZipHashSet()
{
	size=0;    									// ��ʼ��Ԫ�ظ���Ϊ0
	capacity=16;        						// Ĭ��Ͱ��������ʼֵΪ16��16Ϊ2���ݣ�����ÿ�����ݾ�����2����Ͱ������Ϊ2���������ݣ���Ϊ����ʵ�飬Ͱ������2����������ʱԪ�ع�ϣ��Խɢ���ڸ���Ͱ���ܽ��ƾ��ȷֲ� 
	load_factor=0.75;   						// Ĭ�ϵĸ������ӳ�ʼֵΪ0.75
	threshold=capacity*load_factor;        		// ��ϣ��������ֵ����ֵʼ�յ���Ͱ�������Ը�������
	data=new ListNode<T>* [capacity];     	    // ��ʼ��Ͱ������ÿ��Ͱ�е��������һ��ͷ���ƽ�� 
	
	for(int i=0;i<capacity;i++)
	{
		data[i]=new ListNode<T>();
	}
}

/**
 * ZipHashSet: �����鹹���ϣ���� 
 * param data: ���ڹ����ԭʼ�������� 
 */
template<typename T>
ZipHashSet<T>::ZipHashSet(const vector<T> &_data)
{
	size=0;    									// ��ʼ��Ԫ�ظ���Ϊ0
	capacity=16;        						// Ĭ��Ͱ��������ʼֵΪ16
	load_factor=0.75;   						// Ĭ�ϵĸ������ӳ�ʼֵΪ0.75
	threshold=capacity*load_factor;        		// ��ϣ��������ֵ����ֵʼ�յ���Ͱ�������Ը�������
	data=new ListNode<T>* [capacity];     			// ��ʼ��Ͱ������ÿ��Ͱ�е��������һ��ͷ���ƽ��
	
	for(int i=0;i<capacity;i++)
	{
		data[i]=new ListNode<T>();
	}
	
	for(int i=0;i<_data.size();i++)
	{
		this->insert(_data[i]);
	}
}

/**
 * ZipHashSet: �������캯�� 
 */
template<typename T>
ZipHashSet<T>::ZipHashSet(const ZipHashSet &other)
{
	size=other.size;    									
	capacity=other.capacity;        						
	load_factor=other.load_factor;   						
	threshold=capacity*load_factor;
	data=new ListNode<T>* [capacity];     		
	
	for(int i=0;i<capacity;i++)
	{
		data[i]=new ListNode<T>();
		ListNode<T> *now=data[i], *othnow=other.data[i]->next;
		while(othnow)
		{
			now->next=new ListNode<T>(othnow->val);   // ʹ�ÿ������캯�����߿�����ֵ�����ʱ���������ϣ��Ԫ�� 
			now=now->next;
			othnow=othnow->next;
		}
	}
}

/**
 * operator=: ������ֵ����� 
 */
template<typename T>
ZipHashSet<T> &ZipHashSet<T>::operator= (const ZipHashSet &other)
{
	if(this==&other)
	return (*this);
	
	for(int i=0;i<capacity;i++)
	{
		ListNode<T> *now=data[i];
		while(now)
		{
			ListNode<T> *temp=now;
			now=now->next;
			delete temp;
		}
	}
	delete data;
	
	size=other.size;    									
	capacity=other.capacity;        						
	load_factor=other.load_factor;   						
	threshold=capacity*load_factor;
	data=new ListNode<T>* [capacity];     		
	
	for(int i=0;i<capacity;i++)
	{
		data[i]=new ListNode<T>();
		ListNode<T> *now=data[i], *othnow=other.data[i]->next;
		while(othnow)
		{
			now->next=new ListNode<T>(othnow->val);   // ʹ�ÿ������캯�����߿�����ֵ�����ʱ���������ϣ��Ԫ�� 
			now=now->next;
			othnow=othnow->next;
		}
	}
	
	return (*this);
}

/**
 * ZipHashSet: �ƶ����캯�� 
 */
template<typename T>
ZipHashSet<T>::ZipHashSet(ZipHashSet<T> &&other) 
{
	// 1. �ӿ���Դ����ǳ������Ա������ֵ����ǰ���� 
	size=other.size;           // ��ϣ��Ԫ�ظ��� 
	capacity=other.capacity;   // ��ϣ��Ͱ����
	load_factor=other.load_factor;   // װ������
	threshold=capacity*load_factor;  // ������ֵ 
	data=other.data;                 // �ײ�洢�ṹָ��
	
	// 2. ������Դ����ĳ�Ա������ֵ�趨ΪĬ��ֵ����Ĭ�Ϲ��캯���е�ȡֵ��
	other.size=0;    								
	other.capacity=16;        					
	other.load_factor=0.75;   					
	other.threshold=capacity*load_factor;        		
	other.data=new ListNode<T>* [capacity];     			
	
	for(int i=0;i<capacity;i++)
	{
		other.data[i]=new ListNode<T>();
	}
}

/**
 * operator=: �ƶ���ֵ�����������cpp11���ƶ������ṩ��ȫ��ǳ����/�ƶ��ֶ�  
 */ 
template<typename T>
ZipHashSet<T> &ZipHashSet<T>::operator= (ZipHashSet &&other)
{
	// 1. �ж��Ƿ�Ϊ����ֵ
	if(this==&other)
	return (*this);
	
	// 2. �ͷ����������ʹ�õĶѿռ���Դ
	for(int i=0;i<capacity;i++)
	{
		ListNode<T> *now=data[i];
		while(now)
		{
			ListNode<T> *temp=now;
			now=now->next;
			delete temp;
		}
	}
	
	// 3. �ӿ���Դ����ǳ������Ա������ֵ����ǰ���� 
	size=other.size;           // ��ϣ��Ԫ�ظ��� 
	capacity=other.capacity;   // ��ϣ��Ͱ����
	load_factor=other.load_factor;   // װ������
	threshold=capacity*load_factor;  // ������ֵ 
	data=other.data;                 // �ײ�洢�ṹָ��
	
	// 4. ������Դ����ĳ�Ա������ֵ�趨ΪĬ��ֵ����Ĭ�Ϲ��캯���е�ȡֵ��
	other.size=0;    								
	other.capacity=16;         	 				
	other.load_factor=0.75;   					
	other.threshold=capacity*load_factor;        		
	other.data=new ListNode<T>* [capacity];     			
	for(int i=0;i<capacity;i++)
	{
		other.data[i]=new ListNode<T>();
	}
	
	// 5. ���ص�ǰ���������
	return (*this);
}

/**
 * insert: ���ϣ�����в���Ԫ��ֵ
 * note: �������Ԫ��ֵ�ڹ�ϣ�������Ѿ������ظ����򲻻���в���
 */
template<typename T>
void ZipHashSet<T>::insert(T value) 
{
	// 1. �������ֵ�Ѿ������ڹ�ϣ�����У���������в��� 
	if(this->contain(value))
	return;
	// 2. ����Ӧ�������Ͱλ��
	int index=(value.hashCode())%capacity;
	// 4. ��������뵽��Ӧ��Ͱ��
	ListNode<T> *now=data[index];
	ListNode<T> *newnode=new ListNode<T>(value);
	newnode->next=now->next;
	now->next=newnode;
	// 5. ����Ԫ�ؼ������ж��Ƿ���Ҫ���ݣ���Ԫ������size������ֵthreshold�������resize������������
	size+=1;
	if(size>threshold)
	resize();
	
	return; 
}

/**
 * remove: �ӹ�ϣ������ɾ��ָ��ֵ��Ԫ��
 * note: ����ϣ�����в����ڸ�ֵ����ʵ���ϲ������ɾ�� 
 */
template<typename T>
void ZipHashSet<T>::remove(T value) 
{
	// 1. �����ɾ����ֵ�ڹ�ϣ���е�λ��
	int index=(value.hashCode())%capacity; 
	// 2. ������Ͱ�е���������Ŀ��ֵ�Ĺ�ϣ��Ԫ�أ�ǰ��˫ָ�뷨����ɾ�� 
	ListNode<T> *nowprev=data[index];   
	ListNode<T> *now=data[index]->next;
	while(now)
	{
		// �Ƚ�ʱʹ�úͲ�����ͬ���㷨����ʹ��hashCode�����Ƚϣ���������ٵ���equals�����Ƚϣ����������ֱ����Ϊ�Ƚϵ�����Ԫ�ز���� 
		if(now->val.hashCode()==value.hashCode()&&now->val.equals(value))  
		{
			nowprev->next=now->next;
			delete now;   // ����ListNode����������ϣԪ�صĲ����Ѿ���ListNode������������������ˣ������cpp��RAIIԭ�� 
			size-=1;
			break;
		}	
		else
		{
			nowprev=now;
			now=now->next;
		}
	}
	return;
}

/**
 * contain: �жϸ���ֵ�Ƿ��ڹ�ϣ����
 * note: ������ֵ�ڹ�ϣ�����򷵻�true�����򷵻�false 
 */
template<typename T>
bool ZipHashSet<T>::contain(T value) const
{
	// 1. ����Ӧ�����ڵ�Ͱλ��
	int index=(value.hashCode())%capacity;
	// 2. �Ӹ�Ͱ�ĵ�һ�������㿪ʼ���ν��бȽ�
	// note: �Ƚ��㷨�ǣ����ȵ���hashCode������������бȽϣ���hashCodeֵ��ȣ������==��������н�һ���Ƚ��ж��Ƿ���ȣ���hashCode����ȣ���ֱ����Ϊ����������� 
	ListNode<T> *now=data[index]->next; 
	while(now)
	{
		if(now->val.hashCode()==value.hashCode()&&now->val.equals(value))  // �ȱȽ�hashCode()�����ķ���ֵ�Ƿ���ȣ�������ٱȽ�==���������н�һ���Ƚ� 
		return true;
		else
		now=now->next;   
	}
	return false;
}

/**
 * values: ��ȡ��ϣ�����е�����ֵ���б�
 * return: ��ϣ�����е�����Ԫ�ص��б� 
 */
template<typename T>
vector<T> ZipHashSet<T>::values() const
{
	vector<T> res;
	for(int i=0;i<capacity;i++)
	{
		ListNode<T> *now=data[i]->next;
		while(now)
		{
			res.push_back(now->val);
			now=now->next;
		}
	}
	return res;
}

/**
 * length: ��ȡ��ϣ���Ԫ�ظ��� 
 */
template<typename T>
int ZipHashSet<T>::length() const
{
	return size;
}

/**
 * toString: ���ɹ�ϣ�������ַ��� 
 */
template<typename T>
string ZipHashSet<T>::toString() const
{
    string res;
    for(int i=0;i<capacity;i++)
    {
    	if(i==0)
    	res+="*";
    	else
    	res+="\n*";
    	
    	const ListNode<T> *now=data[i]->next;
    	while(now)
    	{
    		res=res+"->"+now->val.toString();
    		now=now->next;
		}
		res=res+"->NULL";
	}
	return res;
}

/** 
 * operator==: �ж�������ϣ�����Ƿ����
 * note: �ж�������������ϣ���Ƿ���ȵ��㷨���ںܴ���Ż��ռ䣬��Ҫ������ȵ��Ż������������ơ�ͬʱ��Ҫ���ѵ��ǣ���Ϊ����ɾ���Ȳ�����˳����ͬ��������ͨ��ֱ�ӱȽ�������ϣ��Ľṹ���Ƚ�������ϣ���Ƿ����
 * note: �������ʹ�õıȽ��㷨���£�
 *       1. �����жϴ����otherָ���ַ�Ƿ��thisָ����ȣ�����ȣ���ֱ�ӷ���true��������벽��2
 *		 2. Ȼ���жϴ���Ĺ�ϣ�����е�Ԫ�������Ƿ�͵�ǰ��ϣ������ȣ�������ȣ���ֱ�ӷ���true��������벽��3
 *       3. ��������жϵ�ǰ��ϣ�����е�ÿһ��Ԫ���Ƿ��ڹ�ϣ����other�У��������ڣ���ֱ�ӷ���true�����򷵻�false		 
 */ 
template<typename T>
bool ZipHashSet<T>::operator== (const ZipHashSet &other)
{
	if(&other==this)
	return true;
	else if(this->length()!=other.length())
	return false;
	for(int i=0;i<capacity;i++)
	{
		ListNode<T> *now=data[i]->next;
		while(now)
		{
			if(this->contain(now->val))
			now=now->next;
			else
			return false;
		}
	}
	return true;
}

/**
 * resize: ��ϣ���ݷ���
 * note 1: ��ʱ������ϣ���ݣ�
 *         ��ֻҪ��ִ�в�������󣬹�ϣ���е�Ԫ������size����Ͱ������capacity����һ����������ϵ��(load_factor)ʱ�ͷ�����ϣ���ݣ�����������Ϊ: size>capacity*load_factor 
 * note 2: ��ϣ���ݾ����㷨���裺 
 *         ��1. ��Ͱ������(capacity)����Ϊԭ�ȵ���������: capacity=2*capacity
 *			   2. ���¼�����ֵ����: threshoud=capacity*load_factor������load_factorΪ�������ӣ��̶�Ϊ0.75 
 *			   3. �����µ�Ͱ����
 *			   4. ����Ͱ�����е���������֮ǰ��ͬ�㷨���¼����ϣֵ�Ͳ���λ�ã���ʹ��ǳ�����ƶ�����Ͱ���飬��: index=(element->hashCode())%capacity 
 *			   5. �ͷž�Ͱ���飬�µ�Ͱ������Ϊ��ǰ��ϣ���Ͱ���� 
 */
template<typename T>
void ZipHashSet<T>::resize() 
{
	// 1. ��Ͱ����capacity�ӱ�
	int old_capacity=capacity;
	capacity*=2;
	// 2. ���¼�����ֵthreshoud
	threshold=capacity*load_factor;
	// 3. �����µ�Ͱ���飬���ҽ�ԭͰ�����е�ÿ��Ԫ������ʹ����ԭ����ͬ�Ĺ�ϣ�㷨���뵽�µ�Ͱ������
	ListNode<T> **new_data=new ListNode<T>* [capacity]; 
	for(int i=0;i<capacity;i++)
	{
		new_data[i]=new ListNode<T>();
	}
	for(int i=0;i<old_capacity;i++)
	{
		ListNode<T> *now=data[i]->next;
		ListNode<T> *nowprev=data[i];
		while(now)
		{
			int index=now->val.hashCode()%capacity;   // �����µĹ�ϣ��ַ��λ�� 
			nowprev->next=now->next;                  // ��ԭ��ϣ�����Ƴ��ý��      
			now->next=new_data[index]->next;          // ���뵽�µ�Ͱ����������� 
			new_data[index]->next=now;
			now=nowprev->next;                        // �����α�ָ��now 
		}
		delete data[i];       // ɾ��ԭͰ�����е�ͷ�������ƽ�� 
	}
	delete [] data;
	data=new_data;
}

/**
 * ~ZipHashSet: ���������� 
 */
template<typename T>
ZipHashSet<T>::~ZipHashSet()
{
	for(int i=0;i<capacity;i++)
	{
		ListNode<T> *now=data[i];
		while(now)
		{
			ListNode<T> *temp=now;
			now=now->next;
			delete temp;
		}
	}
	delete data;
}

#endif
