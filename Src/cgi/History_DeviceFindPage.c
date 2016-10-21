// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Article_InfoFind.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-18
// 负责人：张家铭
// ===================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../Res/cgic.h"
#include "../../Res/SQLite3/sqlite3.h"
#include "../../Res/SQLite3/Tbl_Device_InfoDAL.h"

int cgiMain(){
	char sCon[128];
	char sSort[128];
	char iPageSize[128];
	char iCurrentPageIndex[128];
	cgiFormString("sCon",sCon,128);
	cgiFormString("sSort",sSort,128);
	cgiFormString("iPageSize",iPageSize,128);
	cgiFormString("iCurrentPageIndex",iCurrentPageIndex,128);
	int iTotalPageCount=0;
	sqlite3 *DB;
    int ret=sqlite3_open("QMSSLSJ.db", &DB);
    if (ret!=SQLITE_OK) {
        
    }
	char sql[2048];
    sprintf(sql,"select DeviceName,Temperature,Humidity,Luminosity,Electricity,IsOnLine,IsAlarm from (select DeviceName,Identification,ifnull(Temperature,0) Temperature,ifnull(Humidity,0) Humidity,ifnull(Luminosity,0) Luminosity,ifnull(Electricity,0) Electricity,t1.IsOnLine,t1.IsAlarm,ifnull(MAX(HistoryDate),'1900-01-01') HistoryDate from Tbl_Device_Info t1 left join Tbl_Device_History t2 on t1.DeviceID=t2.DeviceID GROUP by t2.DeviceID order BY t1.DeviceID) where 1=1 %s %s LIMIT %d OFFSET %d",sCon,sSort,atoi(iPageSize),atoi(iPageSize)*(atoi(iCurrentPageIndex)-1));
    int pnRow,pnColum;
    char **pazResult;
	char *pzErrmsg;
    ret=sqlite3_get_table(DB, sql, &pazResult, &pnRow, &pnColum, &pzErrmsg);
    if (ret!=SQLITE_OK) {

    }
    sqlite3_close(DB);

	char strJson[4096]="";
	if(pnRow!=0){
	strcat(strJson,"{\"jsn\":[");
	int i,s;
	for (i = 0; i < pnRow; i++)
	{
		char str[2048]="";
		strcat(str,"{");
		for (s = 0; s < pnColum; s++)
		{
			char stri[1028];
			sprintf(stri,"\"%s\":\"%s\",",pazResult[s],pazResult[pnColum+i*pnColum+s]);
			strcat(str,stri);
		}
		str[strlen(str)-1]='\0';
		strcat(str,"},");
		strcat(strJson,str);
	}
	strJson[strlen(strJson)-1]='\0';
	char buf[128]="";
	sprintf(buf,"],\"iTotalPageCount\":%d}",Tbl_Device_InfoGetTotalPageCount(sCon,atoi(iPageSize)));
	strcat(strJson,buf);
	}
	else
	{
		sprintf(strJson,"{\"jsn\":[]}");
	}
	sqlite3_free_table(pazResult);
	printf("Content-Type:text/html;charset=UTF-8\n\n");
	printf("%s",strJson);

}