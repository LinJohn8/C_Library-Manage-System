#include "Circulate.h"
#include"Configure.h"

Circulate* creatEmptyCirculatr()
{
	Circulate* cir = calloc(1, sizeof(Circulate)); 
	if (!cir)
	{
		printf("creatEmptyCirculatr failed");
		return NULL;
	}

    return cir;
}

Circulate* cir_fromString(const char* str)
{
	Circulate* cir = creatEmptyCirculatr();
	int ret =sscanf(str, "%llu %d %s %s %s", &cir->readerNumber, &cir->bookNumber, cir->borrowDate, cir->returnDate, cir->comment);
	if (ret <=0)
	{
		printf("cir_fromString failed\n");
		free(cir);
		return NULL;
	}
    return cir;
}

void cir_print(Circulate* cir)
{
	printf( "%-8llu %-8d %-10s %-10s %s\n", cir->readerNumber, cir->bookNumber, cir->borrowDate, cir->returnDate, cir->comment);
}

void cir_save(Circulate* cir, FILE* fp)
{
	char buf[BUFSIZ] = { 0 };
	sprintf(buf, "%llu\t%d\t%s\t%s\t%d\n", cir->readerNumber,cir->bookNumber,cir->borrowDate,cir->returnDate,cir->comment);
	fputs(buf, fp);
}
