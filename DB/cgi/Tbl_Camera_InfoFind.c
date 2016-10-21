// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Camera_InfoFind.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#include <stdio.h>
#include "cgic.h"
#include "../SQLite3/Tbl_Camera_InfoDAL.h"

int cgiMain(){
   char sCon[128];
	cgiFormString("sCon",sCon,128);
	SqlLinkQueue list=init_linkqueue();
	int count=Tbl_Camera_InfoFind(list,sCon);
	char strJson[1024]="";
	if (count>0)
	{
		strcat(strJson,"{\"jsn\":[");
		INode p=list->front;
		while (p!=list->rear) {
			char str[128];
			p=p->next;
			Tbl_Camera_Info _Tbl_Camera_Info=p->data->_Tbl_Camera_Info;
			sprintf(str,"{\"CameraID\":\"%d\",\"StorageID\":\"%d\",\"CameraPath\":\"%s\",\"CameraDate\":\"%s\"},",_Tbl_Camera_Info.CameraID,_Tbl_Camera_Info.StorageID,_Tbl_Camera_Info.CameraPath,_Tbl_Camera_Info.CameraDate);
			strcat(strJson,str);
		}
		strJson[strlen(strJson)-1]='\0';
		strcat(strJson,"]}");
	}
	else
	{
		sprintf(strJson,"{\"jsn\":[]}");
	}
	free_linkqueue(list);
	printf("Content-Type:text/html;charset=UTF-8\n\n");
	printf("%s",strJson);

}

