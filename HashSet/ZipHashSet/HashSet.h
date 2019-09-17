#ifndef HASHSET_H   
#define HASHSET_H 
#include <iostream>   
#include <string> 
#include <vector>

using namespace std;

/** 
 * HashSet: ��ϣ���Ͻӿڳ������  
 */
template <typename T>
class HashSet
{    
	public:    
	virtual void insert(T value) = 0;               // ���ϣ���в���ָ��ֵ        
	virtual void remove(T value) = 0;               // �ӹ�ϣ�����Ƴ�ָ��ֵ    
	virtual bool contain(T value) const = 0;        // �жϹ�ϣ�����Ƿ����ָ��ֵ    
	virtual vector<T> values() const = 0;           // ��ù�ϣ��������ֵ���б�  
	virtual int length() const = 0;                 // ��ȡ��ϣ��ĳ��� 
	virtual string toString() const = 0;            // �����ϣ��    
	virtual ~HashSet() {}                           // ��ϣ������������������
};

#endif
