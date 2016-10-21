// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Article_InfoAdd.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-18
// 负责人：张家铭
// ===================================================================

#include <stdio.h>
#include "../../Res/cgic.h"
#include "../../Res/SQLite3/Tbl_Article_InfoDAL.h"

int cgiMain(){
    Tbl_Article_Info _Tbl_Article_Info;
    char ArticleID[128];
	cgiFormString("ArticleID",ArticleID,128);
    _Tbl_Article_Info.ArticleID=atoi(ArticleID);
    char ArticleName[128];
	cgiFormString("ArticleName",ArticleName,128);
    strcpy(_Tbl_Article_Info.ArticleName,ArticleName);
    char StorageID[128];
	cgiFormString("StorageID",StorageID,128);
    _Tbl_Article_Info.StorageID=atoi(StorageID);
    char TypeID[128];
	cgiFormString("TypeID",TypeID,128);
    _Tbl_Article_Info.TypeID=atoi(TypeID);
	
	char strJson[128];
	if (Tbl_Article_InfoAdd(_Tbl_Article_Info))
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

