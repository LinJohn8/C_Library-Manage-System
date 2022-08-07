#ifndef _BOOK_H_
#define _BOOK_H_
#include<stdio.h>
/*图书系统*/
typedef struct Book
{
	int recordNumber;				//记录号
	int bookNumber;					//书号
	char bookName[20];				//书名
	char bookAuthor[20];			//作者
	char bookPublishHouse[20];		//出版社
	int bookCnt;					//藏书数量
	int borrowCnt;					//借出书数量
	int p1;							//指针1
	int p2;							//指针2
	int p3;							//指针3
}Book;
//创建空图书
Book* creatEmptyBook();
//从字符串创建book
Book * book_fromString(const char* str);
void book_save(Book* book, FILE* fp);
//输出图书信息
void book_print(Book* book);




#endif // !_BOOK_H_

