// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_RFID_HistoryAdd.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================

#include <stdio.h>
#include "cgic.h"
#include "../SQLite3/Tbl_RFID_HistoryDAL.h"

int cgiMain(){
    Tbl_RFID_History _Tbl_RFID_History;
    char RFID_HistoryID[128];
	cgiFormString("RFID_HistoryID",RFID_HistoryID,128);
    _Tbl_RFID_History.RFID_HistoryID=atoi(RFID_HistoryID);
    char RFID_ID[128];
	cgiFormString("RFID_ID",RFID_ID,128);
    _Tbl_RFID_History.RFID_ID=atoi(RFID_ID);
    char Date[128];
	cgiFormString("Date",Date,128);
    strcpy(_Tbl_RFID_History.Date,Date);
	
	char strJson[128];
	if (Tbl_RFID_HistoryAdd(_Tbl_RFID_History))
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

