#ifndef _USER_H_
#define _USER_H_
#include<stdbool.h>
#include<stdio.h>
/*ö���û�����*/
enum UserType
{
	UT_SysAdminUser =1,		//ϵͳ����Ա 1
	UT_BookAdminUser,		//ͼ�����Ա 2
	UT_CommenAdmin			//��ͨ�û�   3
};
/*�û�*/
typedef struct User
{
	unsigned long long number;//���
	char password[10];		  //����
	char type;				  //����
}User;

//�����յ��û�
User* createEmptyUser();
User* user_formString(const char* str);
//�����û���Ϣ
void user_print(User* user);
void user_save(User* user, FILE* fp);

//�ж��û��Ƿ�ϵͳ����Ա
bool user_isSysAdmin(User* user);
//�ж��û��Ƿ�ͼ�����Ա
bool user_isBookAdmin(User* user);
//�ж��û��Ƿ���ͨ�û�
bool user_isCommon(User* user);


#endif // !_USER_H_
