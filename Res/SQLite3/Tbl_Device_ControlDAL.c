// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Device_Control.c
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#include <math.h>
#include "Tbl_Device_ControlDAL.h"

//填充结构体
Tbl_Device_Control Populate_Tbl_Device_Control(Tbl_Device_Control _Tbl_Device_Control){
    _Tbl_Device_Control.DeviceID=_Tbl_Device_Control.DeviceID;
    _Tbl_Device_Control.RFIDSet=_Tbl_Device_Control.RFIDSet;
    _Tbl_Device_Control.AlarmSet=_Tbl_Device_Control.AlarmSet;
    _Tbl_Device_Control.LedSet=_Tbl_Device_Control.LedSet;
    _Tbl_Device_Control.BeepSet=_Tbl_Device_Control.BeepSet;
    _Tbl_Device_Control.FanSet=_Tbl_Device_Control.FanSet;
    _Tbl_Device_Control.SegSet=_Tbl_Device_Control.SegSet;
    _Tbl_Device_Control.IsSet=_Tbl_Device_Control.IsSet;
    
    return _Tbl_Device_Control;
}


//增加
bool Tbl_Device_ControlAdd(Tbl_Device_Control _Tbl_Device_Control){
    _Tbl_Device_Control=Populate_Tbl_Device_Control(_Tbl_Device_Control);
    char sql[256];
	sprintf(sql,"insert into Tbl_Device_Control (DeviceID,RFIDSet,AlarmSet,LedSet,BeepSet,FanSet,SegSet,IsSet) values(%d,%d,%d,%d,%d,%d,%d,%d)",_Tbl_Device_Control.DeviceID,_Tbl_Device_Control.RFIDSet,_Tbl_Device_Control.AlarmSet,_Tbl_Device_Control.LedSet,_Tbl_Device_Control.BeepSet,_Tbl_Device_Control.FanSet,_Tbl_Device_Control.SegSet,_Tbl_Device_Control.IsSet);
    return exec_sql(sql)?true:false;
}
//删除
bool Tbl_Device_ControlDelete(char *Con){
    char sql[256];
    sprintf(sql,"delete from Tbl_Device_Control where 1=1 %s",Con);
    return exec_sql(sql)?true:false;
}
//修改
bool Tbl_Device_ControlModify(Tbl_Device_Control _Tbl_Device_Control){
    _Tbl_Device_Control=Populate_Tbl_Device_Control(_Tbl_Device_Control);
    char sql[256];
    sprintf(sql,"update Tbl_Device_Control set RFIDSet=%d,AlarmSet=%d,LedSet=%d,BeepSet=%d,FanSet=%d,SegSet=%d,IsSet=%d where DeviceID=%d",_Tbl_Device_Control.RFIDSet,_Tbl_Device_Control.AlarmSet,_Tbl_Device_Control.LedSet,_Tbl_Device_Control.BeepSet,_Tbl_Device_Control.FanSet,_Tbl_Device_Control.SegSet,_Tbl_Device_Control.IsSet,_Tbl_Device_Control.DeviceID);
    return exec_sql(sql)?true:false;
}


//查询
int Tbl_Device_ControlFind(SqlLinkQueue list,char *Con){
    char sql[256];
    sprintf(sql,"select DeviceID,RFIDSet,AlarmSet,LedSet,BeepSet,FanSet,SegSet,IsSet from Tbl_Device_Control where 1=1 %s",Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    if(pnRow==0)return 0;
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        data->_Tbl_Device_Control.DeviceID=atoi(pazResult[pnColum+i*pnColum+0]);
        data->_Tbl_Device_Control.RFIDSet=atoi(pazResult[pnColum+i*pnColum+1]);
        data->_Tbl_Device_Control.AlarmSet=atoi(pazResult[pnColum+i*pnColum+2]);
        data->_Tbl_Device_Control.LedSet=atoi(pazResult[pnColum+i*pnColum+3]);
        data->_Tbl_Device_Control.BeepSet=atoi(pazResult[pnColum+i*pnColum+4]);
        data->_Tbl_Device_Control.FanSet=atoi(pazResult[pnColum+i*pnColum+5]);
        data->_Tbl_Device_Control.SegSet=atoi(pazResult[pnColum+i*pnColum+6]);
        data->_Tbl_Device_Control.IsSet=atoi(pazResult[pnColum+i*pnColum+7]);
        data->_Tbl_Device_Control=Populate_Tbl_Device_Control(data->_Tbl_Device_Control);
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
Tbl_Device_Control Tbl_Device_ControlFindSingle(char *Con){
    char sql[256];
    sprintf(sql,"select DeviceID,RFIDSet,AlarmSet,LedSet,BeepSet,FanSet,SegSet,IsSet from Tbl_Device_Control where 1=1 %s",Con);
    char **pazResult;
    int pnRow,pnColum;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    //只返回第一条
    Tbl_Device_Control _Tbl_Device_Control;
    _Tbl_Device_Control.DeviceID=0;
    _Tbl_Device_Control.RFIDSet=0;
    _Tbl_Device_Control.AlarmSet=0;
    _Tbl_Device_Control.LedSet=0;
    _Tbl_Device_Control.BeepSet=0;
    _Tbl_Device_Control.FanSet=0;
    _Tbl_Device_Control.SegSet=0;
    _Tbl_Device_Control.IsSet=0;
    if (pnRow<=0) {
        return _Tbl_Device_Control;
    }
    _Tbl_Device_Control.DeviceID=atoi(pazResult[pnColum+0]);
    _Tbl_Device_Control.RFIDSet=atoi(pazResult[pnColum+1]);
    _Tbl_Device_Control.AlarmSet=atoi(pazResult[pnColum+2]);
    _Tbl_Device_Control.LedSet=atoi(pazResult[pnColum+3]);
    _Tbl_Device_Control.BeepSet=atoi(pazResult[pnColum+4]);
    _Tbl_Device_Control.FanSet=atoi(pazResult[pnColum+5]);
    _Tbl_Device_Control.SegSet=atoi(pazResult[pnColum+6]);
    _Tbl_Device_Control.IsSet=atoi(pazResult[pnColum+7]);
    sqlite3_free_table(pazResult);
    return _Tbl_Device_Control;
}
/*
 * 分页查找
 * Con 查找条件
 * Sort 排序条件
 * PageSize 每页多少条
 * CurrentPageIndex 第几页
 */
int Tbl_Device_ControlFindPage(SqlLinkQueue list,char *Con,char *Sort,int PageSize,int CurrentPageIndex){
    char sql[256];
    sprintf(sql,"select DeviceID,RFIDSet,AlarmSet,LedSet,BeepSet,FanSet,SegSet,IsSet from Tbl_Device_Control where 1=1 %s %s LIMIT %d OFFSET %d",Con,Sort,PageSize,PageSize*(CurrentPageIndex-1));
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    if(pnRow==0)return 0;
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        data->_Tbl_Device_Control.DeviceID=atoi(pazResult[pnColum+i*pnColum+0]);
        data->_Tbl_Device_Control.RFIDSet=atoi(pazResult[pnColum+i*pnColum+1]);
        data->_Tbl_Device_Control.AlarmSet=atoi(pazResult[pnColum+i*pnColum+2]);
        data->_Tbl_Device_Control.LedSet=atoi(pazResult[pnColum+i*pnColum+3]);
        data->_Tbl_Device_Control.BeepSet=atoi(pazResult[pnColum+i*pnColum+4]);
        data->_Tbl_Device_Control.FanSet=atoi(pazResult[pnColum+i*pnColum+5]);
        data->_Tbl_Device_Control.SegSet=atoi(pazResult[pnColum+i*pnColum+6]);
        data->_Tbl_Device_Control.IsSet=atoi(pazResult[pnColum+i*pnColum+7]);
        data->_Tbl_Device_Control=Populate_Tbl_Device_Control(data->_Tbl_Device_Control);
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
int Tbl_Device_ControlGetTotalPageCount(char *Con,int PageSize){
    char sql[256];
    sprintf(sql,"SELECT (count(*)*1.0/%d) from Tbl_Device_Control where 1=1 %s",PageSize,Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    sqlite3_free_table(pazResult);
    return (int)ceil(atof(pazResult[pnColum]));
}

