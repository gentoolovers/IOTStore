// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Device_History.c
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#include <math.h>
#include "Tbl_Device_HistoryDAL.h"

//填充结构体
Tbl_Device_History Populate_Tbl_Device_History(Tbl_Device_History _Tbl_Device_History){
    _Tbl_Device_History.HistoryID=_Tbl_Device_History.HistoryID;
    _Tbl_Device_History.DeviceID=_Tbl_Device_History.DeviceID;
    if(strlen(_Tbl_Device_History.HistoryDate)==0)strcpy(_Tbl_Device_History.HistoryDate, " ");
    _Tbl_Device_History.Temperature=_Tbl_Device_History.Temperature;
    _Tbl_Device_History.Humidity=_Tbl_Device_History.Humidity;
    _Tbl_Device_History.Luminosity=_Tbl_Device_History.Luminosity;
    _Tbl_Device_History.Electricity=_Tbl_Device_History.Electricity;
    _Tbl_Device_History.IsAlarm=_Tbl_Device_History.IsAlarm;
    
    return _Tbl_Device_History;
}


//增加
bool Tbl_Device_HistoryAdd(Tbl_Device_History _Tbl_Device_History){
    _Tbl_Device_History=Populate_Tbl_Device_History(_Tbl_Device_History);
    char sql[256];
    sprintf(sql,"insert into Tbl_Device_History (DeviceID,HistoryDate,Temperature,Humidity,Luminosity,Electricity,IsAlarm) values(%d,'%s',%f,%f,%f,%d,%d)",_Tbl_Device_History.DeviceID,_Tbl_Device_History.HistoryDate,_Tbl_Device_History.Temperature,_Tbl_Device_History.Humidity,_Tbl_Device_History.Luminosity,_Tbl_Device_History.Electricity,_Tbl_Device_History.IsAlarm);
    return exec_sql(sql)?true:false;
}
//删除
bool Tbl_Device_HistoryDelete(char *Con){
    char sql[256];
    sprintf(sql,"delete from Tbl_Device_History where 1=1 %s",Con);
    return exec_sql(sql)?true:false;
}
//修改
bool Tbl_Device_HistoryModify(Tbl_Device_History _Tbl_Device_History){
    _Tbl_Device_History=Populate_Tbl_Device_History(_Tbl_Device_History);
    char sql[256];
    sprintf(sql,"update Tbl_Device_History set DeviceID=%d,HistoryDate='%s',Temperature=%f,Humidity=%f,Luminosity=%f,Electricity=%d,IsAlarm=%d where HistoryID=%d",_Tbl_Device_History.DeviceID,_Tbl_Device_History.HistoryDate,_Tbl_Device_History.Temperature,_Tbl_Device_History.Humidity,_Tbl_Device_History.Luminosity,_Tbl_Device_History.Electricity,_Tbl_Device_History.IsAlarm,_Tbl_Device_History.HistoryID);
    return exec_sql(sql)?true:false;
}


//查询
int Tbl_Device_HistoryFind(SqlLinkQueue list,char *Con){
    char sql[256];
    sprintf(sql,"select HistoryID,DeviceID,HistoryDate,Temperature,Humidity,Luminosity,Electricity,IsAlarm from Tbl_Device_History where 1=1 %s",Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    if(pnRow==0)return 0;
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        data->_Tbl_Device_History.HistoryID=atoi(pazResult[pnColum+i*pnColum+0]);
        data->_Tbl_Device_History.DeviceID=atoi(pazResult[pnColum+i*pnColum+1]);
        strcpy(data->_Tbl_Device_History.HistoryDate, pazResult[pnColum+i*pnColum+2]);
        data->_Tbl_Device_History.Temperature=atof(pazResult[pnColum+i*pnColum+3]);
        data->_Tbl_Device_History.Humidity=atof(pazResult[pnColum+i*pnColum+4]);
        data->_Tbl_Device_History.Luminosity=atof(pazResult[pnColum+i*pnColum+5]);
        data->_Tbl_Device_History.Electricity=atoi(pazResult[pnColum+i*pnColum+6]);
        data->_Tbl_Device_History.IsAlarm=atoi(pazResult[pnColum+i*pnColum+7]);
        data->_Tbl_Device_History=Populate_Tbl_Device_History(data->_Tbl_Device_History);
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
Tbl_Device_History Tbl_Device_HistoryFindSingle(char *Con){
    char sql[256];
    sprintf(sql,"select HistoryID,DeviceID,HistoryDate,Temperature,Humidity,Luminosity,Electricity,IsAlarm from Tbl_Device_History where 1=1 %s",Con);
    char **pazResult;
    int pnRow,pnColum;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    //只返回第一条
    Tbl_Device_History _Tbl_Device_History;
    _Tbl_Device_History.HistoryID=0;
    _Tbl_Device_History.DeviceID=0;
    strcpy(_Tbl_Device_History.HistoryDate, " ");
    _Tbl_Device_History.Temperature=0;
    _Tbl_Device_History.Humidity=0;
    _Tbl_Device_History.Luminosity=0;
    _Tbl_Device_History.Electricity=0;
    _Tbl_Device_History.IsAlarm=0;
    if (pnRow<=0) {
        return _Tbl_Device_History;
    }
    _Tbl_Device_History.HistoryID=atoi(pazResult[pnColum+0]);
    _Tbl_Device_History.DeviceID=atoi(pazResult[pnColum+1]);
    strcpy(_Tbl_Device_History.HistoryDate, pazResult[pnColum+2]);
    _Tbl_Device_History.Temperature=atoi(pazResult[pnColum+3]);
    _Tbl_Device_History.Humidity=atoi(pazResult[pnColum+4]);
    _Tbl_Device_History.Luminosity=atoi(pazResult[pnColum+5]);
    _Tbl_Device_History.Electricity=atoi(pazResult[pnColum+6]);
    _Tbl_Device_History.IsAlarm=atoi(pazResult[pnColum+7]);
    sqlite3_free_table(pazResult);
    return _Tbl_Device_History;
}
/*
 * 分页查找
 * Con 查找条件
 * Sort 排序条件
 * PageSize 每页多少条
 * CurrentPageIndex 第几页
 */
int Tbl_Device_HistoryFindPage(SqlLinkQueue list,char *Con,char *Sort,int PageSize,int CurrentPageIndex){
    char sql[4096];
    sprintf(sql,"select HistoryID,DeviceID,HistoryDate,Temperature,Humidity,Luminosity,Electricity,IsAlarm from Tbl_Device_History where 1=1 %s %s LIMIT %d OFFSET %d",Con,Sort,PageSize,PageSize*(CurrentPageIndex-1));
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    if(pnRow==0)return 0;
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        data->_Tbl_Device_History.HistoryID=atoi(pazResult[pnColum+i*pnColum+0]);
        data->_Tbl_Device_History.DeviceID=atoi(pazResult[pnColum+i*pnColum+1]);
        strcpy(data->_Tbl_Device_History.HistoryDate, pazResult[pnColum+i*pnColum+2]);
        data->_Tbl_Device_History.Temperature=atof(pazResult[pnColum+i*pnColum+3]);
        data->_Tbl_Device_History.Humidity=atof(pazResult[pnColum+i*pnColum+4]);
        data->_Tbl_Device_History.Luminosity=atof(pazResult[pnColum+i*pnColum+5]);
        data->_Tbl_Device_History.Electricity=atoi(pazResult[pnColum+i*pnColum+6]);
        data->_Tbl_Device_History.IsAlarm=atoi(pazResult[pnColum+i*pnColum+7]);
        data->_Tbl_Device_History=Populate_Tbl_Device_History(data->_Tbl_Device_History);
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
int Tbl_Device_HistoryGetTotalPageCount(char *Con,int PageSize){
    char sql[256];
    sprintf(sql,"SELECT (count(*)*1.0/%d) from Tbl_Device_History where 1=1 %s",PageSize,Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    sqlite3_free_table(pazResult);
    return (int)ceil(atof(pazResult[pnColum]));
}

