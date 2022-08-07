#ifndef _READERMANAGE_H_
#define _READERMANAGE_H_
#include"List.h"
#include"Reader.h"


/*���߹���*/
typedef struct ReaderManage
{
	List readerList;		//��������
	char filename[128];
}ReaderManage;
//��ʼ��
void readerManage_init(ReaderManage* rmage,const char* filename);
void readerManage_quit(ReaderManage* rmage);
//��������
void readerManage_loadData(ReaderManage* rmage, const char* filename);


//����
void readerManage_operation(ReaderManage* rmage);

//������Ϣ����
void readerManage_input(ReaderManage* rmage);
//������Ϣ�޸�
void readerManage_modify(ReaderManage* rmage);
//������Ϣɾ��
void readerManage_remove(ReaderManage* rmage);
//������Ϣ��ѯ
void readerManage_search(ReaderManage* rmage);
//������Ϣ��ʾ
void readerManage_show(ReaderManage* rmage);


#endif // !_READERMANAGE_H_

