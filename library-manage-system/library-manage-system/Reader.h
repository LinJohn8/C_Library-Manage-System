#ifndef _READER_H_
#define _READER_H_
#include<stdbool.h>
#include<stdio.h>
/*读者*/
typedef struct Reader
{
	unsigned long long readNumber;	//读者号
	char readerName[10];			//读者名
	char readerUnit[20];			//读者单位
	char readerTele[20];			//联系方式
	int canBorrowBookCnt;			//可借书数量
	int yetBorrowBookCnt;			//已借书数量
}Reader;
//创建空的读者
Reader* createEmptyReader();

Reader* reader_fromString(const char* str);

void reader_save(Reader* reader, FILE* fp);
//输出读者
void reader_print(Reader* reader);
bool reader_cmp(Reader* reader, unsigned long long readerNumber);







#endif // !_READER_H_
