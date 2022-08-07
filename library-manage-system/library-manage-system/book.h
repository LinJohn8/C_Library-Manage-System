#ifndef _BOOK_H_
#define _BOOK_H_
#include<stdio.h>
/*ͼ��ϵͳ*/
typedef struct Book
{
	int recordNumber;				//��¼��
	int bookNumber;					//���
	char bookName[20];				//����
	char bookAuthor[20];			//����
	char bookPublishHouse[20];		//������
	int bookCnt;					//��������
	int borrowCnt;					//���������
	int p1;							//ָ��1
	int p2;							//ָ��2
	int p3;							//ָ��3
}Book;
//������ͼ��
Book* creatEmptyBook();
//���ַ�������book
Book * book_fromString(const char* str);
void book_save(Book* book, FILE* fp);
//���ͼ����Ϣ
void book_print(Book* book);




#endif // !_BOOK_H_

