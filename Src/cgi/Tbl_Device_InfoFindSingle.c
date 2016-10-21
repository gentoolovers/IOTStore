// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Device_InfoFindSingle.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-18
// 负责人：张家铭
// ===================================================================
#include <stdio.h>
#include "../../Res/cgic.h"
#include "../../Res/SQLite3/Tbl_Device_InfoDAL.h"

int cgiMain(){
    char sCon[128];
	cgiFormString("sCon",sCon,128);
	Tbl_Device_Info _Tbl_Device_Info=Tbl_Device_InfoFindSingle(sCon);
	char strJson[1024];
	if (_Tbl_Device_Info.DeviceID!=0)
	{
		sprintf(strJson,"{\"jsn\":[{\"DeviceID\":\"%d\",\"StorageID\":\"%d\",\"DeviceName\":\"%s\",\"Identification\":\"%s\",\"IsOnLine\":\"%d\",\"IsAlarm\":\"%d\"}]}",_Tbl_Device_Info.DeviceID,_Tbl_Device_Info.StorageID,_Tbl_Device_Info.DeviceName,_Tbl_Device_Info.Identification,_Tbl_Device_Info.IsOnLine,_Tbl_Device_Info.IsAlarm);
	}
	else
	{
		sprintf(strJson,"{\"jsn\":[]}");
	}
	printf("Content-Type:text/html;charset=UTF-8\n\n");
	printf("%s",strJson);

}

