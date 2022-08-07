#ifndef _LIST_H_
#define _LIST_H_
#include<stdbool.h>
/*链表*/
//用户 读者 图书 图书流通
//void* 万能指针 放在堆区

typedef void* variant ;

typedef struct Node
{
	variant data;		//指向数据的指针
	struct Node* next;	//指向下一个节点的指针

}Node;
/*封装*/
typedef struct List
{
	int size;		//节点元素（元素节点个数，不包含头节点）
	Node* front;	//头指针
	Node* tail;		//尾指针
}List;
//回调函数类型   定义一个函数指针LISTCALLBACK，返回类型为void，参数为variant，的函数
typedef void(*LISTCALLBACK)(variant);
//初始化链表
void list_init(List* list);
//插入元素
void list_pushBack(List* list, variant val);
//删除元素
void list_removeOne(List* list, variant val);
//使用回调函数处理每个数据
void list_transform(List* list, LISTCALLBACK callBack);
//销毁链表
void list_destory(List* list);

//查找
typedef bool (*CMPCALLBACK)(variant, variant);
variant list_find(List* list, CMPCALLBACK cmp,variant val);





#endif // !_LIST_H_

