#include "List.h"
#include<stdio.h>
#include<stdbool.h>
#include<malloc.h>

static bool isVaild(List* list)	//��Ч��
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
	//����ͷ�ڵ�
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
	//β��
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
	//ɾ��val
	Node* curNode = list->front->next;		//ָ����Ԫ�ڵ�
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
		//curNode ����Ҫɾ���Ľڵ�
		prevNode->next = curNode->next;	//��ǰһ���ڵ�ָ��Ҫɾ���ڵ����һ���ڵ�
		free(curNode);
	}
}

void list_destory(List* list)
{
	if (!isVaild(list))
	{
		return;
	}
	Node* curNode = list->front;	//ͷ�ڵ�
	Node* nextNode = curNode->next;	//��Ԫ�ڵ�
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
	//������������callBack����
	Node* curNode = list->front->next;
	while (curNode)
	{
		callBack(curNode->data);
		curNode = curNode->next;
	}

}
