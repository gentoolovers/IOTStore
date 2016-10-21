// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Storage_InfoAdd.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================

#include <stdio.h>
#include "cgic.h"
#include "../SQLite3/Tbl_Storage_InfoDAL.h"

int cgiMain(){
    Tbl_Storage_Info _Tbl_Storage_Info;
    char StorageID[128];
	cgiFormString("StorageID",StorageID,128);
    _Tbl_Storage_Info.StorageID=atoi(StorageID);
    char StorageName[128];
	cgiFormString("StorageName",StorageName,128);
    strcpy(_Tbl_Storage_Info.StorageName,StorageName);
    char StorageAddress[128];
	cgiFormString("StorageAddress",StorageAddress,128);
    strcpy(_Tbl_Storage_Info.StorageAddress,StorageAddress);
	
	char strJson[128];
	if (Tbl_Storage_InfoAdd(_Tbl_Storage_Info))
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

