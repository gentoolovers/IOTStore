// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Device_ControlAdd.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-18
// 负责人：张家铭
// ===================================================================

#include <stdio.h>
#include "../../Res/cgic.h"
#include "../../Res/SQLite3/Tbl_Device_ControlDAL.h"

int cgiMain(){
    Tbl_Device_Control _Tbl_Device_Control;
    char DeviceID[128];
	cgiFormString("DeviceID",DeviceID,128);
    _Tbl_Device_Control.DeviceID=atoi(DeviceID);
    char RFIDSet[128];
	cgiFormString("RFIDSet",RFIDSet,128);
    _Tbl_Device_Control.RFIDSet=atoi(RFIDSet);
    char AlarmSet[128];
	cgiFormString("AlarmSet",AlarmSet,128);
    _Tbl_Device_Control.AlarmSet=atoi(AlarmSet);
    char LedSet[128];
	cgiFormString("LedSet",LedSet,128);
    _Tbl_Device_Control.LedSet=atoi(LedSet);
    char BeepSet[128];
	cgiFormString("BeepSet",BeepSet,128);
    _Tbl_Device_Control.BeepSet=atoi(BeepSet);
    char FanSet[128];
	cgiFormString("FanSet",FanSet,128);
    _Tbl_Device_Control.FanSet=atoi(FanSet);
    char SegSet[128];
	cgiFormString("SegSet",SegSet,128);
    _Tbl_Device_Control.SegSet=atoi(SegSet);
    char IsSet[128];
	cgiFormString("IsSet",IsSet,128);
    _Tbl_Device_Control.IsSet=atoi(IsSet);
	
	char strJson[128];
	if (Tbl_Device_ControlAdd(_Tbl_Device_Control))
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

