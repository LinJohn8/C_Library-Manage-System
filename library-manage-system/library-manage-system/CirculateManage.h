#ifndef _CIRCULATEMANAGE_H_
#define _CIRCULATEMANAGE_H_
#include"List.h"
#include"Circulate.h"
struct BookManage;						
typedef struct BookManage BookManage;	//获取bookManage模块的方向结构体
/*借还管理*/
typedef struct CirculateManage
{
	List cirList;		//接还书信息列表
	BookManage* bookManage;//指向图书管理模块的指针
	char filename[128];
}CirculateManage;

void circulateManage_init(CirculateManage* cmage,BookManage *bmage ,const char* filename);
void circulateManage_quit(CirculateManage* cmage);
void circulateManage_loadData(CirculateManage* cmage, const char* filename);
void circulateManage_operation(CirculateManage* cmage);
void circulateManage_borrowBook(CirculateManage* cmage);
void circulateManage_returnBook(CirculateManage* cmage);

#endif // !_CIRCULATEMANAGE_H_

