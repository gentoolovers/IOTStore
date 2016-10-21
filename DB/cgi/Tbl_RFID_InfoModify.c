// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_RFID_InfoModify.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================

#include <stdio.h>
#include "cgic.h"
#include "../SQLite3/Tbl_RFID_InfoDAL.h"

int cgiMain(){
    Tbl_RFID_Info _Tbl_RFID_Info;
    char RFID_ID[128];
	cgiFormString("RFID_ID",RFID_ID,128);
    _Tbl_RFID_Info.RFID_ID=atoi(RFID_ID);
    char ArticleID[128];
	cgiFormString("ArticleID",ArticleID,128);
    _Tbl_RFID_Info.ArticleID=atoi(ArticleID);
    char RFID[128];
	cgiFormString("RFID",RFID,128);
    strcpy(_Tbl_RFID_Info.RFID,RFID);
	
	char strJson[128];
	if (Tbl_RFID_InfoModify(_Tbl_RFID_Info))
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

