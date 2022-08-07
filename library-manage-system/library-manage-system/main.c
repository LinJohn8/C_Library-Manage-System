#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include"menu.h"
#include"List.h"
#include"UserManage.h"
#include"ReaderManage.h"
#include"BookManage.h"
#include"CirculateManage.h"


/*管理系统*/
typedef struct ManageMent
{
	UserManage userManage;		//用户管理模块
	ReaderManage readerManage;	//读者管理模块
	BookManage bookManage;		//图书管理模块
	CirculateManage circulateManage;//图书流通管理模块
}ManageMent;
//初始化
void management_init(ManageMent* m)
{
	userManage_init(&m->userManage,"res/data/user.txt");
	readerManage_init(&m->readerManage, "res/data/reader.txt");
	bookManage_init(&m->bookManage, "res/data/book/books.txt");
	circulateManage_init(&m->circulateManage,&m->bookManage, "res/data/book/cir.txt");
}
//退出
void management_quit(ManageMent* m)		//为什么要写函数，因为退出保存文件等等都写在这里面
{
	userManage_quit(&m->userManage);
	readerManage_quit(&m->readerManage);
	bookManage_quit(&m->bookManage);
	circulateManage_quit(&m->circulateManage);
	exit(0);
}
//登录
void management_login(ManageMent* m)
{
	//登录
	unsigned long long number;
	char password[10] = { 0 };
	bool ret = false;  //是否登录成功
	int loginCnt = 0;		//尝试登录次数，最多三次
	do
	{
		printf("账户名：");
		scanf("%llu", &number);
		getchar();		//读走缓冲区遗留的\n
		printf("密码:");
		gets_s(password, 10);
		//验证登录是否成功
		ret = userManage_login(&m->userManage, number, password);
		if (ret)
		{
			printf("登录成功\n");
			break;
		}
		else
		{
			loginCnt++;
			printf("输入失败，请重新输入,这是第%d次输入（你一共有3次机会）\n", loginCnt);
			if (loginCnt == 3)
			{
				printf("登录失败3次，程序自动退出。");
				exit(0);
			}
		}
	} while (!ret);
}
//操作菜单
void management_run(ManageMent* m)
{
	int op = welcomeMenu();
	if (op==1)
	{
		management_login(m);
	}
	else
	{
		exit(0);
	}
	while (true)
	{
		int op = mainMenu();		//获取主菜单的选择
		switch (op)
		{
		case 1:				//用户管理
			userManage_operation(&m->userManage);
			break;
		case 2:				//读者管理
			readerManage_operation(&m->readerManage);
			break;
		case 3:				//图书管理
			bookManage_opeation(&m->bookManage);
			break;
		case 4:				//图书流通管理
			circulateManage_operation(&m->circulateManage);
			break;
		case 5:				//退出系统
			management_quit(m);
			break;
		}
	}
}


int main()
{
	ManageMent m;
	management_init(&m);
	management_run(&m);
	

	
	




	
	


	//bookSearchMenu();
	return 0;
}