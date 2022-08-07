#include "List.h"
#include<stdio.h>
#include<stdbool.h>
#include<malloc.h>

static bool isVaild(List* list)	//有效的
{
	if (list == NULL)
	{
		printf("list invaild\n");
	}
	return list != NULL;
}

Node* createNode(variant val)
{
	Node* newNode = calloc(1, sizeof(Node));
	if (!newNode)
	{
		printf("createNode failed");
		return NULL;
	}
	newNode->data = val;
	return newNode;
}

void list_init(List* list)
{
	//申请头节点
	list->front = list->tail = calloc(1, sizeof(Node));
	if (!list->front)
	{
		printf("head Node calloc failed");
		return;
	}
	list->size = 0;
}

void list_pushBack(List* list, variant* val)
{
	if (!isVaild(list))
	{
		return;
	}
	Node* newNode = createNode(val);
	//尾插
	list->tail->next = newNode;
	list->tail = newNode;
	list->size++;

}

void list_removeOne(List* list, variant val)
{
	if (isVaild(list))
	{
		return;
	}
	//删除val
	Node* curNode = list->front->next;		//指向首元节点
	Node* prevNode = list->front;
	while (curNode)
	{
		if (curNode->data ==val)
		{
			break;
		}
		prevNode = curNode;
		curNode = curNode->next;
	}
	if (curNode)
	{
		//curNode 就是要删除的节点
		prevNode->next = curNode->next;	//将前一个节点指向要删除节点的下一个节点
		free(curNode);
	}
}

void list_destory(List* list)
{
	if (!isVaild(list))
	{
		return;
	}
	Node* curNode = list->front;	//头节点
	Node* nextNode = curNode->next;	//首元节点
	while (curNode)
	{
		free(curNode);
		curNode = nextNode;
		if (curNode ==NULL)
		{
			break;
		}
		nextNode = curNode->next;
	}
}

variant list_find(List* list, CMPCALLBACK cmp, variant val)
{
	Node* curNode = list->front->next;
	while (curNode)
	{
		if (cmp(curNode->data,val))
		{
			return curNode->data;
		}
		curNode = curNode->next;
	}
	return NULL;
}

void list_transform(List* list, LISTCALLBACK callBack)
{
	if (!isVaild(list))
	{
		return;
	}
	//遍历链表，调用callBack函数
	Node* curNode = list->front->next;
	while (curNode)
	{
		callBack(curNode->data);
		curNode = curNode->next;
	}

}
