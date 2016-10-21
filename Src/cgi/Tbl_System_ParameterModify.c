// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_System_ParameterModify.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-18
// 负责人：张家铭
// ===================================================================

#include <stdio.h>
#include "../../Res/cgic.h"
#include "../../Res/SQLite3/Tbl_System_ParameterDAL.h"

int cgiMain(){
    Tbl_System_Parameter _Tbl_System_Parameter;
    char key[128];
	cgiFormString("key",key,128);
    strcpy(_Tbl_System_Parameter.key,key);
    char value[128];
	cgiFormString("value",value,128);
    strcpy(_Tbl_System_Parameter.value,value);
	
	char strJson[128];
	if (Tbl_System_ParameterModify(_Tbl_System_Parameter))
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

