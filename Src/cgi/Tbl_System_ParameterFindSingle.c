// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_System_ParameterFindSingle.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-18
// 负责人：张家铭
// ===================================================================
#include <stdio.h>
#include "../../Res/cgic.h"
#include "../../Res/SQLite3/Tbl_System_ParameterDAL.h"

int cgiMain(){
    char sCon[128];
	cgiFormString("sCon",sCon,128);
	Tbl_System_Parameter _Tbl_System_Parameter=Tbl_System_ParameterFindSingle(sCon);
	char strJson[1024];
	if (_Tbl_System_Parameter.key!=0)
	{
		sprintf(strJson,"{\"jsn\":[{\"key\":\"%s\",\"value\":\"%s\"}]}",_Tbl_System_Parameter.key,_Tbl_System_Parameter.value);
	}
	else
	{
		sprintf(strJson,"{\"jsn\":[]}");
	}
	printf("Content-Type:text/html;charset=UTF-8\n\n");
	printf("%s",strJson);

}

