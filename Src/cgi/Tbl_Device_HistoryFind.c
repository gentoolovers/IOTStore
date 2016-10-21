// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Device_HistoryFind.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-18
// 负责人：张家铭
// ===================================================================
#include <stdio.h>
#include "../../Res/cgic.h"
#include "../../Res/SQLite3/Tbl_Device_HistoryDAL.h"

int cgiMain(){
   char sCon[128];
	cgiFormString("sCon",sCon,128);
	SqlLinkQueue list=init_linkqueue();
	int count=Tbl_Device_HistoryFind(list,sCon);
	char strJson[2024]="";
	if (count>0)
	{
		strcat(strJson,"{\"jsn\":[");
		INode p=list->front;
		while (p!=list->rear) {
			char str[128];
			p=p->next;
			Tbl_Device_History _Tbl_Device_History=p->data->_Tbl_Device_History;
			sprintf(str,"{\"HistoryID\":\"%d\",\"DeviceID\":\"%d\",\"HistoryDate\":\"%s\",\"Temperature\":\"%.2f\",\"Humidity\":\"%.2f\",\"Luminosity\":\"%.2f\",\"Electricity\":\"%d\",\"IsAlarm\":\"%d\"},",_Tbl_Device_History.HistoryID,_Tbl_Device_History.DeviceID,_Tbl_Device_History.HistoryDate,_Tbl_Device_History.Temperature,_Tbl_Device_History.Humidity,_Tbl_Device_History.Luminosity,_Tbl_Device_History.Electricity,_Tbl_Device_History.IsAlarm);
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

