// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Camera_InfoAdd.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================

#include <stdio.h>
#include "cgic.h"
#include "../SQLite3/Tbl_Camera_InfoDAL.h"

int cgiMain(){
    Tbl_Camera_Info _Tbl_Camera_Info;
    char CameraID[128];
	cgiFormString("CameraID",CameraID,128);
    _Tbl_Camera_Info.CameraID=atoi(CameraID);
    char StorageID[128];
	cgiFormString("StorageID",StorageID,128);
    _Tbl_Camera_Info.StorageID=atoi(StorageID);
    char CameraPath[128];
	cgiFormString("CameraPath",CameraPath,128);
    strcpy(_Tbl_Camera_Info.CameraPath,CameraPath);
    char CameraDate[128];
	cgiFormString("CameraDate",CameraDate,128);
    strcpy(_Tbl_Camera_Info.CameraDate,CameraDate);
	
	char strJson[128];
	if (Tbl_Camera_InfoAdd(_Tbl_Camera_Info))
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

