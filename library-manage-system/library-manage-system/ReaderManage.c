#include "ReaderManage.h"
#include<stdio.h>
#include<stdlib.h>
#include"menu.h"
#include"user.h"
//能否操作读者管理模块
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

void readerManage_init(ReaderManage* rmage, const char* filename)
{
	list_init(&rmage->readerList);
	strcpy(rmage->filename, filename);
	readerManage_loadData(rmage, filename);
}

void readerManage_quit(ReaderManage* rmage)
{
	//保存文件
	FILE* fp = fopen(rmage->filename, "w");
	if (!fp)
	{
		perror("file open failed");
		return;
	}
	fputs("读者号\t读者名\t单位\t联系方式\t可借书量\t已借书量\n", fp);
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
	fgets(buf, BUFSIZ, fp);		//从fp中读取bufsiz大小的数据到buf里面
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
		//读者管理菜单
		int op = readerMenu();
		switch (op)
		{
		case 1:				//读者信息输入
			readerManage_input(rmage);
			break;
		case 2:				//读者信息修改
			readerManage_modify(rmage);
			break;
		case 3:				//读者信息删除
			readerManage_remove(rmage);
			break;
		case 4:				//读者信息查询
			readerManage_search(rmage);
			break;
		case 5:				//读者信息显示
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
	printf("请输入读者信息（读者号 读者名 单位 联系方式 可借书量）");
	Reader* reader = createEmptyReader();
	scanf("%llu %s %s %s %d", &reader->readNumber, reader->readerName, reader->readerUnit, reader->readerTele, &reader->canBorrowBookCnt);
	list_pushBack(&rmage->readerList, reader);
	printf("读者添加成功\n");

}


void readerManage_modify(ReaderManage* rmage)
{
	if (!canOp())
	{
		return;
	}
	printf("请输入要修改的读者号");
	unsigned long long number;
	scanf("%llu", &number);
	Reader* reader = list_find(&rmage->readerList, reader_cmp, number);
	if (!reader)
	{
		printf("你要修改的读者号不存在\n");
		return;
	}
	printf("请输入读者的联系方式和可借书数\n");
	scanf("%s %d", reader->readerTele, &reader->canBorrowBookCnt);
	printf("修改成功\n");
}

void readerManage_remove(ReaderManage* rmage)
{
	if (!canOp())
	{
		return;
	}
	printf("请输入要删除的读者号");
	unsigned long long number;
	scanf("%llu", &number);
	Reader* reader = list_find(&rmage->readerList, reader_cmp, number);
	if (!reader)
	{
		printf("你要删除的读者号不存在\n");
		return;
	}
	list_removeOne(&rmage->readerList, reader);
	printf("读者删除成功\n");
}

void readerManage_search(ReaderManage* rmage)
{
	if (!canOp())
	{
		return;
	}
	printf("请输入要查询的读者号");
	unsigned long long number;
	scanf("%llu", &number);
	Reader* reader = list_find(&rmage->readerList, reader_cmp, number);
	if (!reader)
	{
		printf("%-10s %-10s %-15s %-15s %s %s\n", "读者号 ", "读者名 ", "单位 ", "联系方式 ", "可借书数 ", "已借书数");
		printf("你要查询的读者号不存在\n");
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
	printf("%-10s %-10s %-15s %-15s %s %s\n", "读者号 ", "读者名 ", "单位 ", "联系方式 ", "可借书数 ", "已借书数");
	list_transform(&rmage->readerList, reader_print);
}
