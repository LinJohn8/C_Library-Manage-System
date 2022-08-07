#ifndef _CIRCULATE_H
#define _CIRCULATE_H
#include<stdio.h>
/*�軹*/
typedef struct Circulate
{
	unsigned long long readerNumber;	//���ߺ�
	int bookNumber;						//���
	char borrowDate[11];				//��������
	char returnDate[11];				//��������
	char comment[20];					//��ע
}Circulate;

Circulate* creatEmptyCirculatr();
Circulate* cir_fromString(const char* str);
void cir_print(Circulate* cir);
void cir_save(Circulate* cir, FILE* fp);






#endif // !_CIRCULATE_H

