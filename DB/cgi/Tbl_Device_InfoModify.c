// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Device_InfoModify.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================

#include <stdio.h>
#include "cgic.h"
#include "../SQLite3/Tbl_Device_InfoDAL.h"

int cgiMain(){
    Tbl_Device_Info _Tbl_Device_Info;
    char DeviceID[128];
	cgiFormString("DeviceID",DeviceID,128);
    _Tbl_Device_Info.DeviceID=atoi(DeviceID);
    char StorageID[128];
	cgiFormString("StorageID",StorageID,128);
    _Tbl_Device_Info.StorageID=atoi(StorageID);
    char DeviceName[128];
	cgiFormString("DeviceName",DeviceName,128);
    strcpy(_Tbl_Device_Info.DeviceName,DeviceName);
    char Identification[128];
	cgiFormString("Identification",Identification,128);
    strcpy(_Tbl_Device_Info.Identification,Identification);
    char IsOnLine[128];
	cgiFormString("IsOnLine",IsOnLine,128);
    _Tbl_Device_Info.IsOnLine=atoi(IsOnLine);
    char IsAlarm[128];
	cgiFormString("IsAlarm",IsAlarm,128);
    _Tbl_Device_Info.IsAlarm=atoi(IsAlarm);
	
	char strJson[128];
	if (Tbl_Device_InfoModify(_Tbl_Device_Info))
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

