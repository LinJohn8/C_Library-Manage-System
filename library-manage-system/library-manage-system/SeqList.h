#define _SEQLIST_H_
#ifdef _SEQLIST_H_
#include"Configure.h"
#define _SEQLIST_INIT_SIZE 10//顺序表初始大小

/*顺序表*/

typedef struct SeqList
{
	int size;		//元素个数
	int capacity;	//容量
	variant* data;	//指向数组的指针
}SeqList;
//宏顺序表
//初始化顺序表
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
			printf("扩容失败，不能插入\n");\
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

#define Break break;_i=999999;	//跳出foreach循环

#endif // _SEQLIST_H_
