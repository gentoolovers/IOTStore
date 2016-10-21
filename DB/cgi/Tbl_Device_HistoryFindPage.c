// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Device_HistoryFindPage.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#include <stdio.h>
#include "cgic.h"
#include "../SQLite3/Tbl_Device_HistoryDAL.h"

int cgiMain(){
    char sCon[128];
	char sSort[128];
	char iPageSize[128];
	char iCurrentPageIndex[128];
	cgiFormString("sCon",sCon,128);
	cgiFormString("sSort",sSort,128);
	cgiFormString("iPageSize",iPageSize,128);
	cgiFormString("iCurrentPageIndex",iCurrentPageIndex,128);
	SqlLinkQueue list=init_linkqueue();
	int count=Tbl_Device_HistoryFindPage(list,sCon,sSort,atoi(iPageSize),atoi(iCurrentPageIndex));
	char strJson[1024]="";
	char str[128];
	if (count>0)
	{
		strcat(strJson,"{\"jsn\":[");
		INode p=list->front;
		while (p!=list->rear) {
			char str[128];
			p=p->next;
			Tbl_Device_History _Tbl_Device_History=p->data->_Tbl_Device_History;
			sprintf(str,"{\"HistoryID\":\"%d\",\"DeviceID\":\"%d\",\"HistoryDate\":\"%s\",\"Temperature\":\"%f\",\"Humidity\":\"%f\",\"Luminosity\":\"%f\",\"Electricity\":\"%d\",\"IsAlarm\":\"%d\"},",_Tbl_Device_History.HistoryID,_Tbl_Device_History.DeviceID,_Tbl_Device_History.HistoryDate,_Tbl_Device_History.Temperature,_Tbl_Device_History.Humidity,_Tbl_Device_History.Luminosity,_Tbl_Device_History.Electricity,_Tbl_Device_History.IsAlarm);
			strcat(strJson,str);
		}
		strJson[strlen(strJson)-1]='\0';
		sprintf(str,"],\"iTotalPageCount\":%d}",Tbl_Device_HistoryGetTotalPageCount(sCon,atoi(iPageSize)));
		strcat(strJson,str);
	}
	else
	{
		sprintf(strJson,"{\"jsn\":[],\"iTotalPageCount\":0}");
	}
	free_linkqueue(list);
	printf("Content-Type:text/html;charset=UTF-8\n\n");
	printf("%s",strJson);

}

