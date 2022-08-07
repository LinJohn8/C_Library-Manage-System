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
		printf("你没有此权限，只有图书管理员操作\n");
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
	//保存文件
	FILE* fp = fopen(cmage->filename, "w");
	if (!fp)
	{
		perror("file open failed");
		return;
	}
	fputs("读者号\t书号\t借书日期\t归还日期\t备注\n", fp);
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
	printf("请输入借书的 读者号 书号 借书日期:");
	Circulate* cir = creatEmptyCirculatr();
	scanf("%llu %d %s", &cir->readerNumber, &cir->bookNumber, cir->borrowDate);
	list_pushBack(&cmage->cirList, cir);
	//让读书的借出数+1
	foreach(Book * book, &cmage->bookManage->books, )
	{
		if (book->bookNumber =cir->bookNumber)
		{
			book->borrowCnt++;
			Break;
		}
	}
	printf("插入借书信息成功\n");
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
	printf("请输入还书的 读者号 书号:");
	Circulate cir;
	scanf("%llu %d", &cir.readerNumber, &cir.bookNumber);
	//查找有没有该读者
	Circulate *picr = list_find(&cmage->cirList, cmpCir, &cir);
	if (!picr)
	{
		printf("没有该读者借这本书的信息\n");
		return;
	}
	list_removeOne(&cmage->cirList, picr);
	//让读书的借出数-1
	foreach(Book * book, &cmage->bookManage->books, )
	{
		if (book->bookNumber = cir.bookNumber)
		{
			book->borrowCnt--;
			Break;
		}
	}
	printf("还书成功\n");
}
