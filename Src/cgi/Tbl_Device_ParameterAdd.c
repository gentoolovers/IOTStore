// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Device_ParameterAdd.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-18
// 负责人：张家铭
// ===================================================================

#include <stdio.h>
#include "../../Res/cgic.h"
#include "../../Res/SQLite3/Tbl_Device_ParameterDAL.h"

int cgiMain(){
    Tbl_Device_Parameter _Tbl_Device_Parameter;
    char DeviceID[128];
	cgiFormString("DeviceID",DeviceID,128);
    _Tbl_Device_Parameter.DeviceID=atoi(DeviceID);
    char MinTem[128];
	cgiFormString("MinTem",MinTem,128);
    _Tbl_Device_Parameter.MinTem=atof(MinTem);
    char MaxTem[128];
	cgiFormString("MaxTem",MaxTem,128);
    _Tbl_Device_Parameter.MaxTem=atof(MaxTem);
    char MinHum[128];
	cgiFormString("MinHum",MinHum,128);
    _Tbl_Device_Parameter.MinHum=atof(MinHum);
    char MaxHum[128];
	cgiFormString("MaxHum",MaxHum,128);
    _Tbl_Device_Parameter.MaxHum=atof(MaxHum);
    char MinLit[128];
	cgiFormString("MinLit",MinLit,128);
    _Tbl_Device_Parameter.MinLit=atof(MinLit);
    char MaxLit[128];
	cgiFormString("MaxLit",MaxLit,128);
    _Tbl_Device_Parameter.MaxLit=atof(MaxLit);
    char TimeSet[128];
	cgiFormString("TimeSet",TimeSet,128);
    _Tbl_Device_Parameter.TimeSet=atoi(TimeSet);
    char IsSet[128];
	cgiFormString("IsSet",IsSet,128);
    _Tbl_Device_Parameter.IsSet=atoi(IsSet);
	
	char strJson[128];
	if (Tbl_Device_ParameterAdd(_Tbl_Device_Parameter))
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

