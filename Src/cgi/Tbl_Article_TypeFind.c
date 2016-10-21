// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Article_TypeFind.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-18
// 负责人：张家铭
// ===================================================================
#include <stdio.h>
#include "../../Res/cgic.h"
#include "../../Res/SQLite3/Tbl_Article_TypeDAL.h"

int cgiMain(){
   char sCon[128];
	cgiFormString("sCon",sCon,128);
	SqlLinkQueue list=init_linkqueue();
	int count=Tbl_Article_TypeFind(list,sCon);
	char strJson[1024]="";
	if (count>0)
	{
		strcat(strJson,"{\"jsn\":[");
		INode p=list->front;
		while (p!=list->rear) {
			char str[128];
			p=p->next;
			Tbl_Article_Type _Tbl_Article_Type=p->data->_Tbl_Article_Type;
			sprintf(str,"{\"TypeID\":\"%d\",\"TypeName\":\"%s\"},",_Tbl_Article_Type.TypeID,_Tbl_Article_Type.TypeName);
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

