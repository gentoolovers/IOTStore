// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_RFID_InfoFindSingle.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#include <stdio.h>
#include "cgic.h"
#include "../SQLite3/Tbl_RFID_InfoDAL.h"

int cgiMain(){
    char sCon[128];
	cgiFormString("sCon",sCon,128);
	Tbl_RFID_Info _Tbl_RFID_Info=Tbl_RFID_InfoFindSingle(sCon);
	char strJson[1024];
	if (_Tbl_RFID_Info.RFID_ID!=0)
	{
		sprintf(strJson,"{\"jsn\":[{\"RFID_ID\":\"%d\",\"ArticleID\":\"%d\",\"RFID\":\"%s\"}]}",_Tbl_RFID_Info.RFID_ID,_Tbl_RFID_Info.ArticleID,_Tbl_RFID_Info.RFID);
	}
	else
	{
		sprintf(strJson,"{\"jsn\":[]}");
	}
	printf("Content-Type:text/html;charset=UTF-8\n\n");
	printf("%s",strJson);

}

