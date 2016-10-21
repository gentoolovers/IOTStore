// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Storage_InfoFindSingle.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#include <stdio.h>
#include "cgic.h"
#include "../SQLite3/Tbl_Storage_InfoDAL.h"

int cgiMain(){
    char sCon[128];
	cgiFormString("sCon",sCon,128);
	Tbl_Storage_Info _Tbl_Storage_Info=Tbl_Storage_InfoFindSingle(sCon);
	char strJson[1024];
	if (_Tbl_Storage_Info.StorageID!=0)
	{
		sprintf(strJson,"{\"jsn\":[{\"StorageID\":\"%d\",\"StorageName\":\"%s\",\"StorageAddress\":\"%s\"}]}",_Tbl_Storage_Info.StorageID,_Tbl_Storage_Info.StorageName,_Tbl_Storage_Info.StorageAddress);
	}
	else
	{
		sprintf(strJson,"{\"jsn\":[]}");
	}
	printf("Content-Type:text/html;charset=UTF-8\n\n");
	printf("%s",strJson);

}

