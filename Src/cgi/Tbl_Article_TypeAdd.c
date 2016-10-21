// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Article_TypeAdd.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-18
// 负责人：张家铭
// ===================================================================

#include <stdio.h>
#include "../../Res/cgic.h"
#include "../../Res/SQLite3/Tbl_Article_TypeDAL.h"

int cgiMain(){
    Tbl_Article_Type _Tbl_Article_Type;
    char TypeID[128];
	cgiFormString("TypeID",TypeID,128);
    _Tbl_Article_Type.TypeID=atoi(TypeID);
    char TypeName[128];
	cgiFormString("TypeName",TypeName,128);
    strcpy(_Tbl_Article_Type.TypeName,TypeName);
	
	char strJson[128];
	if (Tbl_Article_TypeAdd(_Tbl_Article_Type))
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

