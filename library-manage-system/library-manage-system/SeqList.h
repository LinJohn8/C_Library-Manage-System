#define _SEQLIST_H_
#ifdef _SEQLIST_H_
#include"Configure.h"
#define _SEQLIST_INIT_SIZE 10//˳����ʼ��С

/*˳���*/

typedef struct SeqList
{
	int size;		//Ԫ�ظ���
	int capacity;	//����
	variant* data;	//ָ�������ָ��
}SeqList;
//��˳���
//��ʼ��˳���
#define SeqList_init(plist)\
(plist)->size =0;\
(plist)->capacity =_SEQLIST_INIT_SIZE;\
(plist)->data =calloc((plist)->capacity,sizeof(variant));\
if (!(plist)->data)\
{\
	printf("(plist) data calloc failed\n");\
}

#define SeqList_pushBack(plist,val)\
if((plist)->size == (plist)->capacity)\
	{\
		realloc((plist)->data, ((plist)->capacity + 10) * sizeof(variant));\
		if (!(plist)->data)\
		{\
			printf("����ʧ�ܣ����ܲ���\n");\
		}\
		else\
		{\
			(plist)->capacity = (plist)->capacity + 10;\
			(plist)->data[(plist)->size++] = val;\
		}\
	}\
else\
{\
	(plist)->data[(plist)->size++] = val;\
}

#define foreach(variable,plist)\
for (int _i = 0,_cnt =0; _i < (plist)->size; _i++,_cnt =0)\
	for (variable =(plist)->data[_i]; _cnt < 1;_cnt++)\

#define Break break;_i=999999;	//����foreachѭ��

#endif // _SEQLIST_H_
