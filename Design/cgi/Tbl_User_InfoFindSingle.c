#include <stdio.h>
#include "cgic.h"
#include "../SQLite3/Tbl_User_InfoDAL.h"

int cgiMain(){
	char sCon[128];
	cgiFormString("sCon",sCon,128);
	Tbl_User_Info _Tbl_User_Info=Tbl_User_InfoFindSingle(sCon);
	char strJson[128];
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