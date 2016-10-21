// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Device_Info.c
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#include <math.h>
#include "Tbl_Device_InfoDAL.h"

//填充结构体
Tbl_Device_Info Populate_Tbl_Device_Info(Tbl_Device_Info _Tbl_Device_Info){
    _Tbl_Device_Info.DeviceID=_Tbl_Device_Info.DeviceID;
    _Tbl_Device_Info.StorageID=_Tbl_Device_Info.StorageID;
    if(strlen(_Tbl_Device_Info.DeviceName)==0)strcpy(_Tbl_Device_Info.DeviceName, " ");
    if(strlen(_Tbl_Device_Info.Identification)==0)strcpy(_Tbl_Device_Info.Identification, " ");
    _Tbl_Device_Info.IsOnLine=_Tbl_Device_Info.IsOnLine;
    _Tbl_Device_Info.IsAlarm=_Tbl_Device_Info.IsAlarm;
    
    return _Tbl_Device_Info;
}


//增加
bool Tbl_Device_InfoAdd(Tbl_Device_Info _Tbl_Device_Info){
    _Tbl_Device_Info=Populate_Tbl_Device_Info(_Tbl_Device_Info);
    char sql[256];
    sprintf(sql,"insert into Tbl_Device_Info (StorageID,DeviceName,Identification,IsOnLine,IsAlarm) values(%d,'%s','%s',%d,%d);",_Tbl_Device_Info.StorageID,_Tbl_Device_Info.DeviceName,_Tbl_Device_Info.Identification,_Tbl_Device_Info.IsOnLine,_Tbl_Device_Info.IsAlarm);
	return exec_sql(sql)?true:false;
}
//删除
bool Tbl_Device_InfoDelete(char *Con){
    char sql[256];
    sprintf(sql,"delete from Tbl_Device_Info where 1=1 %s",Con);
    return exec_sql(sql)?true:false;
}
//修改
bool Tbl_Device_InfoModify(Tbl_Device_Info _Tbl_Device_Info){
    _Tbl_Device_Info=Populate_Tbl_Device_Info(_Tbl_Device_Info);
    char sql[256];
    sprintf(sql,"update Tbl_Device_Info set StorageID=%d,DeviceName='%s',Identification='%s',IsOnLine=%d,IsAlarm=%d where DeviceID=%d",_Tbl_Device_Info.StorageID,_Tbl_Device_Info.DeviceName,_Tbl_Device_Info.Identification,_Tbl_Device_Info.IsOnLine,_Tbl_Device_Info.IsAlarm,_Tbl_Device_Info.DeviceID);
    return exec_sql(sql)?true:false;
}


//查询
int Tbl_Device_InfoFind(SqlLinkQueue list,char *Con){
    char sql[256];
    sprintf(sql,"select DeviceID,StorageID,DeviceName,Identification,IsOnLine,IsAlarm from Tbl_Device_Info where 1=1 %s",Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    if(pnRow==0)return 0;
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        data->_Tbl_Device_Info.DeviceID=atoi(pazResult[pnColum+i*pnColum+0]);
        data->_Tbl_Device_Info.StorageID=atoi(pazResult[pnColum+i*pnColum+1]);
        strcpy(data->_Tbl_Device_Info.DeviceName, pazResult[pnColum+i*pnColum+2]);
        strcpy(data->_Tbl_Device_Info.Identification, pazResult[pnColum+i*pnColum+3]);
        data->_Tbl_Device_Info.IsOnLine=atoi(pazResult[pnColum+i*pnColum+4]);
        data->_Tbl_Device_Info.IsAlarm=atoi(pazResult[pnColum+i*pnColum+5]);
        data->_Tbl_Device_Info=Populate_Tbl_Device_Info(data->_Tbl_Device_Info);
        if(!in_linkqueue(list,data))
        {
            perror("fail to in_linkqueue!");
            free_linkqueue(list);
            break;
        }
    }
    sqlite3_free_table(pazResult);
    return pnRow;
}


//查询单条
Tbl_Device_Info Tbl_Device_InfoFindSingle(char *Con){
    char sql[256];
    sprintf(sql,"select DeviceID,StorageID,DeviceName,Identification,IsOnLine,IsAlarm from Tbl_Device_Info where 1=1 %s",Con);
    char **pazResult;
    int pnRow,pnColum;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    //只返回第一条
    Tbl_Device_Info _Tbl_Device_Info;
    _Tbl_Device_Info.DeviceID=0;
    _Tbl_Device_Info.StorageID=0;
    strcpy(_Tbl_Device_Info.DeviceName, " ");
    strcpy(_Tbl_Device_Info.Identification, " ");
    _Tbl_Device_Info.IsOnLine=0;
    _Tbl_Device_Info.IsAlarm=0;
    if (pnRow<=0) {
        return _Tbl_Device_Info;
    }
    _Tbl_Device_Info.DeviceID=atoi(pazResult[pnColum+0]);
    _Tbl_Device_Info.StorageID=atoi(pazResult[pnColum+1]);
    strcpy(_Tbl_Device_Info.DeviceName, pazResult[pnColum+2]);
    strcpy(_Tbl_Device_Info.Identification, pazResult[pnColum+3]);
    _Tbl_Device_Info.IsOnLine=atoi(pazResult[pnColum+4]);
    _Tbl_Device_Info.IsAlarm=atoi(pazResult[pnColum+5]);
    sqlite3_free_table(pazResult);
    return _Tbl_Device_Info;
}
/*
 * 分页查找
 * Con 查找条件
 * Sort 排序条件
 * PageSize 每页多少条
 * CurrentPageIndex 第几页
 */
int Tbl_Device_InfoFindPage(SqlLinkQueue list,char *Con,char *Sort,int PageSize,int CurrentPageIndex){
    char sql[256];
    sprintf(sql,"select DeviceID,StorageID,DeviceName,Identification,IsOnLine,IsAlarm from Tbl_Device_Info where 1=1 %s %s LIMIT %d OFFSET %d",Con,Sort,PageSize,PageSize*(CurrentPageIndex-1));
	FILE *fp=fopen("log.txt","w+");
	fwrite(sql,strlen(sql),1,fp);
	fclose(fp);
	int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    if(pnRow==0)return 0;
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        data->_Tbl_Device_Info.DeviceID=atoi(pazResult[pnColum+i*pnColum+0]);
        data->_Tbl_Device_Info.StorageID=atoi(pazResult[pnColum+i*pnColum+1]);
        strcpy(data->_Tbl_Device_Info.DeviceName, pazResult[pnColum+i*pnColum+2]);
        strcpy(data->_Tbl_Device_Info.Identification, pazResult[pnColum+i*pnColum+3]);
        data->_Tbl_Device_Info.IsOnLine=atoi(pazResult[pnColum+i*pnColum+4]);
        data->_Tbl_Device_Info.IsAlarm=atoi(pazResult[pnColum+i*pnColum+5]);
        data->_Tbl_Device_Info=Populate_Tbl_Device_Info(data->_Tbl_Device_Info);
        if(!in_linkqueue(list,data))
        {
            perror("fail to in_linkqueue!");
            free_linkqueue(list);
            break;
        }
    }
    sqlite3_free_table(pazResult);
    return pnRow;
}
//获取总页数
int Tbl_Device_InfoGetTotalPageCount(char *Con,int PageSize){
    char sql[256];
    sprintf(sql,"SELECT (count(*)*1.0/%d) from Tbl_Device_Info where 1=1 %s",PageSize,Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    sqlite3_free_table(pazResult);
    return (int)ceil(atof(pazResult[pnColum]));
}

