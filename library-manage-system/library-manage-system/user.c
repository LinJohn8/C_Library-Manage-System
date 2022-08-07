#include "user.h"
#include<stdio.h>
#include<malloc.h>

User* createEmptyUser()
{
    User* user = calloc(1, sizeof(User));
	if (!user)
	{
		printf("creatEmptyUser failed");
		return NULL;
	}
    return user;
}

User* user_formString(const char* str)
{
	//²ð·Ö×Ö·û´®
	User* user = createEmptyUser();
	int ret = sscanf(str, "%llu %s %d", &user->number, &user->password, &user->type);
	if (ret <= 0)
	{
		printf("sscanf failed\n");
		free(user);
		return NULL;
	}
	return user;
}

void user_print(User* user)
{
	printf("%-10llu %-10s %d\n", user->number, user->password, user->type);
}

void user_save(User* user, FILE* fp)
{
	char buf[BUFSIZ] = { 0 };
	sprintf(buf, "%llu\t%s\t%d\n", user->number, user->password, user->type);
	fputs(buf, fp);
}

bool user_isSysAdmin(User* user)
{
	return user->type ==UT_SysAdminUser;
}

bool user_isBookAdmin(User* user)
{
	return user->type ==UT_BookAdminUser;
}

bool user_isCommon(User* user)
{
	return user->type ==UT_CommenAdmin;
}


