#ifndef _USER_H_
#define _USER_H_
#include<stdbool.h>
#include<stdio.h>
/*枚举用户类型*/
enum UserType
{
	UT_SysAdminUser =1,		//系统管理员 1
	UT_BookAdminUser,		//图书管理员 2
	UT_CommenAdmin			//普通用户   3
};
/*用户*/
typedef struct User
{
	unsigned long long number;//编号
	char password[10];		  //密码
	char type;				  //类型
}User;

//创建空的用户
User* createEmptyUser();
User* user_formString(const char* str);
//创建用户信息
void user_print(User* user);
void user_save(User* user, FILE* fp);

//判断用户是否系统管理员
bool user_isSysAdmin(User* user);
//判断用户是否图书管理员
bool user_isBookAdmin(User* user);
//判断用户是否普通用户
bool user_isCommon(User* user);


#endif // !_USER_H_
