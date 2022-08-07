#ifndef _BOOKMANAGE_H_
#define _BOOKMANAGE_H_
#include"SeqList.h"
#include"book.h"

/*ͼ�����*/
typedef struct BookManage
{
	SeqList books;		//ͼ��˳���
	char filename[128];	//�洢��Ϣ�ļ�
	bool useIndex;		//�Ƿ�ʹ������
}BookManage;
	
//��ʼ��ͼ�����
void bookManage_init(BookManage* bmage,const char* filename);
//�˳���ϵͳ
void bookManage_quit(BookManage* bmage);
//��������
void bookManage_loadData(BookManage* bmage,const char* filename);
//��������
void bookMange_createIndex(BookManage* bmage);
//��������
void bookMange_destoryIndex(BookManage* bmage);
//����
void bookManage_opeation(BookManage* bmage);

//ͼ����Ϣ���� 
void bookManage_input(BookManage* bmage);
//ͼ����Ϣ�޸� 
void bookManage_modify(BookManage* bmage);
//ͼ����Ϣ��ѯ 
void bookManage_search(BookManage* bmage);
//����ͳ��     
void bookManage_statistics(BookManage* bmage);

//����Ų�ѯ
void bookManage_serarchBookNumber(BookManage* bmage);
//��������ѯ
void bookManage_serarchBookName(BookManage* bmage);
//�����߲�ѯ
void bookManage_serarchBookAuthor(BookManage* bmage);
//���������ѯ
void bookManage_serarchBookPHouse(BookManage* bmage);


#endif // !_BOOKMANAGE_H_

