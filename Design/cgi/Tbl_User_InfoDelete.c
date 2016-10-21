#include <stdio.h>
#include "cgic.h"
#include "../SQLite3/Tbl_User_InfoDAL.h"

int cgiMain(){
	char sCon[128];
	cgiFormString("sCon",sCon,128);
	char strJson[128];
	if (Tbl_User_InfoDelete(sCon))
	{
		sprintf(strJson,"{\"jsn\":1}");
	}
	else
	{
		sprintf(strJson,"{\"jsn\":0}");
	}
	printf("Content-Type:text/html;charset=UTF-8\n\n");
	printf("%s",strJson);

}