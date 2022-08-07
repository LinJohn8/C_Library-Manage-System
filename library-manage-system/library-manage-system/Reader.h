#ifndef _READER_H_
#define _READER_H_
#include<stdbool.h>
#include<stdio.h>
/*����*/
typedef struct Reader
{
	unsigned long long readNumber;	//���ߺ�
	char readerName[10];			//������
	char readerUnit[20];			//���ߵ�λ
	char readerTele[20];			//��ϵ��ʽ
	int canBorrowBookCnt;			//�ɽ�������
	int yetBorrowBookCnt;			//�ѽ�������
}Reader;
//�����յĶ���
Reader* createEmptyReader();

Reader* reader_fromString(const char* str);

void reader_save(Reader* reader, FILE* fp);
//�������
void reader_print(Reader* reader);
bool reader_cmp(Reader* reader, unsigned long long readerNumber);







#endif // !_READER_H_
