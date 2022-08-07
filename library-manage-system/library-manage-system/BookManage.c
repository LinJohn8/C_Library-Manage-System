#include "BookManage.h"
//#include"Configure.h"
#include"menu.h"
#include<string.h>
#include"user.h"
#include"List.h"

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

void bookManage_init(BookManage* bmage, const char* filename)
{
	SeqList_init(&bmage->books);
	strcpy(bmage->filename , filename);
	/*bmage->useIndex = false;*/

	bookManage_loadData(bmage, filename);
	/*bookMange_createIndex(bmage);*/
}

void bookManage_quit(BookManage* bmage)
{
	//保存文件
	FILE* fp = fopen(bmage->filename, "w");
	if (!fp)
	{
		perror("file open failed");
		return;
	}
	fputs("书号\t书名\t作者\t出版社\t藏书量\t借书量\t指针1\t指针2\t指针3\n", fp);
	foreach(Book * book, &bmage->books)
	{
		book_save(book, fp);
	}

	fclose(fp);
}

void bookManage_loadData(BookManage* bmage, const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (!fp)
	{
		perror("dile open failed");
		return;
	}
	char buf[BUFSIZ] = { 0 };
	fgets(buf, BUFSIZ, fp);
	while (!feof(fp))
	{
		fgets(buf, BUFSIZ, fp);
		SeqList_pushBack(&bmage->books, book_fromString(buf));
	}

	fclose(fp);
}

//void bookMange_createIndex(BookManage* bmage)
//{
//	bmage->useIndex = true;
//	//1.建立图书主文件索引
//	for (int i = bmage->books.size-1; i >=0; i--)
//	{
//		Book* book = bmage->books.data[i];
//
//		for (int k = i-1; k >= 0; k--)
//		{
//			Book* tb = bmage->books.data[k];
//			//每一个都与book的name进行比较，if ==，就把记录号给指针1
//			if (strcmp(book->bookName, tb->bookName) == 0)
//			{
//				book->p1 = tb->recordNumber;
//			}
//		}
//	}
//
//
//	//2.建立书名次关键字索引
//	//3.建立作者次关键字索引
//	//4.建立出版社次关键字索引
//}

//void bookMange_destoryIndex(BookManage* bmage)
//{
//	bmage->useIndex = false;
//}

void bookManage_opeation(BookManage* bmage)
{
	bool isDone = false;
	while (!isDone)
	{
		int op = bookMenu();
		switch (op)
		{
		case 1:
			bookManage_input(bmage);
			break; 
		case 2:
			bookManage_modify(bmage);
			break;
		case 3:
			bookManage_search(bmage);
			break;
		case 4:
			bookManage_statistics(bmage);
			break;
		case 5:
			isDone = true;
			break;
		}
		system("pause");
	}
}

void bookManage_input(BookManage* bmage)
{
	if (!canOp())
	{
		return;
	}
	Book* book = creatEmptyBook();
	printf("请输入（书号 书名 作者 出版社 藏书量）");
	int ret =scanf("%d %s %s %s %d", &book->bookNumber, book->bookName, book->bookAuthor, book->bookPublishHouse, &book->bookCnt);
	if (ret !=5)
	{
		printf("添加图书失败\n");
		free(book);
	}
	printf("添加图书成功\n");
	SeqList_pushBack(&bmage->books, book);
}

void bookManage_modify(BookManage* bmage)
{
	if (!canOp())
	{
		return;
	}
	printf("请输入要修改的图书号:");
	int bookNumber	 = -1;
	scanf("%d", &bookNumber);
	foreach(Book * book, &bmage->books)
	{
		if (book->bookNumber ==bookNumber)
		{
			printf("请输入藏书量，借出数：");
			scanf("%d %d", &book->bookCnt, &book->borrowCnt);
			printf("图书修改成功\n");
			return;
		}
	}
}

void bookManage_search(BookManage* bmage)
{
	bool isDone = false;
	while (!isDone)
	{
		//具体的查询
		int op = bookSearchMenu();
		switch (op)
		{
		case 1:
			bookManage_serarchBookNumber(bmage);
			break;
		case 2:
			bookManage_serarchBookName(bmage);
			break;
		case 3:
			bookManage_serarchBookAuthor(bmage);
			break;
		case 4:
			bookManage_serarchBookPHouse(bmage);
			break;
		case 5:
			isDone = true;
			break;
		}
		system("pause");
	}

}

void bookManage_statistics(BookManage* bmage)
{
	if (!canOp())
	{
		return;
	}
	int cnt = 0;
	//查总共的藏书量
	foreach(Book * book, &bmage->books)
	{
		cnt += book->bookCnt;
	}
	printf("图书馆总藏书%d本\n", cnt);
}

void bookManage_serarchBookNumber(BookManage* bmage)
{
	printf("请输入图书号：");
	int bookNumber = -1;
	scanf("%d", &bookNumber);
	//Book* book = NULL;
	foreach(Book * book, &bmage->books)
	{
		if (book->bookNumber == bookNumber)
		{
			printf("%-8s %-5s %-10s %-10s %-10s %-6s %s\n", "记录号 ", "书号 ", "书名 ", "作者 ", "出版社 ", "藏书量 ", "借出数");
			book_print(book);
			return;
		}
	}
	printf("你查找的图书不存在\n");
}

void bookManage_serarchBookName(BookManage* bmage)
{
	printf("请输入图书名字：");
	char name[20] = { 0 };
	gets_s(name, 20);
	bool isFind = false;
	bool firstName = true;
	foreach(Book * book, &bmage->books)
	{
		if (strcmp(book->bookName , name)==0)
		{
			if (firstName)
			{
				printf("%-8s %-5s %-10s %-10s %-10s %-6s %s\n", "记录号 ", "书号 ", "书名 ", "作者 ", "出版社 ", "藏书量 ", "借出数");
				firstName = false;
			}
			book_print(book);
			isFind = true;
		}
	}
	if (!isFind)
	{
		printf("你查找的图书不存在\n");
	}
}

void bookManage_serarchBookAuthor(BookManage* bmage)
{
	printf("请输入图书作者：");
	char author[20] = { 0 };
	gets_s(author, 20);
	bool isFind = false;
	bool firstName = true;
	foreach(Book * book, &bmage->books)
	{
		if (strcmp(book->bookAuthor, author) == 0)
		{
			if (firstName)
			{
				printf("%-8s %-5s %-10s %-10s %-10s %-6s %s\n", "记录号 ", "书号 ", "书名 ", "作者 ", "出版社 ", "藏书量 ", "借出数");
				firstName = false;
			}
			book_print(book);
			isFind = true;
		}
	}
	if (!isFind)
	{
		printf("你查找的图书不存在\n");
	}
}

void bookManage_serarchBookPHouse(BookManage* bmage)
{
	printf("请输入图书出版社：");
	char phouse[20] = { 0 };
	gets_s(phouse, 20);
	bool isFind = false;
	bool firstName = true;
	foreach(Book * book, &bmage->books)
	{
		if (strcmp(book->bookPublishHouse, phouse) == 0)
		{
			if (firstName)
			{
				printf("%-8s %-5s %-10s %-10s %-10s %-6s %s\n", "记录号 ", "书号 ", "书名 ", "作者 ", "出版社 ", "藏书量 ", "借出数");
				firstName = false;
			}
			book_print(book);
			isFind = true;
		}
	}
	if (!isFind)
	{
		printf("你查找的图书不存在\n");
	}
}
