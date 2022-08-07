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
		printf("��û�д�Ȩ�ޣ�ֻ��ͼ�����Ա����\n");
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
	//�����ļ�
	FILE* fp = fopen(bmage->filename, "w");
	if (!fp)
	{
		perror("file open failed");
		return;
	}
	fputs("���\t����\t����\t������\t������\t������\tָ��1\tָ��2\tָ��3\n", fp);
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
//	//1.����ͼ�����ļ�����
//	for (int i = bmage->books.size-1; i >=0; i--)
//	{
//		Book* book = bmage->books.data[i];
//
//		for (int k = i-1; k >= 0; k--)
//		{
//			Book* tb = bmage->books.data[k];
//			//ÿһ������book��name���бȽϣ�if ==���ͰѼ�¼�Ÿ�ָ��1
//			if (strcmp(book->bookName, tb->bookName) == 0)
//			{
//				book->p1 = tb->recordNumber;
//			}
//		}
//	}
//
//
//	//2.���������ιؼ�������
//	//3.�������ߴιؼ�������
//	//4.����������ιؼ�������
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
	printf("�����루��� ���� ���� ������ ��������");
	int ret =scanf("%d %s %s %s %d", &book->bookNumber, book->bookName, book->bookAuthor, book->bookPublishHouse, &book->bookCnt);
	if (ret !=5)
	{
		printf("���ͼ��ʧ��\n");
		free(book);
	}
	printf("���ͼ��ɹ�\n");
	SeqList_pushBack(&bmage->books, book);
}

void bookManage_modify(BookManage* bmage)
{
	if (!canOp())
	{
		return;
	}
	printf("������Ҫ�޸ĵ�ͼ���:");
	int bookNumber	 = -1;
	scanf("%d", &bookNumber);
	foreach(Book * book, &bmage->books)
	{
		if (book->bookNumber ==bookNumber)
		{
			printf("��������������������");
			scanf("%d %d", &book->bookCnt, &book->borrowCnt);
			printf("ͼ���޸ĳɹ�\n");
			return;
		}
	}
}

void bookManage_search(BookManage* bmage)
{
	bool isDone = false;
	while (!isDone)
	{
		//����Ĳ�ѯ
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
	//���ܹ��Ĳ�����
	foreach(Book * book, &bmage->books)
	{
		cnt += book->bookCnt;
	}
	printf("ͼ����ܲ���%d��\n", cnt);
}

void bookManage_serarchBookNumber(BookManage* bmage)
{
	printf("������ͼ��ţ�");
	int bookNumber = -1;
	scanf("%d", &bookNumber);
	//Book* book = NULL;
	foreach(Book * book, &bmage->books)
	{
		if (book->bookNumber == bookNumber)
		{
			printf("%-8s %-5s %-10s %-10s %-10s %-6s %s\n", "��¼�� ", "��� ", "���� ", "���� ", "������ ", "������ ", "�����");
			book_print(book);
			return;
		}
	}
	printf("����ҵ�ͼ�鲻����\n");
}

void bookManage_serarchBookName(BookManage* bmage)
{
	printf("������ͼ�����֣�");
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
				printf("%-8s %-5s %-10s %-10s %-10s %-6s %s\n", "��¼�� ", "��� ", "���� ", "���� ", "������ ", "������ ", "�����");
				firstName = false;
			}
			book_print(book);
			isFind = true;
		}
	}
	if (!isFind)
	{
		printf("����ҵ�ͼ�鲻����\n");
	}
}

void bookManage_serarchBookAuthor(BookManage* bmage)
{
	printf("������ͼ�����ߣ�");
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
				printf("%-8s %-5s %-10s %-10s %-10s %-6s %s\n", "��¼�� ", "��� ", "���� ", "���� ", "������ ", "������ ", "�����");
				firstName = false;
			}
			book_print(book);
			isFind = true;
		}
	}
	if (!isFind)
	{
		printf("����ҵ�ͼ�鲻����\n");
	}
}

void bookManage_serarchBookPHouse(BookManage* bmage)
{
	printf("������ͼ������磺");
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
				printf("%-8s %-5s %-10s %-10s %-10s %-6s %s\n", "��¼�� ", "��� ", "���� ", "���� ", "������ ", "������ ", "�����");
				firstName = false;
			}
			book_print(book);
			isFind = true;
		}
	}
	if (!isFind)
	{
		printf("����ҵ�ͼ�鲻����\n");
	}
}
