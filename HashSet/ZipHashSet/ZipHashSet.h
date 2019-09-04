#ifndef ZIPHASHSET_H
#define ZIPHASHSET_H
#include "HashSet.h"
#include "HashElement.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct ListNode
{
    ListNode(const HashElement *_val=NULL):val(_val), next(NULL)
    {
    }
    
    ~ListNode()
    {
    	if(val)         // ע��ָ���пպ������� 
    	delete val;
	}
	 
    const HashElement *val;   // ��ǰ���洢�Ĺ�ϣԪ�ض��󣬹�ϣ���ṩ�޸Ķ���Ĺ��ܣ���˽���Դָ������Ϊ����const 
    ListNode *next;     	  // ָ��������һ������ָ��
};

/**
 * ZipHashSet: ������ʵ�ֵĹ�ϣ����
 * note: ������ȷ��ϣ���ϵĿ������⣬�漰����ǳ������������ڸ����������Ѿ���� 
 */
class ZipHashSet: public HashSet
{
    public:
    // 1. constructor
    ZipHashSet();                                          // Ĭ�Ϲ��캯��
    ZipHashSet(const vector<HashElement *> &data);         // �����鹹���ϣ��

    // 2. copy/move_controller
    ZipHashSet(const ZipHashSet &other);                   // �������캯��������� 
    ZipHashSet &operator= (const ZipHashSet &other);       // ������ֵ������������ 
    ZipHashSet(ZipHashSet &&other);                        // �ƶ����캯�� ��ǳ����/�ƶ���
	ZipHashSet &operator= (ZipHashSet &&other);            // �ƶ���ֵ�������ǳ����/�ƶ��� 

    // 3. methods
    void insert(const HashElement *value) override;        // ���ϣ���в���ָ��ֵ
    void remove(const HashElement *value) override;        // �ӹ�ϣ�����Ƴ�ָ��ֵ
    bool contain(const HashElement *value) const override; // �жϹ�ϣ�����Ƿ����ָ��ֵ
    vector<const HashElement *> values() const override;   // ��ù�ϣ��������ֵ���б�
    int length() const override;                           // ��ȡ��ϣ���Ԫ�ظ��� 
	string toString() const override;                      // �����ϣ��
    bool operator== (const ZipHashSet &other);             // ����ж������

    // 4. destructor
    ~ZipHashSet();                                         // ��ϣ������������������

    private:
    // 5. domains
    ListNode **data;     // ��ϣ������ṹ
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
ZipHashSet::ZipHashSet()
{
	size=0;    									// ��ʼ��Ԫ�ظ���Ϊ0
	capacity=16;        						// Ĭ��Ͱ��������ʼֵΪ16
	load_factor=0.75;   						// Ĭ�ϵĸ������ӳ�ʼֵΪ0.75
	threshold=capacity*load_factor;        		// ��ϣ��������ֵ����ֵʼ�յ���Ͱ�������Ը�������
	data=new ListNode* [capacity];     			// ��ʼ��Ͱ������ÿ��Ͱ�е��������һ��ͷ���ƽ��
	
	for(int i=0;i<capacity;i++)
	{
		data[i]=new ListNode(NULL);
	}
}

/**
 * ZipHashSet: �����鹹���ϣ���� 
 * param data: ���ڹ����ԭʼ�������� 
 * note: ���ǵ�ִ��Ч�ʣ��÷���������������ǳ�������û�������HashElement��������󽫻�ֱ�Ӽ��뵽��ϣ���У���Щ����Ķ����ɵ�ǰ��ZipHashSet�����������������ͷ� 
 */
ZipHashSet::ZipHashSet(const vector<HashElement *> &_data)
{
	size=0;    									// ��ʼ��Ԫ�ظ���Ϊ0
	capacity=16;        						// Ĭ��Ͱ��������ʼֵΪ16
	load_factor=0.75;   						// Ĭ�ϵĸ������ӳ�ʼֵΪ0.75
	threshold=capacity*load_factor;        		// ��ϣ��������ֵ����ֵʼ�յ���Ͱ�������Ը�������
	data=new ListNode* [capacity];     			// ��ʼ��Ͱ������ÿ��Ͱ�е��������һ��ͷ���ƽ��
	
	for(int i=0;i<capacity;i++)
	{
		data[i]=new ListNode(NULL);
	}
	
	for(int i=0;i<_data.size();i++)
	{
		this->insert(_data[i]);
	}
}

/**
 * ZipHashSet: �������캯�� 
 * note: ���ǵ������д�ŵ�Ԫ��Ϊ����ָ�룬��˿������캯��ʹ����� 
 */
ZipHashSet::ZipHashSet(const ZipHashSet &other)
{
	size=other.size;    									
	capacity=other.capacity;        						
	load_factor=other.load_factor;   						
	threshold=capacity*load_factor;
	data=new ListNode* [capacity];     		
	
	for(int i=0;i<capacity;i++)
	{
		data[i]=new ListNode(NULL);
		ListNode *now=data[i], *othnow=other.data[i]->next;
		while(othnow)
		{
			now->next=new ListNode(othnow->val->clone());   // ʹ�ÿ������캯�����߿�����ֵ�����ʱ���������ϣ��Ԫ�� 
			now=now->next;
			othnow=othnow->next;
		}
	}
}

/**
 * operator=: ������ֵ����� 
 * note: ���ǵ������д�ŵ�ָ��Ϊ����ָ�룬��˿�����ֵ�����ʹ����� 
 */
ZipHashSet &ZipHashSet::operator= (const ZipHashSet &other)
{
	if(this==&other)
	return (*this);
	
	for(int i=0;i<capacity;i++)
	{
		ListNode *now=data[i];
		while(now)
		{
			ListNode *temp=now;
			now=now->next;
			delete temp;
		}
	}
	delete data;
	
	size=other.size;    									
	capacity=other.capacity;        						
	load_factor=other.load_factor;   						
	threshold=capacity*load_factor;
	data=new ListNode* [capacity];     		
	
	for(int i=0;i<capacity;i++)
	{
		data[i]=new ListNode(NULL);
		ListNode *now=data[i], *othnow=other.data[i]->next;
		while(othnow)
		{
			now->next=new ListNode(othnow->val->clone());   // ʹ�ÿ������캯�����߿�����ֵ�����ʱ���������ϣ��Ԫ�� 
			now=now->next;
			othnow=othnow->next;
		}
	}
	
	return (*this);
}

/**
 * ZipHashSet: �ƶ����캯�� 
 */
ZipHashSet::ZipHashSet(ZipHashSet &&other)
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
	other.data=new ListNode* [capacity];     			
	
	for(int i=0;i<capacity;i++)
	{
		other.data[i]=new ListNode(NULL);
	}
}

ZipHashSet &ZipHashSet::operator= (ZipHashSet &&other)
{
	// 1. �ж��Ƿ�Ϊ����ֵ
	if(this==&other)
	return (*this);
	
	// 2. �ͷ����������ʹ�õĶѿռ���Դ
	for(int i=0;i<capacity;i++)
	{
		ListNode *now=data[i];
		while(now)
		{
			ListNode *temp=now;
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
	other.data=new ListNode* [capacity];     			
	
	for(int i=0;i<capacity;i++)
	{
		other.data[i]=new ListNode(NULL);
	}
	
	// 5. ���ص�ǰ���������
	return (*this);
}

/**
 * insert: ���ϣ�����в���Ԫ��ֵ
 * note 1: �������Ԫ��ֵ�ڹ�ϣ�������Ѿ������ظ����򲻻���в��� 
 */
void ZipHashSet::insert(const HashElement *value) 
{
	// 1. ����ָ���пգ�������ָ��Ϊ�գ����ߴ����ֵ�Ѿ������ڹ�ϣ�����У���������в��� 
	if(!value||this->contain(value))
	return;
	// 2. ����Ӧ�������Ͱλ��
	int index=(value->hashCode())%capacity;
	// 4. ��������뵽��Ӧ��Ͱ��
	ListNode *now=data[index];
	ListNode *newnode=new ListNode(value->clone());
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
void ZipHashSet::remove(const HashElement *value) 
{
	// 1. ����ָ���пգ�������ָ��Ϊ�գ����������ɾ��
	if(!value)
	return; 
	// 2. �����ɾ����ֵ�ڹ�ϣ���е�λ��
	int index=(value->hashCode())%capacity; 
	// 3. ������Ͱ�е���������Ŀ��ֵ�Ĺ�ϣ��Ԫ�أ�ǰ��˫ָ�뷨����ɾ�� 
	ListNode *nowprev=data[index];   
	ListNode *now=data[index]->next;
	while(now)
	{
		// �Ƚ�ʱʹ�úͲ�����ͬ���㷨����ʹ��hashCode�����Ƚϣ���������ٵ���equals�����Ƚϣ����������ֱ����Ϊ�Ƚϵ�����Ԫ�ز���� 
		if(now->val->hashCode()==value->hashCode()&&now->val->equals(value))  
		{
			nowprev->next=now->next;
			delete now;
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
bool ZipHashSet::contain(const HashElement *value) const 
{
	// 1. ����ָ���п�
	if(!value)
	return false;
	// 2. ����Ӧ�����ڵ�Ͱλ��
	int index=(value->hashCode())%capacity;
	// 3. �Ӹ�Ͱ�ĵ�һ�������㿪ʼ���ν��бȽ�
	// note: �Ƚ��㷨�ǣ����ȵ���hashCode������������бȽϣ���hashCodeֵ��ȣ������==��������н�һ���Ƚ��ж��Ƿ���ȣ���hashCode����ȣ���ֱ����Ϊ����������� 
	ListNode *now=data[index]->next;
	while(now)
	{
		if(now->val->hashCode()==value->hashCode()&&now->val->equals(value))
		return true;
		else
		now=now->next;
	}
	return false;
}

/**
 * values: ��ȡ��ϣ�����е�����ֵ���б�
 * return: ��ϣ�����е�����Ԫ�صĵײ�constָ��
 * note: ���صײ�const��ָ����Ҫ��Ϊ�˱�����ϣ���е����ݲ����û������޸� 
 */
vector<const HashElement *> ZipHashSet::values() const
{
	vector<const HashElement *> res;
	for(int i=0;i<capacity;i++)
	{
		ListNode *now=data[i]->next;
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
int ZipHashSet::length() const
{
	return size;
}

/**
 * toString: ���ɹ�ϣ�������ַ��� 
 */
string ZipHashSet::toString() const
{
    string res;
    for(int i=0;i<capacity;i++)
    {
    	if(i==0)
    	res+="*";
    	else
    	res+="\n*";
    	
    	const ListNode *now=data[i]->next;
    	while(now)
    	{
    		res=res+"->"+now->val->toString();
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
bool ZipHashSet::operator== (const ZipHashSet &other)
{
	if(&other==this)
	return true;
	else if(this->length()!=other.length())
	return false;
	for(int i=0;i<capacity;i++)
	{
		ListNode *now=data[i]->next;
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
void ZipHashSet::resize() 
{
	// 1. ��Ͱ����capacity�ӱ�
	int old_capacity=capacity;
	capacity*=2;
	// 2. ���¼�����ֵthreshoud
	threshold=capacity*load_factor;
	// 3. �����µ�Ͱ���飬���ҽ�ԭͰ�����е�Ԫ������ʹ����ԭ����ͬ�Ĺ�ϣ�㷨���뵽�µ�Ͱ������
	ListNode **new_data=new ListNode* [capacity];
	for(int i=0;i<capacity;i++)
	{
		new_data[i]=new ListNode(NULL);
	}
	for(int i=0;i<old_capacity;i++)
	{
		if(data[i]->next)
		{
			int index=(data[i]->next->val->hashCode())%capacity;   // ��Ϊ��һ��Ͱ�е�Ԫ��ԭ�ȵĹ�ϣֵģͰ����������ȵģ��������ݺ�Ҳ����ȵģ����ֻ��Ҫ�����һ��Ԫ�صĹ�ϣֵ
			delete new_data[index];
			new_data[index]=data[i];
		}
	}
	data=new_data;
}

/**
 * ~ZipHashSet: ���������� 
 */
ZipHashSet::~ZipHashSet()
{
	for(int i=0;i<capacity;i++)
	{
		ListNode *now=data[i];
		while(now)
		{
			ListNode *temp=now;
			now=now->next;
			delete temp;
		}
	}
	delete data;
}

#endif
