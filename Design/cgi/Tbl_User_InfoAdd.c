#include <stdio.h>
#include "cgic.h"
#include "../SQLite3/Tbl_User_InfoDAL.h"

int cgiMain(){
	Tbl_User_Info _Tbl_User_Info;
	char UserID[128];
	cgiFormString("UserID",UserID,128);
	char UserName[128];
	cgiFormString("UserName",UserName,128);
	char Password[128];
	cgiFormString("Password",Password,128);
	char RoleID[128];
	cgiFormString("RoleID",RoleID,128);
	char NickName[128];
	cgiFormString("NickName",NickName,128);
	_Tbl_User_Info.UserID=atoi(UserID);
	strcpy(_Tbl_User_Info.UserName,UserName);
	strcpy(_Tbl_User_Info.Password,Password);
	_Tbl_User_Info.RoleID=atoi(RoleID);
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