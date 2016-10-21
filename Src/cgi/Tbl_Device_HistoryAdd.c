// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Device_HistoryAdd.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-18
// 负责人：张家铭
// ===================================================================

#include <stdio.h>
#include "../../Res/cgic.h"
#include "../../Res/SQLite3/Tbl_Device_HistoryDAL.h"

int cgiMain(){
    Tbl_Device_History _Tbl_Device_History;
    char HistoryID[128];
	cgiFormString("HistoryID",HistoryID,128);
    _Tbl_Device_History.HistoryID=atoi(HistoryID);
    char DeviceID[128];
	cgiFormString("DeviceID",DeviceID,128);
    _Tbl_Device_History.DeviceID=atoi(DeviceID);
    char HistoryDate[128];
	cgiFormString("HistoryDate",HistoryDate,128);
    strcpy(_Tbl_Device_History.HistoryDate,HistoryDate);
    char Temperature[128];
	cgiFormString("Temperature",Temperature,128);
    _Tbl_Device_History.Temperature=atof(Temperature);
    char Humidity[128];
	cgiFormString("Humidity",Humidity,128);
    _Tbl_Device_History.Humidity=atof(Humidity);
    char Luminosity[128];
	cgiFormString("Luminosity",Luminosity,128);
    _Tbl_Device_History.Luminosity=atof(Luminosity);
    char Electricity[128];
	cgiFormString("Electricity",Electricity,128);
    _Tbl_Device_History.Electricity=atoi(Electricity);
    char IsAlarm[128];
	cgiFormString("IsAlarm",IsAlarm,128);
    _Tbl_Device_History.IsAlarm=atoi(IsAlarm);
	
	char strJson[128];
	if (Tbl_Device_HistoryAdd(_Tbl_Device_History))
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

