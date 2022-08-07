#include "menu.h"
#include<stdio.h>
#include<stdlib.h>

//提示用户选择
static int select()
{
    int op = -1;
    printf("请选择:");
    scanf_s("%d", &op);
    getchar();
    return op;
}

int welcomeMenu()
{
    system("cls");
    printf("*****欢迎使用图书管理系统*****\n");
    printf("*        1.用户登录          *\n");
    printf("*      任意键退出系统        *\n");
    printf("******************************\n");


    return select();
}

int mainMenu()
{
    system("cls");
    printf("******************************\n");
    printf("*      1.用户管理            *\n");
    printf("*      2.读者管理            *\n");
    printf("*      3.图书管理            *\n");
    printf("*      4.图书流通管理        *\n");
    printf("*      5.退出系统            *\n");
    printf("******************************\n");


    return select();
}

int userMenu()
{
    system("cls");
    printf("******************************\n");
    printf("*      1.用户信息输入        *\n");
    printf("*      2.用户信息修改        *\n");
    printf("*      3.用户信息删除        *\n");
    printf("*      4.用户信息显示        *\n");
    printf("*      5.用户密码修改        *\n");
    printf("*      6.返回主菜单          *\n");
    printf("******************************\n");
    return select();
}

int readerMenu()
{
    system("cls");
    printf("******************************\n");
    printf("*      1.读者信息录入        *\n");
    printf("*      2.读者信息修改        *\n");
    printf("*      3.读者信息删除        *\n");
    printf("*      4.读者信息查询        *\n");
    printf("*      5.读者信息显示        *\n");
    printf("*      6.返回主菜单          *\n");
    printf("******************************\n");

    return select();
}

int bookMenu()
{
    system("cls");
    printf("******************************\n");
    printf("*      1.图书信息输入        *\n");
    printf("*      2.图书信息修改        *\n");
    printf("*      3.图书信息查询        *\n");
    printf("*      4.汇总统计            *\n");
    printf("*      5.返回主菜单          *\n");
    printf("******************************\n");
    return select();
}

int bookSearchMenu()
{
    system("cls");
    printf("******************************\n");
    printf("*      1.按书号查询          *\n");
    printf("*      2.按书名查询          *\n");
    printf("*      3.按作者查询          *\n");
    printf("*      4.按出版社查询        *\n");
    printf("*      5.返回上级菜单        *\n");
    printf("******************************\n");
    return select();
}

int bookCirculateMenu()
{
    system("cls");
    printf("******************************\n");
    printf("*         1.借书             *\n");
    printf("*         2.还书             *\n");
    printf("*         3.返回主菜单       *\n");
    printf("******************************\n");
    return select();
}
