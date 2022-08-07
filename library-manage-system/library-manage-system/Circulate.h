#ifndef _CIRCULATE_H
#define _CIRCULATE_H
#include<stdio.h>
/*借还*/
typedef struct Circulate
{
	unsigned long long readerNumber;	//读者号
	int bookNumber;						//书号
	char borrowDate[11];				//借书日期
	char returnDate[11];				//还书日期
	char comment[20];					//备注
}Circulate;

Circulate* creatEmptyCirculatr();
Circulate* cir_fromString(const char* str);
void cir_print(Circulate* cir);
void cir_save(Circulate* cir, FILE* fp);






#endif // !_CIRCULATE_H

