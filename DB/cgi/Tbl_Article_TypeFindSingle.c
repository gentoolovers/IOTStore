// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Article_TypeFindSingle.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#include <stdio.h>
#include "cgic.h"
#include "../SQLite3/Tbl_Article_TypeDAL.h"

int cgiMain(){
    char sCon[128];
	cgiFormString("sCon",sCon,128);
	Tbl_Article_Type _Tbl_Article_Type=Tbl_Article_TypeFindSingle(sCon);
	char strJson[1024];
	if (_Tbl_Article_Type.TypeID!=0)
	{
		sprintf(strJson,"{\"jsn\":[{\"TypeID\":\"%d\",\"TypeName\":\"%s\"}]}",_Tbl_Article_Type.TypeID,_Tbl_Article_Type.TypeName);
	}
	else
	{
		sprintf(strJson,"{\"jsn\":[]}");
	}
	printf("Content-Type:text/html;charset=UTF-8\n\n");
	printf("%s",strJson);

}

