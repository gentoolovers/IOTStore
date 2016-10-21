// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Device_ControlFind.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#include <stdio.h>
#include "cgic.h"
#include "../SQLite3/Tbl_Device_ControlDAL.h"

int cgiMain(){
   char sCon[128];
	cgiFormString("sCon",sCon,128);
	SqlLinkQueue list=init_linkqueue();
	int count=Tbl_Device_ControlFind(list,sCon);
	char strJson[1024]="";
	if (count>0)
	{
		strcat(strJson,"{\"jsn\":[");
		INode p=list->front;
		while (p!=list->rear) {
			char str[128];
			p=p->next;
			Tbl_Device_Control _Tbl_Device_Control=p->data->_Tbl_Device_Control;
			sprintf(str,"{\"DeviceID\":\"%d\",\"RFIDSet\":\"%d\",\"AlarmSet\":\"%d\",\"LedSet\":\"%d\",\"BeepSet\":\"%d\",\"FanSet\":\"%d\",\"SegSet\":\"%d\",\"IsSet\":\"%d\"},",_Tbl_Device_Control.DeviceID,_Tbl_Device_Control.RFIDSet,_Tbl_Device_Control.AlarmSet,_Tbl_Device_Control.LedSet,_Tbl_Device_Control.BeepSet,_Tbl_Device_Control.FanSet,_Tbl_Device_Control.SegSet,_Tbl_Device_Control.IsSet);
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

