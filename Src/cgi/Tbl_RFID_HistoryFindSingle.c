// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_RFID_HistoryFindSingle.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-18
// 负责人：张家铭
// ===================================================================
#include <stdio.h>
#include "../../Res/cgic.h"
#include "../../Res/SQLite3/Tbl_RFID_HistoryDAL.h"

int cgiMain(){
    char sCon[128];
	cgiFormString("sCon",sCon,128);
	Tbl_RFID_History _Tbl_RFID_History=Tbl_RFID_HistoryFindSingle(sCon);
	char strJson[1024];
	if (_Tbl_RFID_History.RFID_HistoryID!=0)
	{
		sprintf(strJson,"{\"jsn\":[{\"RFID_HistoryID\":\"%d\",\"RFID_ID\":\"%d\",\"Date\":\"%s\"}]}",_Tbl_RFID_History.RFID_HistoryID,_Tbl_RFID_History.RFID_ID,_Tbl_RFID_History.Date);
	}
	else
	{
		sprintf(strJson,"{\"jsn\":[]}");
	}
	printf("Content-Type:text/html;charset=UTF-8\n\n");
	printf("%s",strJson);

}

