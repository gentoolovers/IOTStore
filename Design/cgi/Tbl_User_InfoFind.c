#include <stdio.h>
#include "cgic.h"
#include "../SQLite3/Tbl_User_InfoDAL.h"

int cgiMain(){
	char sCon[128];
	cgiFormString("sCon",sCon,128);
	SqlLinkQueue list=init_linkqueue();
	int count=Tbl_User_InfoFind(list,sCon);
	char strJson[1024]="";
	if (count>0)
	{
		strcat(strJson,"{\"jsn\":[");
		INode p=list->front;
		while (p!=list->rear) {
			char str[128];
			p=p->next;
			Tbl_User_Info _Tbl_User_Info=p->data->_Tbl_User_Info;
			sprintf(str,"{\"UserID\":\"%d\",\"UserName\":\"%s\",\"Password\":\"%s\",\"RoleID\":\"%d\",\"NickName\":\"%s\"},",_Tbl_User_Info.UserID,_Tbl_User_Info.UserName,_Tbl_User_Info.Password,_Tbl_User_Info.RoleID,_Tbl_User_Info.NickName);
			strcat(strJson,str);
		}
		strJson[strlen(strJson)-1]='\0';
		strcat(strJson,"]}");
	}
	else
	{
		sprintf(strJson,"{\"jsn\":[]}");
	}
	free_linkqueue(list);
	printf("Content-Type:text/html;charset=UTF-8\n\n");
	printf("%s",strJson);

}