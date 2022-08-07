#ifndef _BOOKMANAGE_H_
#define _BOOKMANAGE_H_
#include"SeqList.h"
#include"book.h"

/*图书管理*/
typedef struct BookManage
{
	SeqList books;		//图书顺序表
	char filename[128];	//存储信息文件
	bool useIndex;		//是否使用索引
}BookManage;
	
//初始化图书管理
void bookManage_init(BookManage* bmage,const char* filename);
//退出子系统
void bookManage_quit(BookManage* bmage);
//加载数据
void bookManage_loadData(BookManage* bmage,const char* filename);
//创建索引
void bookMange_createIndex(BookManage* bmage);
//销毁索引
void bookMange_destoryIndex(BookManage* bmage);
//操作
void bookManage_opeation(BookManage* bmage);

//图书信息输入 
void bookManage_input(BookManage* bmage);
//图书信息修改 
void bookManage_modify(BookManage* bmage);
//图书信息查询 
void bookManage_search(BookManage* bmage);
//汇总统计     
void bookManage_statistics(BookManage* bmage);

//按书号查询
void bookManage_serarchBookNumber(BookManage* bmage);
//按书名查询
void bookManage_serarchBookName(BookManage* bmage);
//按作者查询
void bookManage_serarchBookAuthor(BookManage* bmage);
//按出版社查询
void bookManage_serarchBookPHouse(BookManage* bmage);


#endif // !_BOOKMANAGE_H_

