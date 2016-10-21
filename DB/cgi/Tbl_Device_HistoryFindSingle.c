// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Device_HistoryFindSingle.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#include <stdio.h>
#include "cgic.h"
#include "../SQLite3/Tbl_Device_HistoryDAL.h"

int cgiMain(){
    char sCon[128];
	cgiFormString("sCon",sCon,128);
	Tbl_Device_History _Tbl_Device_History=Tbl_Device_HistoryFindSingle(sCon);
	char strJson[1024];
	if (_Tbl_Device_History.HistoryID!=0)
	{
		sprintf(strJson,"{\"jsn\":[{\"HistoryID\":\"%d\",\"DeviceID\":\"%d\",\"HistoryDate\":\"%s\",\"Temperature\":\"%.2f\",\"Humidity\":\"%.2f\",\"Luminosity\":\"%.2f\",\"Electricity\":\"%d\",\"IsAlarm\":\"%d\"}]}",_Tbl_Device_History.HistoryID,_Tbl_Device_History.DeviceID,_Tbl_Device_History.HistoryDate,_Tbl_Device_History.Temperature,_Tbl_Device_History.Humidity,_Tbl_Device_History.Luminosity,_Tbl_Device_History.Electricity,_Tbl_Device_History.IsAlarm);
	}
	else
	{
		sprintf(strJson,"{\"jsn\":[]}");
	}
	printf("Content-Type:text/html;charset=UTF-8\n\n");
	printf("%s",strJson);

}

