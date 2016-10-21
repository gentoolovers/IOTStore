// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Article_InfoFindSingle.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-18
// 负责人：张家铭
// ===================================================================
#include <stdio.h>
#include "../../Res/cgic.h"
#include "../../Res/SQLite3/Tbl_Article_InfoDAL.h"

int cgiMain(){
    char sCon[128];
	cgiFormString("sCon",sCon,128);
	Tbl_Article_Info _Tbl_Article_Info=Tbl_Article_InfoFindSingle(sCon);
	char strJson[1024];
	if (_Tbl_Article_Info.ArticleID!=0)
	{
		sprintf(strJson,"{\"jsn\":[{\"ArticleID\":\"%d\",\"ArticleName\":\"%s\",\"StorageID\":\"%d\",\"TypeID\":\"%d\"}]}",_Tbl_Article_Info.ArticleID,_Tbl_Article_Info.ArticleName,_Tbl_Article_Info.StorageID,_Tbl_Article_Info.TypeID);
	}
	else
	{
		sprintf(strJson,"{\"jsn\":[]}");
	}
	printf("Content-Type:text/html;charset=UTF-8\n\n");
	printf("%s",strJson);

}

