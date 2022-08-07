#include "UserManage.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<malloc.h>
#include"menu.h"
User* g_curUser = NULL;	//ȫ�ֵĵ�ǰ�û�ָ��

void userManage_init(UserManage* umage, const char* filename)
{
	list_init(&umage->userList);//��ʼ���û�����
	umage->curUser = NULL;
	strcpy(umage->filename, filename);
	userManage_loadData(umage,filename);
}


void userManage_quit(UserManage* umage)
{
	//�����ļ�
	FILE* fp = fopen(umage->filename, "w");
	if (!fp)
	{
		perror("file open failed");
		return;
	}
	fputs("�û���\t����\tȨ������\n",fp);
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
	//��ȡ��ȡ����
	char buf[BUFSIZ] = { 0 };	//BUFSIZ��stdio.h����ģ�����512        ����ǻ�����
	fgets(buf, BUFSIZ, fp);		//��ȡ��ͷ������
	//��ȡ�������
	while (!feof(fp))		//feof�ж��ļ��Ƿ����
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
	//����number��password�Ƿ����
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
	bool isDone = false;	//�Ƿ��˳�
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
		case 6:			//�������˵�
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
		printf("��û��Ȩ��,ֻ����ϵͳ����Ա����\n");
		return;
	}

	printf("�������û�ID�����룬����\n");
	User* user = createEmptyUser();
	int ret =scanf("%llu %s %d", &user->number, user->password, &user->type);
	if (ret ==3)
	{
		printf("�û���ӳɹ�\n");
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
		printf("��û��Ȩ��,ֻ����ϵͳ����Ա����\n");
		return;
	}
	printf("��������Ҫ�޸ĵ��û�id\n");
	unsigned long long number = -1;
	scanf("%llu", &number);
	//����idΪnumber���û�
	User* user = list_find(&umage->userList, user_cmp, number);
	if (!user)	//�ٵ�	
	{
		printf("�Բ�����Ҫ�޸ĵ��û������ڡ�\n");
		return;
	}
	printf("��������Ҫ���µ��û����ͣ�1��2��3��\n");
	if (scanf("%d", &user->type) == 1)
	{
		printf("�û��޸ĳɹ�\n");
	}

}

void userManage_remove(UserManage* umage)
{
	if (!user_isSysAdmin(umage->curUser))
	{
		printf("��û��Ȩ��,ֻ����ϵͳ����Ա����\n");
		return;
	}
	printf("������Ҫɾ�����û�id");
	unsigned long long number = -1;
	scanf("%llu", &number);
	User* user = list_find(&umage->userList, user_cmp, number);
	if (!user)
	{
		printf("�Բ�����Ҫɾ�����û�������\n");
		return;
	}
	list_removeOne(&umage->userList, user);
	printf("�û�ɾ���ɹ�\n");
}

void userManage_show(UserManage* umage)
{
	if (!user_isSysAdmin(umage->curUser))
	{
		printf("��û��Ȩ��,ֻ����ϵͳ����Ա����\n");
		return;
	}
	printf("�û�ID     �û�����   �û�����\n");
	list_transform(&umage->userList, user_print);
}

void userManage_modifyPassword(UserManage* umage)
{
	if (!userManage_isLogin(umage))
	{
		printf("�㻹û�е�¼�����¼�����ԡ�\n");
		return;
	}
	printf("�������µ�����");
	gets_s(umage->curUser->password, 10);
	printf("�����޸ĳɹ�,���������Ϊ��%s\n", umage->curUser->password);

}
