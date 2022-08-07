#include "UserManage.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<malloc.h>
#include"menu.h"
User* g_curUser = NULL;	//全局的当前用户指针

void userManage_init(UserManage* umage, const char* filename)
{
	list_init(&umage->userList);//初始化用户链表
	umage->curUser = NULL;
	strcpy(umage->filename, filename);
	userManage_loadData(umage,filename);
}


void userManage_quit(UserManage* umage)
{
	//保存文件
	FILE* fp = fopen(umage->filename, "w");
	if (!fp)
	{
		perror("file open failed");
		return;
	}
	fputs("用户名\t密码\t权限类型\n",fp);
	Node* curNode = umage->userList.front->next;
	while (curNode)
	{
		user_save(curNode->data, fp);
		curNode = curNode->next;
	}
	fclose(fp);
}

void userManage_loadData(UserManage* umage, const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (!fp)
	{
		perror("fopen failed");
		return;
	}
	//读取获取数据
	char buf[BUFSIZ] = { 0 };	//BUFSIZ是stdio.h里面的，代表512        这个是缓冲区
	fgets(buf, BUFSIZ, fp);		//读取表头并丢弃
	//获取真的数据
	while (!feof(fp))		//feof判断文件是否结束
	{
		fgets(buf, BUFSIZ, fp);
		list_pushBack(&umage->userList, user_formString(buf));
	
	}






	fclose(fp);
}

static bool cmpUser(User* u1, User* u2)
{
	return(u1->number == u2->number && strcmp(u1->password, u2->password)==0);
}
bool userManage_login(UserManage* umage, unsigned long long number, const char* password)
{
	User u;
	u.number = number;
	strcpy(u.password, password);
	//查找number和password是否存在
	User* user = list_find(&umage->userList, cmpUser, &u);
	if (!user)
	{
		return false;
	}
	umage->curUser = user;
	g_curUser = user;
	return true;
}

bool userManage_isLogin(UserManage* umage)
{
	return umage->curUser != NULL;
}

void userManage_operation(UserManage* umage)
{
	bool isDone = false;	//是否退出
	while (!isDone)
	{
		int op = userMenu();
		switch (op)
		{
		case 1:
			userManage_input(umage);
			break;
		case 2:
			userManage_modify(umage);
			break;
		case 3:
			userManage_remove(umage);
			break;
		case 4:
			userManage_show(umage);
			break;
		case 5:
			userManage_modifyPassword(umage);
			break;
		case 6:			//返回主菜单
			isDone = true;
			break;
		}
		system("pause");
	}
}

void userManage_input(UserManage* umage)
{
	if (!user_isSysAdmin(umage->curUser))
	{
		printf("你没有权限,只能由系统管理员操作\n");
		return;
	}

	printf("请输入用户ID，密码，类型\n");
	User* user = createEmptyUser();
	int ret =scanf("%llu %s %d", &user->number, user->password, &user->type);
	if (ret ==3)
	{
		printf("用户添加成功\n");
		list_pushBack(&umage->userList, user);
	}


}

bool user_cmp(variant v1, variant v2)
{
	User* user = v1;
	unsigned long long number = v2;
	return user->number == number;
}
void userManage_modify(UserManage* umage)
{
	if (!user_isSysAdmin(umage->curUser))
	{
		printf("你没有权限,只能由系统管理员操作\n");
		return;
	}
	printf("请输入你要修改的用户id\n");
	unsigned long long number = -1;
	scanf("%llu", &number);
	//查找id为number的用户
	User* user = list_find(&umage->userList, user_cmp, number);
	if (!user)	//假的	
	{
		printf("对不起，你要修改的用户不存在。\n");
		return;
	}
	printf("请输入需要的新的用户类型（1，2，3）\n");
	if (scanf("%d", &user->type) == 1)
	{
		printf("用户修改成功\n");
	}

}

void userManage_remove(UserManage* umage)
{
	if (!user_isSysAdmin(umage->curUser))
	{
		printf("你没有权限,只能由系统管理员操作\n");
		return;
	}
	printf("请输入要删除的用户id");
	unsigned long long number = -1;
	scanf("%llu", &number);
	User* user = list_find(&umage->userList, user_cmp, number);
	if (!user)
	{
		printf("对不起，你要删除的用户不存在\n");
		return;
	}
	list_removeOne(&umage->userList, user);
	printf("用户删除成功\n");
}

void userManage_show(UserManage* umage)
{
	if (!user_isSysAdmin(umage->curUser))
	{
		printf("你没有权限,只能由系统管理员操作\n");
		return;
	}
	printf("用户ID     用户密码   用户类型\n");
	list_transform(&umage->userList, user_print);
}

void userManage_modifyPassword(UserManage* umage)
{
	if (!userManage_isLogin(umage))
	{
		printf("你还没有登录，请登录后重试。\n");
		return;
	}
	printf("请输入新的密码");
	gets_s(umage->curUser->password, 10);
	printf("密码修改成功,你的新密码为：%s\n", umage->curUser->password);

}
