// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Role_InfoAdd.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-18
// 负责人：张家铭
// ===================================================================

#include <stdio.h>
#include "../../Res/cgic.h"
#include "../../Res/SQLite3/Tbl_Role_InfoDAL.h"

int cgiMain(){
    Tbl_Role_Info _Tbl_Role_Info;
    char RoleID[128];
	cgiFormString("RoleID",RoleID,128);
    _Tbl_Role_Info.RoleID=atoi(RoleID);
    char RoleName[128];
	cgiFormString("RoleName",RoleName,128);
    strcpy(_Tbl_Role_Info.RoleName,RoleName);
	
	char strJson[128];
	if (Tbl_Role_InfoAdd(_Tbl_Role_Info))
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

