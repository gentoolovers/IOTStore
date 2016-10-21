#include <stdio.h>
#include "../../Res/cgic.h"

int cgiMain()
{
	char user[10],pwd[10];
	cgiFormString("name",user,10);
	cgiFormString("pwd",pwd,10);
	printf("Content-Type:text/html;charset=UTF-8\n\n");
	printf("%s %s",user,pwd);
	return 0;
}
