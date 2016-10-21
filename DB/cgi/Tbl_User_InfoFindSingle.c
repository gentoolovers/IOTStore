// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_User_InfoFindSingle.c
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
	cgiFormString("sCon",sCon,128);
	Tbl_User_Info _Tbl_User_Info=Tbl_User_InfoFindSingle(sCon);
	char strJson[1024];
	if (_Tbl_User_Info.UserID!=0)
	{
		sprintf(strJson,"{\"jsn\":[{\"UserID\":\"%d\",\"UserName\":\"%s\",\"Password\":\"%s\",\"RoleID\":\"%d\",\"NickName\":\"%s\"}]}",_Tbl_User_Info.UserID,_Tbl_User_Info.UserName,_Tbl_User_Info.Password,_Tbl_User_Info.RoleID,_Tbl_User_Info.NickName);
	}
	else
	{
		sprintf(strJson,"{\"jsn\":[]}");
	}
	printf("Content-Type:text/html;charset=UTF-8\n\n");
	printf("%s",strJson);

}

