#include "menu.h"
#include<stdio.h>
#include<stdlib.h>

//��ʾ�û�ѡ��
static int select()
{
    int op = -1;
    printf("��ѡ��:");
    scanf_s("%d", &op);
    getchar();
    return op;
}

int welcomeMenu()
{
    system("cls");
    printf("*****��ӭʹ��ͼ�����ϵͳ*****\n");
    printf("*        1.�û���¼          *\n");
    printf("*      ������˳�ϵͳ        *\n");
    printf("******************************\n");


    return select();
}

int mainMenu()
{
    system("cls");
    printf("******************************\n");
    printf("*      1.�û�����            *\n");
    printf("*      2.���߹���            *\n");
    printf("*      3.ͼ�����            *\n");
    printf("*      4.ͼ����ͨ����        *\n");
    printf("*      5.�˳�ϵͳ            *\n");
    printf("******************************\n");


    return select();
}

int userMenu()
{
    system("cls");
    printf("******************************\n");
    printf("*      1.�û���Ϣ����        *\n");
    printf("*      2.�û���Ϣ�޸�        *\n");
    printf("*      3.�û���Ϣɾ��        *\n");
    printf("*      4.�û���Ϣ��ʾ        *\n");
    printf("*      5.�û������޸�        *\n");
    printf("*      6.�������˵�          *\n");
    printf("******************************\n");
    return select();
}

int readerMenu()
{
    system("cls");
    printf("******************************\n");
    printf("*      1.������Ϣ¼��        *\n");
    printf("*      2.������Ϣ�޸�        *\n");
    printf("*      3.������Ϣɾ��        *\n");
    printf("*      4.������Ϣ��ѯ        *\n");
    printf("*      5.������Ϣ��ʾ        *\n");
    printf("*      6.�������˵�          *\n");
    printf("******************************\n");

    return select();
}

int bookMenu()
{
    system("cls");
    printf("******************************\n");
    printf("*      1.ͼ����Ϣ����        *\n");
    printf("*      2.ͼ����Ϣ�޸�        *\n");
    printf("*      3.ͼ����Ϣ��ѯ        *\n");
    printf("*      4.����ͳ��            *\n");
    printf("*      5.�������˵�          *\n");
    printf("******************************\n");
    return select();
}

int bookSearchMenu()
{
    system("cls");
    printf("******************************\n");
    printf("*      1.����Ų�ѯ          *\n");
    printf("*      2.��������ѯ          *\n");
    printf("*      3.�����߲�ѯ          *\n");
    printf("*      4.���������ѯ        *\n");
    printf("*      5.�����ϼ��˵�        *\n");
    printf("******************************\n");
    return select();
}

int bookCirculateMenu()
{
    system("cls");
    printf("******************************\n");
    printf("*         1.����             *\n");
    printf("*         2.����             *\n");
    printf("*         3.�������˵�       *\n");
    printf("******************************\n");
    return select();
}
