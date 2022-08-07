#ifndef _CIRCULATEMANAGE_H_
#define _CIRCULATEMANAGE_H_
#include"List.h"
#include"Circulate.h"
struct BookManage;						
typedef struct BookManage BookManage;	//��ȡbookManageģ��ķ���ṹ��
/*�軹����*/
typedef struct CirculateManage
{
	List cirList;		//�ӻ�����Ϣ�б�
	BookManage* bookManage;//ָ��ͼ�����ģ���ָ��
	char filename[128];
}CirculateManage;

void circulateManage_init(CirculateManage* cmage,BookManage *bmage ,const char* filename);
void circulateManage_quit(CirculateManage* cmage);
void circulateManage_loadData(CirculateManage* cmage, const char* filename);
void circulateManage_operation(CirculateManage* cmage);
void circulateManage_borrowBook(CirculateManage* cmage);
void circulateManage_returnBook(CirculateManage* cmage);

#endif // !_CIRCULATEMANAGE_H_

