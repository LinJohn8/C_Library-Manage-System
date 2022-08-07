#ifndef _READERMANAGE_H_
#define _READERMANAGE_H_
#include"List.h"
#include"Reader.h"


/*读者管理*/
typedef struct ReaderManage
{
	List readerList;		//读者链表
	char filename[128];
}ReaderManage;
//初始化
void readerManage_init(ReaderManage* rmage,const char* filename);
void readerManage_quit(ReaderManage* rmage);
//加载数据
void readerManage_loadData(ReaderManage* rmage, const char* filename);


//操作
void readerManage_operation(ReaderManage* rmage);

//读者信息输入
void readerManage_input(ReaderManage* rmage);
//读者信息修改
void readerManage_modify(ReaderManage* rmage);
//读者信息删除
void readerManage_remove(ReaderManage* rmage);
//读者信息查询
void readerManage_search(ReaderManage* rmage);
//读者信息显示
void readerManage_show(ReaderManage* rmage);


#endif // !_READERMANAGE_H_

