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
#include <string.h>
#include "../../Res/cgic.h"
#include "../../Res/SQLite3/sqlite3.h"

int cgiMain(){
	char sCon[128];
	cgiFormString("sCon",sCon,128);
	sqlite3 *DB;
    int ret=sqlite3_open("QMSSLSJ.db", &DB);
    if (ret!=SQLITE_OK) {
        
    }
	char sql[1048];
    sprintf(sql,"SELECT t6.storageName,ifnull(t8.Temperature,0) Temperature,ifnull(t8.humidity,0) Humidity,ifnull(t8.luminosity,0) Luminosity,t7.typename,t7.articlenum,t6.devicenum,t6.isalarm from (select t2.StorageName,t1.DeviceID,COUNT(t1.DeviceID) DeviceNUM,MAX(t1.IsAlarm) IsAlarm from Tbl_Device_Info t1 left join Tbl_Storage_Info t2 on t1.StorageID=t2.storageID GROUP by t1.StorageID) t6 left join (select t5.StorageName,COUNT(ArticleID) ArticleNUM,t4.TypeName from Tbl_Article_Info t3 left join Tbl_Article_Type t4 on t3.TypeID=t4.TypeID left JOIN Tbl_Storage_Info t5 on t3.StorageID=t5.StorageID where t3.StorageID<>0 GROUP by t3.StorageID) t7 on t6.storageName=t7.storageName left join (SELECT DeviceID,Temperature,Humidity,Luminosity,max(HistoryDate) HistoryDate from Tbl_Device_History where Temperature not null GROUP by DeviceID) t8 on t6.deviceID=t8.deviceid where 1=1 %s",sCon);
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
		char str[256]="";
		strcat(str,"{");
		for (s = 0; s < pnColum; s++)
		{
			char stri[128];
			sprintf(stri,"\"%s\":\"%s\",",pazResult[s],pazResult[pnColum+i*pnColum+s]);
			strcat(str,stri);
		}
		str[strlen(str)-1]='\0';
		strcat(str,"},");
		strcat(strJson,str);
	}
	strJson[strlen(strJson)-1]='\0';
	strcat(strJson,"]}");
	}
	else
	{
		sprintf(strJson,"{\"jsn\":[]}");
	}

	printf("Content-Type:text/html;charset=UTF-8\n\n");
	printf("%s",strJson);

}