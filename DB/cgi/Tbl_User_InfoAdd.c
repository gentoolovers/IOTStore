// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_User_InfoAdd.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================

#include <stdio.h>
#include "cgic.h"
#include "../SQLite3/Tbl_User_InfoDAL.h"

int cgiMain(){
    Tbl_User_Info _Tbl_User_Info;
    char UserID[128];
	cgiFormString("UserID",UserID,128);
    _Tbl_User_Info.UserID=atoi(UserID);
    char UserName[128];
	cgiFormString("UserName",UserName,128);
    strcpy(_Tbl_User_Info.UserName,UserName);
    char Password[128];
	cgiFormString("Password",Password,128);
    strcpy(_Tbl_User_Info.Password,Password);
    char RoleID[128];
	cgiFormString("RoleID",RoleID,128);
    _Tbl_User_Info.RoleID=atoi(RoleID);
    char NickName[128];
	cgiFormString("NickName",NickName,128);
    strcpy(_Tbl_User_Info.NickName,NickName);
	
	char strJson[128];
	if (Tbl_User_InfoAdd(_Tbl_User_Info))
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

