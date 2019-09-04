#ifndef HASHSET_H
#define HASHSET_h  
#include "HashElement.h"     
#include <iostream>  
#include <string>
#include <vector>

using namespace std;

/** 
 * HashSet: ��ϣ���Ͻӿڳ������  
 * note 1: ������ϸ˵����ϣ�����Ԫ�صĸ��Ʋ��ԣ���ϣ��ӿ��еĲ�����ʹ����Ԫ�ػ���HashElement��ָ�룬��ʵ�ʲ���ʱʹ��ǳ�������������ܿ��ǣ�����Դ���ͷ���HashSet�����У������б�ʱ���ص�Ҳ��ǳ�����������ǵײ�constָ�룩����Ϊ���󿽱���Ҫ����ʱ�� 
 * note 2: ֻҪʹ��ָ������ĺ�����дʱ��������ϸ�пգ���ע��NULL��nullptr������    
 */
class HashSet
{    
	public:    
	virtual void insert(const HashElement *value) = 0 ;       // ���ϣ���в���ָ��ֵ     
	virtual void remove(const HashElement *value) = 0;        // �ӹ�ϣ�����Ƴ�ָ��ֵ    
	virtual bool contain(const HashElement *value) const = 0; // �жϹ�ϣ�����Ƿ����ָ��ֵ    
	virtual vector<const HashElement *> values() const = 0;   // ��ù�ϣ��������ֵ���б�  
	virtual int length() const = 0;                           // ��ȡ��ϣ��ĳ��� 
	virtual string toString() const = 0;                      // �����ϣ��    
	virtual ~HashSet() {}                                     // ��ϣ������������������
};

#endif
