#ifndef _LIST_H_
#define _LIST_H_
#include<stdbool.h>
/*����*/
//�û� ���� ͼ�� ͼ����ͨ
//void* ����ָ�� ���ڶ���

typedef void* variant ;

typedef struct Node
{
	variant data;		//ָ�����ݵ�ָ��
	struct Node* next;	//ָ����һ���ڵ��ָ��

}Node;
/*��װ*/
typedef struct List
{
	int size;		//�ڵ�Ԫ�أ�Ԫ�ؽڵ������������ͷ�ڵ㣩
	Node* front;	//ͷָ��
	Node* tail;		//βָ��
}List;
//�ص���������   ����һ������ָ��LISTCALLBACK����������Ϊvoid������Ϊvariant���ĺ���
typedef void(*LISTCALLBACK)(variant);
//��ʼ������
void list_init(List* list);
//����Ԫ��
void list_pushBack(List* list, variant val);
//ɾ��Ԫ��
void list_removeOne(List* list, variant val);
//ʹ�ûص���������ÿ������
void list_transform(List* list, LISTCALLBACK callBack);
//��������
void list_destory(List* list);

//����
typedef bool (*CMPCALLBACK)(variant, variant);
variant list_find(List* list, CMPCALLBACK cmp,variant val);





#endif // !_LIST_H_

