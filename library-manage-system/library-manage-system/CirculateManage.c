#include "CirculateManage.h"
#include<stdio.h>
#include"menu.h"
#include"BookManage.h"
#include"user.h"

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

void circulateManage_init(CirculateManage* cmage, BookManage* bmage, const char* filename)
{
	list_init(&cmage->cirList);
	strcpy(cmage->filename, filename);
	circulateManage_loadData(cmage,filename);

	cmage->bookManage = bmage;
}

void circulateManage_quit(CirculateManage* cmage)
{
	//�����ļ�
	FILE* fp = fopen(cmage->filename, "w");
	if (!fp)
	{
		perror("file open failed");
		return;
	}
	fputs("���ߺ�\t���\t��������\t�黹����\t��ע\n", fp);
	Node* curNode = cmage->cirList.front->next;
	while (curNode)
	{
		cir_save(curNode->data, fp);
		curNode = curNode->next;
	}
	fclose(fp);
}

void circulateManage_loadData(CirculateManage* cmage, const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (!fp)
	{
		perror("file open failed");
		return;
	}
	char buf[BUFSIZ] = { 0 };
	fgets(buf, BUFSIZ, fp);
	while (!feof(fp))
	{
		fgets(buf, BUFSIZ, fp);
		list_pushBack(&cmage->cirList,cir_fromString(buf));
	}
	fclose(fp);
	//list_transform(&cmage->cirList, cir_print);
}

void circulateManage_operation(CirculateManage* cmage)
{
	bool isDone = false;
	while (!isDone)
	{
		int op = bookCirculateMenu();
		switch (op)
		{
		case 1:
			circulateManage_borrowBook(cmage);
			break;
		case 2:
			circulateManage_returnBook(cmage);
			break;
		case 3:
			isDone = true;
			break;
		}
		system("pause");
	}
}

void circulateManage_borrowBook(CirculateManage* cmage)
{
	if (!canOp())
	{
		return;
	}
	printf("���������� ���ߺ� ��� ��������:");
	Circulate* cir = creatEmptyCirculatr();
	scanf("%llu %d %s", &cir->readerNumber, &cir->bookNumber, cir->borrowDate);
	list_pushBack(&cmage->cirList, cir);
	//�ö���Ľ����+1
	foreach(Book * book, &cmage->bookManage->books, )
	{
		if (book->bookNumber =cir->bookNumber)
		{
			book->borrowCnt++;
			Break;
		}
	}
	printf("���������Ϣ�ɹ�\n");
}

bool cmpCir(Circulate* c1, Circulate* c2)
{
	return c1->readerNumber == c2->readerNumber && c1->bookNumber == c2->bookNumber;
}
void circulateManage_returnBook(CirculateManage* cmage)
{
	if (!canOp())
	{
		return;
	}
	printf("�����뻹��� ���ߺ� ���:");
	Circulate cir;
	scanf("%llu %d", &cir.readerNumber, &cir.bookNumber);
	//������û�иö���
	Circulate *picr = list_find(&cmage->cirList, cmpCir, &cir);
	if (!picr)
	{
		printf("û�иö��߽��Ȿ�����Ϣ\n");
		return;
	}
	list_removeOne(&cmage->cirList, picr);
	//�ö���Ľ����-1
	foreach(Book * book, &cmage->bookManage->books, )
	{
		if (book->bookNumber = cir.bookNumber)
		{
			book->borrowCnt--;
			Break;
		}
	}
	printf("����ɹ�\n");
}
