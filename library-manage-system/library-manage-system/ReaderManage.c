#include "ReaderManage.h"
#include<stdio.h>
#include<stdlib.h>
#include"menu.h"
#include"user.h"
//�ܷ�������߹���ģ��
static bool canOp()
{
	extern User* g_curUser;
	if (!user_isBookAdmin(g_curUser))
	{
		printf("��û�д�Ȩ�ޣ�ֻ��ͼ�����Ա����\n");
		return false;
	}
	return true;
}

void readerManage_init(ReaderManage* rmage, const char* filename)
{
	list_init(&rmage->readerList);
	strcpy(rmage->filename, filename);
	readerManage_loadData(rmage, filename);
}

void readerManage_quit(ReaderManage* rmage)
{
	//�����ļ�
	FILE* fp = fopen(rmage->filename, "w");
	if (!fp)
	{
		perror("file open failed");
		return;
	}
	fputs("���ߺ�\t������\t��λ\t��ϵ��ʽ\t�ɽ�����\t�ѽ�����\n", fp);
	Node* curNode = rmage->readerList.front->next;
	while (curNode)
	{
		reader_save(curNode->data, fp);
		curNode = curNode->next;
	}
	fclose(fp);
}

void readerManage_loadData(ReaderManage* rmage, const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (!fp)
	{
		perror("fopen failed:");
		return;
	}
	char buf[BUFSIZ] = { 0 };
	fgets(buf, BUFSIZ, fp);		//��fp�ж�ȡbufsiz��С�����ݵ�buf����
	while (!feof(fp))
	{
		fgets(buf, BUFSIZ, fp);
		list_pushBack(&rmage->readerList, reader_fromString(buf));
	}

	fclose(fp);
}

void readerManage_operation(ReaderManage* rmage)
{
	bool isDone = false;
	while (!isDone)
	{
		//���߹���˵�
		int op = readerMenu();
		switch (op)
		{
		case 1:				//������Ϣ����
			readerManage_input(rmage);
			break;
		case 2:				//������Ϣ�޸�
			readerManage_modify(rmage);
			break;
		case 3:				//������Ϣɾ��
			readerManage_remove(rmage);
			break;
		case 4:				//������Ϣ��ѯ
			readerManage_search(rmage);
			break;
		case 5:				//������Ϣ��ʾ
			readerManage_show(rmage);
			break;
		case 6:
			isDone = true;
			break;
		}
		system("pause");
	}
	
}

void readerManage_input(ReaderManage* rmage)
{
	if (!canOp())
	{
		return;
	}
	printf("�����������Ϣ�����ߺ� ������ ��λ ��ϵ��ʽ �ɽ�������");
	Reader* reader = createEmptyReader();
	scanf("%llu %s %s %s %d", &reader->readNumber, reader->readerName, reader->readerUnit, reader->readerTele, &reader->canBorrowBookCnt);
	list_pushBack(&rmage->readerList, reader);
	printf("������ӳɹ�\n");

}


void readerManage_modify(ReaderManage* rmage)
{
	if (!canOp())
	{
		return;
	}
	printf("������Ҫ�޸ĵĶ��ߺ�");
	unsigned long long number;
	scanf("%llu", &number);
	Reader* reader = list_find(&rmage->readerList, reader_cmp, number);
	if (!reader)
	{
		printf("��Ҫ�޸ĵĶ��ߺŲ�����\n");
		return;
	}
	printf("��������ߵ���ϵ��ʽ�Ϳɽ�����\n");
	scanf("%s %d", reader->readerTele, &reader->canBorrowBookCnt);
	printf("�޸ĳɹ�\n");
}

void readerManage_remove(ReaderManage* rmage)
{
	if (!canOp())
	{
		return;
	}
	printf("������Ҫɾ���Ķ��ߺ�");
	unsigned long long number;
	scanf("%llu", &number);
	Reader* reader = list_find(&rmage->readerList, reader_cmp, number);
	if (!reader)
	{
		printf("��Ҫɾ���Ķ��ߺŲ�����\n");
		return;
	}
	list_removeOne(&rmage->readerList, reader);
	printf("����ɾ���ɹ�\n");
}

void readerManage_search(ReaderManage* rmage)
{
	if (!canOp())
	{
		return;
	}
	printf("������Ҫ��ѯ�Ķ��ߺ�");
	unsigned long long number;
	scanf("%llu", &number);
	Reader* reader = list_find(&rmage->readerList, reader_cmp, number);
	if (!reader)
	{
		printf("%-10s %-10s %-15s %-15s %s %s\n", "���ߺ� ", "������ ", "��λ ", "��ϵ��ʽ ", "�ɽ����� ", "�ѽ�����");
		printf("��Ҫ��ѯ�Ķ��ߺŲ�����\n");
		return;
	}
	reader_print(reader);
}

void readerManage_show(ReaderManage* rmage)
{
	if (!canOp())
	{
		return;
	}
	printf("%-10s %-10s %-15s %-15s %s %s\n", "���ߺ� ", "������ ", "��λ ", "��ϵ��ʽ ", "�ɽ����� ", "�ѽ�����");
	list_transform(&rmage->readerList, reader_print);
}
