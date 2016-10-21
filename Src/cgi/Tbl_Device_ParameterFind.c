// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Device_ParameterFind.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-18
// 负责人：张家铭
// ===================================================================
#include <stdio.h>
#include "../../Res/cgic.h"
#include "../../Res/SQLite3/Tbl_Device_ParameterDAL.h"

int cgiMain(){
   char sCon[128];
	cgiFormString("sCon",sCon,128);
	SqlLinkQueue list=init_linkqueue();
	int count=Tbl_Device_ParameterFind(list,sCon);
	char strJson[1024]="";
	if (count>0)
	{
		strcat(strJson,"{\"jsn\":[");
		INode p=list->front;
		while (p!=list->rear) {
			char str[128];
			p=p->next;
			Tbl_Device_Parameter _Tbl_Device_Parameter=p->data->_Tbl_Device_Parameter;
			sprintf(str,"{\"DeviceID\":\"%d\",\"MinTem\":\"%.2f\",\"MaxTem\":\"%.2f\",\"MinHum\":\"%.2f\",\"MaxHum\":\"%.2f\",\"MinLit\":\"%.2f\",\"MaxLit\":\"%.2f\",\"TimeSet\":\"%d\",\"IsSet\":\"%d\"},",_Tbl_Device_Parameter.DeviceID,_Tbl_Device_Parameter.MinTem,_Tbl_Device_Parameter.MaxTem,_Tbl_Device_Parameter.MinHum,_Tbl_Device_Parameter.MaxHum,_Tbl_Device_Parameter.MinLit,_Tbl_Device_Parameter.MaxLit,_Tbl_Device_Parameter.TimeSet,_Tbl_Device_Parameter.IsSet);
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

