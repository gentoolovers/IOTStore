// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_User_InfoFindPage.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#include <stdio.h>
#include "cgic.h"
#include "../SQLite3/Tbl_User_InfoDAL.h"

int cgiMain(){
    char sCon[128];
	char sSort[128];
	char iPageSize[128];
	char iCurrentPageIndex[128];
	cgiFormString("sCon",sCon,128);
	cgiFormString("sSort",sSort,128);
	cgiFormString("iPageSize",iPageSize,128);
	cgiFormString("iCurrentPageIndex",iCurrentPageIndex,128);
	SqlLinkQueue list=init_linkqueue();
	int count=Tbl_User_InfoFindPage(list,sCon,sSort,atoi(iPageSize),atoi(iCurrentPageIndex));
	char strJson[1024]="";
	char str[128];
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
		sprintf(str,"],\"iTotalPageCount\":%d}",Tbl_User_InfoGetTotalPageCount(sCon,atoi(iPageSize)));
		strcat(strJson,str);
	}
	else
	{
		sprintf(strJson,"{\"jsn\":[],\"iTotalPageCount\":0}");
	}
	free_linkqueue(list);
	printf("Content-Type:text/html;charset=UTF-8\n\n");
	printf("%s",strJson);

}

