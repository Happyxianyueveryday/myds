#ifndef ARRAYHASHSET_H   
#define ARRAYHASHSET_H
#include "HashElement.h"    
#include "HashSet.h"

using namespace std;

class ArrayHashSet: public HashSet
{
	public:
	// 1. constructor
	ArrayHashSet(string mode, const int (*_rehash)(const HashElement *value)=nullptr);  // ���캯�� 
	
	// 2. copy/move controller
	ArrayHashSet(const ArrayHashSet &other);   			   // �������캯��
	ArrayHashSet &operator= (const ArrayHashSet &other);   // ������ֵ����� 
	ArrayHashSet(ArrayHashSet &&other);                    // �ƶ����캯��
	ArrayHashSet &operator= (ArrayHashSet &&other);        // �ƶ���ֵ����� 
	
	// 3. methods
	void insert(const HashElement *value) override;        // ���ϣ���в���ָ��ֵ     
	void remove(const HashElement *value) override;        // �ӹ�ϣ�����Ƴ�ָ��ֵ    
	bool contain(const HashElement *value) const override; // �жϹ�ϣ�����Ƿ����ָ��ֵ    
	vector<const HashElement *> values() const override;   // ��ù�ϣ��������ֵ���б�  
	int length() const override;                           // ��ȡ��ϣ��ĳ��� 
	string toString() const override;                      // �����ϣ��
	
	// 4. destructor
	~ArrayHashSet();                  // ��ϣ������������������
	
	private:
	// 5. domain
	const HashElement **data;// ��ϣԪ�ش洢���� 
	bool *sign;              // ��ϣԪ��ɾ����־����
	string mode;             // ѡ�õ�ģʽ  
	int size;                // ��ϣ���е�Ԫ������ 
	int max_size;            // ��ϣ���Ͱ����
	const int (*rehash)(const HashElement *value);    // �ٹ�ϣ��ʹ�õ��ٹ�ϣ������ָ�� 
	
	// 6. private functions
	void resize();           // ��ϣ���ݷ��� 
};

/** 
 * ArrayHashSet: ���캯��
 * param _mode: ʹ�õĿ��Ŷ�ַ�������� 
 * param _rehash: �ٹ�ϣ����ʹ�õ��ٹ�ϣ�����������ʹ���ٹ�ϣ���������ṩ�˲��������ʹ���ٹ�ϣ�����ǲ��ṩ��������ʹ��ԭ���Ĺ�ϣ�������ٹ�ϣ 
 */
ArrayHashSet::ArrayHashSet(string _mode, const int (*_rehash)(const HashElement *value))
{
	size=0;
	max_size=13;    // Ĭ�ϵĳ�ʼͰ����Ϊ13 
	data=new const HashElement* [max_size];
	sign=new bool [max_size];
	rehash=_rehash;
	for(int i=0;i<max_size;i++)
	{
		sign[i]=true;      // ��ʼ״̬�±��в�����Ԫ�أ���˶�Ӧ�ı��Ϊ��ɾ������true 
		data[i]=nullptr;
	}
	
	if(_mode=="linear"||_mode=="square"||_mode=="rehash")   // linear: ����̽�鷨��square: ����̽�鷨��rehash:�ٹ�ϣ�� 
	mode=_mode;
	else
	mode="linear";     // �û����벻�Ϸ�ģʽ��Ĭ��ʹ������̽�鷨
}

/**
 * ArrayHashSet: �������캯�� 
 * note: �������캯���Թ�ϣ�������� 
 */
ArrayHashSet::ArrayHashSet(const ArrayHashSet &other)
{
	// 1. ���Դ�����Ա 
	size=other.size;
	max_size=other.max_size;
	mode=other.mode;
	rehash=other.rehash;
	data=new const HashElement* [max_size];
	sign=new bool [max_size];
	for(int i=0;i<max_size;i++)
	{
		if(other.data[i])
		data[i]=other.data[i]->clone();
		else
		data[i]=nullptr;
		sign[i]=other.sign[i];
	}
}

/**
 * operator=: ������ֵ����� 
 * note: �������캯���Թ�ϣ�������� 
 */
ArrayHashSet &ArrayHashSet::operator= (const ArrayHashSet &other)
{
	// 1. �ж��Ƿ�����ֵ 
	if(&other==this)
	return (*this);
	// 2. �ͷ�������ʹ�õĶ���Դ 
	if(max_size!=other.max_size)
	{
		for(int i=0;i<max_size;i++)
		{
			if(data[i])
			delete data[i];
		}
		delete [] data;
		delete [] sign;
		data=new const HashElement* [max_size];
		sign=new bool [max_size];
	}
	// 3. ���Դ�����Ա 
	size=other.size;
	max_size=other.max_size;
	mode=other.mode;
	rehash=other.rehash;
	for(int i=0;i<max_size;i++)
	{
		if(other.data[i])
		data[i]=other.data[i]->clone();
		else
		data[i]=nullptr;
		sign[i]=other.sign[i];
	}
	// 4. ���ص�ǰ�������� 
	return (*this);
}

/**
 * ArrayHashSet: �ƶ����캯�� 
 */ 
ArrayHashSet::ArrayHashSet(ArrayHashSet &&other)
{
	// 1. ǳ����Դ����ĳ�Ա 
	size=other.size;
	max_size=other.max_size;
	data=other.data;
	mode=other.mode;
	sign=other.sign;
	rehash=other.rehash;
	// 2. ����Դ�����ԱΪĬ��ֵ
	other.size=0;
	other.data=new const HashElement* [other.max_size];
	other.sign=new bool [other.max_size];
	for(int i=0;i<other.max_size;i++)
	{
		other.data[i]=nullptr;
		other.sign[i]=true;      // ��ʼ״̬�±��в�����Ԫ�أ���˶�Ӧ�ı��Ϊ��ɾ������true 
	}
}

/** 
 * operator=: �ƶ���ֵ����� 
 */
ArrayHashSet &ArrayHashSet::operator= (ArrayHashSet &&other)
{
	// 1. ��������ֵ 
	if(&other==this)
	return (*this);
	// 2. �ͷ�������ʹ�õĶ���Դ 
	for(int i=0;i<max_size;i++)
	{
		if(data[i])
		delete data[i];
	}
	delete [] data;
	delete [] sign; 
	// 3. ǳ����Դ����ĳ�Ա 
	size=other.size;
	max_size=other.max_size;
	data=other.data;
	mode=other.mode;
	sign=other.sign;
	rehash=other.rehash;
	// 4. ����Դ�����ԱΪĬ��ֵ 
	other.size=0;
	other.data=new const HashElement* [other.max_size];
	other.sign=new bool [other.max_size];
	for(int i=0;i<other.max_size;i++)
	{
		other.data[i]=nullptr;
		other.sign[i]=true;
	}
	// 5. ���ص�ǰ��������� 
	return (*this);
}

/**
 * insert: ���ϣ���в������ֵ 
 * note 1: �����ֵ������Ĺ�ϣԪ�ص���� 
 * note 2: ɾ�����㷨�ܽ����£����ȸ��ݹ�ϣֵ��ѡ��Ľ����ͻ��ģʽ���η��ʸ���Ͱ������ǰͰ��ɾ�����Ϊ��ɾ��(true)���������ͷŵ�ǰͰ�е�Ԫ�أ�����еĻ�����Ȼ�󽫴�����Ԫ�ز��뵽�˴� 
 * note 3: ����ڲ��������ɺ���Ҫ����Ƿ���Ҫ���й�ϣ���� 
 */
void ArrayHashSet::insert(const HashElement *value)
{
	// 0. ����Ԫ���п� 
	if(!value)
	return;
	// 1. ������ǰ�����Ѿ��������߹�ϣ�����Ѿ�������ֵͬ�������ʧ�� 
	if(size==max_size||this->contain(value))
	return;
	// 2. ����Ԫ�ز���Ͱ�ĳ�ʼλ���±�
	int index=(value->hashCode())%max_size;
	// 3. �ӳ�ʼλ���±꿪ʼ����Ԫ�صĲ���λ���±꣬�����û�ѡ���ģʽ��ͬ��ʹ������̽�鷨������̽�鷨�����ٹ�ϣ�� 
	int search_time=(mode=="linear"||mode=="rehash")?max_size:(max_size/2);   // ���̽�����������̽�鷨���ٹ�ϣ�������ֻ��Ҫmax_size��̽�飬����̽�鷨����Ҫmax_size/2�� 
	for(int i=0;i<search_time;i++)
	{
		// ���㵱ǰ̽���λ�� 
		int now=0;
		if(mode=="linear")
		now=(index+i)%max_size;     // ����̽�鷨����̽��(index+0)%max_size, (index+1)%max_size, (index+2)%max_size, ...,���̽��max_size�� 
		else if(mode=="square")
		now=(index+i*i)%max_size;   // ����̽�鷨����̽��(index+0^2)%max_size, (index+1^2)%max_size, (index+2^2)%max_size, (index+3^2)%max_size,...,���̽��max_size/2�� 
		else
		now=(index+i*((rehash==nullptr)?value->hashCode():rehash(value)))%max_size;// �ٹ�ϣ������̽��(index+0*rehash(value))%max_size, (index+1*rehash(value))%max_size, (index+2*rehash(value))%max_size, ...,���̽��max_size��
		
		// ̽�鵽���Բ����λ��ʱ�����жϸ�Ͱ���Ƿ�������ɾ����Ԫ�أ����������ɾ������󽫴�����Ԫ�ز��뵽�˲���Ǹ�ͰΪδɾ�� 
		if(sign[now])     
		{
			if(data[now])
			delete data[now];
			data[now]=value->clone();
			sign[now]=false;
			break;
		}
	}
	size+=1;   // ����Ԫ�صļ����� 
	// 4. ����Ƿ���Ҫ��ϣ���� 
	int threshold=max_size*0.75;    // ��Ԫ����������Ͱ��������0.75ʱ�����й�ϣ������� 
	if(size>threshold)
	resize();
	return;
}

/**
 * remove: �ӹ�ϣ�����Ƴ�ֵ 
 * note: �ڿ��Ŷ�ַ���Ĺ�ϣ��ʵ���У�����Ҫ��������ɾ����������������ɾ����Ҫ�����¼��㣺 
 * 		 1. Ϊʲô��Ҫ����ɾ����
 *		 ��Ϊ��ϣ��Ĳ���ĳ��ֵ���㷨�У�����ʹ�����ֿ��Ŷ�ַ��ͻ���������һ�����ʵ��յ�Ͱλ�ã�����Ϊ��ϣ���в����ڸ�Ԫ�أ����ǹ�ϣ��Ĳ��ҿ������Ա��ԭ�򡣶����������ɾ������ɾ��ĳ��Ԫ��Ϊ�տ��ܵ��²��Ҳ���������Ԫ�أ���Ϊһ�����ʵ���Ͱ����Ϊ���ҽ����ˡ� 
 *		 2. ����ɾ����ν��У�
 *	     ����Ҫɾ��ĳ��Ͱ��Ԫ��ʱ������Ǹ�Ԫ�صĶ�Ӧ�ı�Ǳ������ɣ���ɾ��Ԫ�ء� 
 *       3. ����ɾ���µĹ�ϣ�����㷨�� 
 *       (1) �ڲ��ҹ����У�ֻ������ͰΪ�յ�����²���Ϊ��ϣ���в����ڴ�����Ԫ�أ���Ͱ��Ϊ�յ���ɾ�����Ϊ�棬�Լ������������������ҹ��̡�
 *       (2) �ڲ�������У�ֻҪ������Ǳ������Ϊ"��ɾ��"��Ͱ�ͽ��в��롣 
 *       (3) ��ɾ�������У�ֻ��������Ǳ������Ϊ"δɾ��"��Ͱ�е�Ԫ�غʹ�ɾ����ȵ�����Ž���ɾ���� 
 *       4. ��δ�������ɾ���������µ�ռ�ÿռ��Ԫ�أ�
 *       ռ�ÿռ������ɾ����Ԫ�����ڹ�ϣ������ʱ������ģ���ϣ��������ʱ���Զ�������ЩԪ�ء� 
 * 
 */
void ArrayHashSet::remove(const HashElement *value) 
{
	// 1. �����пպ͵�ǰ��ϣ���п� 
	if(!value||!size)
	return;
	// 2. ʹ�ö�Ӧ�Ŀ��Ŷ�ַ�����в��Ҵ�ɾ��Ԫ�صĲ��� 
	int search_time=(mode=="linear"||mode=="rehash")?max_size:(max_size/2);
	int index=(value->hashCode())%max_size;
	for(int i=0;i<search_time;i++)
	{
		int now=0;
		if(mode=="linear")
		now=(index+i)%max_size;
		else if(mode=="square")
		now=(index+i*i)%max_size;
		else
		now=(index+i*((rehash==nullptr)?value->hashCode():rehash(value)))%max_size;
		
		if(!sign[now])    
		{
			if(data[now]->hashCode()==value->hashCode()&data[now]->equals(value))  // ���ҵ���ɾ��Ԫ�أ���ɾ��Ԫ����������ӦΪδɾ���ģ����ֵӦ����������� 
			sign[now]=true;   // ��������ɾ�� 
			break;
		}
		else if(sign[now]&&!data[now])   // �������Ϊ��ɾ������Ͱ�е�Ԫ��Ϊ�գ���˵����ϣ���в����ڸ�Ԫ�أ�ֱ�ӷ��ؼ��� 
		return;
		else    // ����ǰ���Ϊ����ɾ���Ľ�㣬�������в��Ҵ�ɾ��Ԫ�� 
		continue;  
	}
	size-=1;
}

/**
 * contain: �ж�ĳ��ֵ�Ƿ��ڹ�ϣ���� 
 * note 1: ���������൱�ڹ�ϣ��������㷨�������㷨���£�ʹ�ù�ϣֵ����Ŀ��Ԫ�����ڵ�Ͱλ�ã���ʹ�ö�Ӧ�ĳ�ͻ��㷽�����Ϸ��ʺ�����Ͱ������ǰͰ��Ԫ�غ�Ŀ��Ԫ������ұ��Ϊδɾ�����򷵻�true������������ʵ����Ϊ�Ѿ�ɾ����Ͱ��Ͱ�е�Ԫ��Ϊ�գ���˵��Ŀ��Ԫ�ز��ڹ�ϣ���У�����false 
 * note 2: �ж�Ŀ��Ԫ�غ͵�ǰͰ�е�Ԫ���Ƿ����ʱ��ʹ��java�еı�׼�����ȱȽ�hashCode()�����õ��Ĺ�ϣֵ�Ƿ���ȣ�����ϣֵ���ȣ���Ԫ�ز���ȣ�����ϣֵ��ȣ����һ������equals()����ȷ������Ԫ���Ƿ���ȫ��� 
 */
bool ArrayHashSet::contain(const HashElement *value) const 
{
	// 1. �����пպ͵�ǰ��ϣ���п� 
	if(!value||!size)
	return false;	
	// 2. ʹ�ö�Ӧ�Ŀ��Ŷ�ַ�����в���Ŀ��Ԫ�صĲ��� 
	int search_time=(mode=="linear"||mode=="rehash")?max_size:(max_size/2);
	int index=(value->hashCode())%max_size;
	for(int i=0;i<search_time;i++)
	{
		int now=0;
		if(mode=="linear")
		now=(index+i)%max_size;
		else if(mode=="square")
		now=(index+i*i)%max_size;
		else
		now=(index+i*((rehash==nullptr)?value->hashCode():rehash(value)))%max_size;
		
		if(!sign[now])                   // �������Ϊδɾ����Ͱ�����Ͱ��Ԫ�غ�Ŀ��ֵ�Ƿ���� 
		{
			if(data[now]->hashCode()==value->hashCode()&data[now]->equals(value))
			return true;
		}
		else if(sign[now]&&!data[now])   // �������Ϊ��ɾ������Ͱ�е�Ԫ��Ϊ�գ���˵����ϣ���в����ڸ�Ԫ�أ�ֱ�ӷ���false
		return false;
		else    // ����ǰ���Ϊ����ɾ���Ľ�㣬�������в���
		continue;  
	}
	return false;
}

/** 
 * value: ������ϣ�� 
 */
vector<const HashElement *> ArrayHashSet::values() const
{
	vector<const HashElement *> res;
	for(int i=0;i<max_size;i++)
	{
		if(!sign[i])
		res.push_back(data[i]);
	}
	return res;
}

/** 
 * length: ���ع�ϣ���Ԫ�ظ��� 
 */
int ArrayHashSet::length() const
{
	return size;
}

/**
 * toString: �����ϣ�� 
 */
string ArrayHashSet::toString() const
{
	string res;
	for(int i=0;i<max_size;i++) 
	{
		if(!sign[i])
		res=res+data[i]->toString()+" ";
		else
		res=res+"X"+" "; 
	}
	return res;
}

/**
 * resize: ��ϣ�����ݺ��� 
 * note 1: ��ʱ�������ݣ�
 *		   ����ϣ���е�Ԫ����������Ͱ��������0.75ʱ���ͽ����Զ����� 
 * note 2: ��ν��й�ϣ���ݣ�
 *         (1) �����µ�Ͱ���飬��Ͱ����Ĵ�С����Ϊ��Ͱ��������� 
 *         (2) ����Ͱ�����е�δɾ��Ԫ�����°�����ͬ�Ĺ�ϣ�㷨���뵽��Ͱ�����У���Ͱ�����б��Ϊ��ɾ��������ɾ����Ԫ�ؽ����������ٲ��뵽�µĹ�ϣ���� 
 *         (3) ����ԭʼͰ���飬��Ͱ������Ϊ��ǰ��ϣ���Ͱ���� 
 * note 3: ���ڿ��Ŷ�ַ���Ĺ�ϣ�����ݵ����壿
 *         (1) ��߲���Ч�ʣ����ٹ�ϣ��ͻ 
 *         (2) ��ʱ�����Ѿ�����ɾ���Ĺ�ϣ��Ԫ�� 
 */
void ArrayHashSet::resize()
{
	// 1. �����µ�Ͱ���� 
	int old_size=max_size;
	const HashElement **old_data=data;
	bool *old_sign=sign;
	
	max_size*=2;
	size=0;
	data=new const HashElement* [max_size];
	sign=new bool [max_size];
	for(int i=0;i<max_size;i++)
	{
		data[i]=nullptr;
		sign[i]=true;
	}
	
	// 2. ����Ͱ�����б��Ϊδɾ����Ԫ�ذ�����ͬ�ķ������뵽�µ�Ͱ�����У��Ѿ�����ɾ����Ԫ����������� 
	for(int i=0;i<old_size;i++)
	{
		if(!old_sign[i])
		this->insert(old_data[i]);
	}
	
	// 3. �ͷžɵ�Ͱ�����е�����Ԫ�� 
	for(int i=0;i<old_size;i++)
	{
		if(old_data[i])
		delete old_data[i];
	}
	delete [] old_data;
	delete [] old_sign;
}

/** 
 * ~ArrayHashSet: ��ϣ���������� 
 */
ArrayHashSet::~ArrayHashSet()
{
	for(int i=0;i<max_size;i++)
	{
		if(data[i])
		delete data[i];
	}
	delete [] data;
	delete [] sign;
}


#endif


