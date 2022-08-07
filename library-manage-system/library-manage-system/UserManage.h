#ifndef _USERMANAGE_H_
#define _USERMANAGE_H_
#include"user.h"
#include"List.h"
/*�û�����*/
typedef struct UserManage
{
	List userList;		//�洢�����û�������
	User* curUser;	    //��¼һ�µ�ǰ��¼���û�
	char filename[128];
}UserManage;

//��ʼ������ṹ
void userManage_init(UserManage* umage,const char* filename);

void userManage_quit(UserManage* umage);
//�����û�����
void userManage_loadData(UserManage* umage, const char* filename);
//��֤��¼
bool userManage_login(UserManage* umage, unsigned long long number, const char* password);
//�ж��û��Ƿ��¼
bool userManage_isLogin(UserManage* umage);

//�û�������
void userManage_operation(UserManage* umage);



//�û���Ϣ����
void userManage_input(UserManage* umage);
//�û���Ϣ�޸�
void userManage_modify(UserManage* umage);
//�û���Ϣɾ��
void userManage_remove(UserManage* umage);
//�û���Ϣ��ʾ
void userManage_show(UserManage* umage);
//�û������޸�
void userManage_modifyPassword(UserManage* umage);


#endif // !_USERMANAGE_H_

