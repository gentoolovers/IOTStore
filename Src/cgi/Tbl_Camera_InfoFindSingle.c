// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Camera_InfoFindSingle.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-18
// 负责人：张家铭
// ===================================================================
#include <stdio.h>
#include "../../Res/cgic.h"
#include "../../Res/SQLite3/Tbl_Camera_InfoDAL.h"

int cgiMain(){
    char sCon[128];
	cgiFormString("sCon",sCon,128);
	Tbl_Camera_Info _Tbl_Camera_Info=Tbl_Camera_InfoFindSingle(sCon);
	char strJson[2024];
	if (_Tbl_Camera_Info.CameraID!=0)
	{
		sprintf(strJson,"{\"jsn\":[{\"CameraID\":\"%d\",\"StorageID\":\"%d\",\"CameraPath\":\"%s\",\"CameraDate\":\"%s\"}]}",_Tbl_Camera_Info.CameraID,_Tbl_Camera_Info.StorageID,_Tbl_Camera_Info.CameraPath,_Tbl_Camera_Info.CameraDate);
	}
	else
	{
		sprintf(strJson,"{\"jsn\":[]}");
	}
	printf("Content-Type:text/html;charset=UTF-8\n\n");
	printf("%s",strJson);

}

