#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include"menu.h"
#include"List.h"
#include"UserManage.h"
#include"ReaderManage.h"
#include"BookManage.h"
#include"CirculateManage.h"


/*����ϵͳ*/
typedef struct ManageMent
{
	UserManage userManage;		//�û�����ģ��
	ReaderManage readerManage;	//���߹���ģ��
	BookManage bookManage;		//ͼ�����ģ��
	CirculateManage circulateManage;//ͼ����ͨ����ģ��
}ManageMent;
//��ʼ��
void management_init(ManageMent* m)
{
	userManage_init(&m->userManage,"res/data/user.txt");
	readerManage_init(&m->readerManage, "res/data/reader.txt");
	bookManage_init(&m->bookManage, "res/data/book/books.txt");
	circulateManage_init(&m->circulateManage,&m->bookManage, "res/data/book/cir.txt");
}
//�˳�
void management_quit(ManageMent* m)		//ΪʲôҪд��������Ϊ�˳������ļ��ȵȶ�д��������
{
	userManage_quit(&m->userManage);
	readerManage_quit(&m->readerManage);
	bookManage_quit(&m->bookManage);
	circulateManage_quit(&m->circulateManage);
	exit(0);
}
//��¼
void management_login(ManageMent* m)
{
	//��¼
	unsigned long long number;
	char password[10] = { 0 };
	bool ret = false;  //�Ƿ��¼�ɹ�
	int loginCnt = 0;		//���Ե�¼�������������
	do
	{
		printf("�˻�����");
		scanf("%llu", &number);
		getchar();		//���߻�����������\n
		printf("����:");
		gets_s(password, 10);
		//��֤��¼�Ƿ�ɹ�
		ret = userManage_login(&m->userManage, number, password);
		if (ret)
		{
			printf("��¼�ɹ�\n");
			break;
		}
		else
		{
			loginCnt++;
			printf("����ʧ�ܣ�����������,���ǵ�%d�����루��һ����3�λ��ᣩ\n", loginCnt);
			if (loginCnt == 3)
			{
				printf("��¼ʧ��3�Σ������Զ��˳���");
				exit(0);
			}
		}
	} while (!ret);
}
//�����˵�
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
		int op = mainMenu();		//��ȡ���˵���ѡ��
		switch (op)
		{
		case 1:				//�û�����
			userManage_operation(&m->userManage);
			break;
		case 2:				//���߹���
			readerManage_operation(&m->readerManage);
			break;
		case 3:				//ͼ�����
			bookManage_opeation(&m->bookManage);
			break;
		case 4:				//ͼ����ͨ����
			circulateManage_operation(&m->circulateManage);
			break;
		case 5:				//�˳�ϵͳ
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