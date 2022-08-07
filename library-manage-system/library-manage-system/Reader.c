#include "Reader.h"
#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>

Reader* createEmptyReader()
{
    Reader* reader = calloc(1, sizeof(Reader));
	if (!reader)
	{
		printf("calloc reader failed");
		return NULL;
	}
	return reader;
}

Reader* reader_fromString(const char* str)
{
	Reader* reader = createEmptyReader();
	int ret = sscanf(str, "%llu %s %s %s %d %d", &reader->readNumber, reader->readerName, reader->readerUnit, reader->readerTele, &reader->canBorrowBookCnt, &reader->yetBorrowBookCnt);
	if (ret <= 0)
	{
		printf("load reader failed\n");
		free(reader);
		return NULL;
	}
	return reader;
}

void reader_save(Reader* reader, FILE* fp)
{
	char buf[BUFSIZ] = { 0 };
	sprintf(buf, "%llu\t%s\t%s\t%s\t%d\t%d\n",reader->readNumber,reader->readerName,reader->readerUnit,reader->readerTele,reader->canBorrowBookCnt,reader->yetBorrowBookCnt);
	fputs(buf, fp);
}



void reader_print(Reader* reader)
{
	printf("%-10llu %-10s %-15s %-15s %-10d %-10d\n", reader->readNumber, reader->readerName, reader->readerUnit, reader->readerTele, reader->canBorrowBookCnt, reader->yetBorrowBookCnt);

}

bool reader_cmp(Reader* reader, unsigned long long readerNumber)
{
	return reader->readNumber == readerNumber;
}
