// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Device_Parameter.c
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#include <math.h>
#include "Tbl_Device_ParameterDAL.h"

//填充结构体
Tbl_Device_Parameter Populate_Tbl_Device_Parameter(Tbl_Device_Parameter _Tbl_Device_Parameter){
    _Tbl_Device_Parameter.DeviceID=_Tbl_Device_Parameter.DeviceID;
    _Tbl_Device_Parameter.MinTem=_Tbl_Device_Parameter.MinTem;
    _Tbl_Device_Parameter.MaxTem=_Tbl_Device_Parameter.MaxTem;
    _Tbl_Device_Parameter.MinHum=_Tbl_Device_Parameter.MinHum;
    _Tbl_Device_Parameter.MaxHum=_Tbl_Device_Parameter.MaxHum;
    _Tbl_Device_Parameter.MinLit=_Tbl_Device_Parameter.MinLit;
    _Tbl_Device_Parameter.MaxLit=_Tbl_Device_Parameter.MaxLit;
    _Tbl_Device_Parameter.TimeSet=_Tbl_Device_Parameter.TimeSet;
    _Tbl_Device_Parameter.IsSet=_Tbl_Device_Parameter.IsSet;
    
    return _Tbl_Device_Parameter;
}


//增加
bool Tbl_Device_ParameterAdd(Tbl_Device_Parameter _Tbl_Device_Parameter){
    _Tbl_Device_Parameter=Populate_Tbl_Device_Parameter(_Tbl_Device_Parameter);
    char sql[256];
	sprintf(sql,"insert into Tbl_Device_Parameter (DeviceID,MinTem,MaxTem,MinHum,MaxHum,MinLit,MaxLit,TimeSet,IsSet) values(%d,%f,%f,%f,%f,%f,%f,%d,%d)",_Tbl_Device_Parameter.DeviceID,_Tbl_Device_Parameter.MinTem,_Tbl_Device_Parameter.MaxTem,_Tbl_Device_Parameter.MinHum,_Tbl_Device_Parameter.MaxHum,_Tbl_Device_Parameter.MinLit,_Tbl_Device_Parameter.MaxLit,_Tbl_Device_Parameter.TimeSet,_Tbl_Device_Parameter.IsSet);
    return exec_sql(sql)?true:false;
}
//删除
bool Tbl_Device_ParameterDelete(char *Con){
    char sql[256];
    sprintf(sql,"delete from Tbl_Device_Parameter where 1=1 %s",Con);
    return exec_sql(sql)?true:false;
}
//修改
bool Tbl_Device_ParameterModify(Tbl_Device_Parameter _Tbl_Device_Parameter){
    _Tbl_Device_Parameter=Populate_Tbl_Device_Parameter(_Tbl_Device_Parameter);
    char sql[256];
    sprintf(sql,"update Tbl_Device_Parameter set MinTem=%f,MaxTem=%f,MinHum=%f,MaxHum=%f,MinLit=%f,MaxLit=%f,TimeSet=%d,IsSet=%d where DeviceID=%d",_Tbl_Device_Parameter.MinTem,_Tbl_Device_Parameter.MaxTem,_Tbl_Device_Parameter.MinHum,_Tbl_Device_Parameter.MaxHum,_Tbl_Device_Parameter.MinLit,_Tbl_Device_Parameter.MaxLit,_Tbl_Device_Parameter.TimeSet,_Tbl_Device_Parameter.IsSet,_Tbl_Device_Parameter.DeviceID);
    return exec_sql(sql)?true:false;
}


//查询
int Tbl_Device_ParameterFind(SqlLinkQueue list,char *Con){
    char sql[256];
    sprintf(sql,"select DeviceID,MinTem,MaxTem,MinHum,MaxHum,MinLit,MaxLit,TimeSet,IsSet from Tbl_Device_Parameter where 1=1 %s",Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    if(pnRow==0)return 0;
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        data->_Tbl_Device_Parameter.DeviceID=atoi(pazResult[pnColum+i*pnColum+0]);
        data->_Tbl_Device_Parameter.MinTem=atof(pazResult[pnColum+i*pnColum+1]);
        data->_Tbl_Device_Parameter.MaxTem=atof(pazResult[pnColum+i*pnColum+2]);
        data->_Tbl_Device_Parameter.MinHum=atof(pazResult[pnColum+i*pnColum+3]);
        data->_Tbl_Device_Parameter.MaxHum=atof(pazResult[pnColum+i*pnColum+4]);
        data->_Tbl_Device_Parameter.MinLit=atof(pazResult[pnColum+i*pnColum+5]);
        data->_Tbl_Device_Parameter.MaxLit=atof(pazResult[pnColum+i*pnColum+6]);
        data->_Tbl_Device_Parameter.TimeSet=atoi(pazResult[pnColum+i*pnColum+7]);
        data->_Tbl_Device_Parameter.IsSet=atoi(pazResult[pnColum+i*pnColum+8]);
        data->_Tbl_Device_Parameter=Populate_Tbl_Device_Parameter(data->_Tbl_Device_Parameter);
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
Tbl_Device_Parameter Tbl_Device_ParameterFindSingle(char *Con){
    char sql[256];
    sprintf(sql,"select DeviceID,MinTem,MaxTem,MinHum,MaxHum,MinLit,MaxLit,TimeSet,IsSet from Tbl_Device_Parameter where 1=1 %s",Con);
    char **pazResult;
    int pnRow,pnColum;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    //只返回第一条
    Tbl_Device_Parameter _Tbl_Device_Parameter;
    _Tbl_Device_Parameter.DeviceID=0;
    _Tbl_Device_Parameter.MinTem=0;
    _Tbl_Device_Parameter.MaxTem=0;
    _Tbl_Device_Parameter.MinHum=0;
    _Tbl_Device_Parameter.MaxHum=0;
    _Tbl_Device_Parameter.MinLit=0;
    _Tbl_Device_Parameter.MaxLit=0;
    _Tbl_Device_Parameter.TimeSet=0;
    _Tbl_Device_Parameter.IsSet=0;
    if (pnRow<=0) {
        return _Tbl_Device_Parameter;
    }
    _Tbl_Device_Parameter.DeviceID=atoi(pazResult[pnColum+0]);
    _Tbl_Device_Parameter.MinTem=atoi(pazResult[pnColum+1]);
    _Tbl_Device_Parameter.MaxTem=atoi(pazResult[pnColum+2]);
    _Tbl_Device_Parameter.MinHum=atoi(pazResult[pnColum+3]);
    _Tbl_Device_Parameter.MaxHum=atoi(pazResult[pnColum+4]);
    _Tbl_Device_Parameter.MinLit=atoi(pazResult[pnColum+5]);
    _Tbl_Device_Parameter.MaxLit=atoi(pazResult[pnColum+6]);
    _Tbl_Device_Parameter.TimeSet=atoi(pazResult[pnColum+7]);
    _Tbl_Device_Parameter.IsSet=atoi(pazResult[pnColum+8]);
    sqlite3_free_table(pazResult);
    return _Tbl_Device_Parameter;
}
/*
 * 分页查找
 * Con 查找条件
 * Sort 排序条件
 * PageSize 每页多少条
 * CurrentPageIndex 第几页
 */
int Tbl_Device_ParameterFindPage(SqlLinkQueue list,char *Con,char *Sort,int PageSize,int CurrentPageIndex){
    char sql[256];
    sprintf(sql,"select DeviceID,MinTem,MaxTem,MinHum,MaxHum,MinLit,MaxLit,TimeSet,IsSet from Tbl_Device_Parameter where 1=1 %s %s LIMIT %d OFFSET %d",Con,Sort,PageSize,PageSize*(CurrentPageIndex-1));
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    if(pnRow==0)return 0;
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        data->_Tbl_Device_Parameter.DeviceID=atoi(pazResult[pnColum+i*pnColum+0]);
        data->_Tbl_Device_Parameter.MinTem=atof(pazResult[pnColum+i*pnColum+1]);
        data->_Tbl_Device_Parameter.MaxTem=atof(pazResult[pnColum+i*pnColum+2]);
        data->_Tbl_Device_Parameter.MinHum=atof(pazResult[pnColum+i*pnColum+3]);
        data->_Tbl_Device_Parameter.MaxHum=atof(pazResult[pnColum+i*pnColum+4]);
        data->_Tbl_Device_Parameter.MinLit=atof(pazResult[pnColum+i*pnColum+5]);
        data->_Tbl_Device_Parameter.MaxLit=atof(pazResult[pnColum+i*pnColum+6]);
        data->_Tbl_Device_Parameter.TimeSet=atoi(pazResult[pnColum+i*pnColum+7]);
        data->_Tbl_Device_Parameter.IsSet=atoi(pazResult[pnColum+i*pnColum+8]);
        data->_Tbl_Device_Parameter=Populate_Tbl_Device_Parameter(data->_Tbl_Device_Parameter);
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
int Tbl_Device_ParameterGetTotalPageCount(char *Con,int PageSize){
    char sql[256];
    sprintf(sql,"SELECT (count(*)*1.0/%d) from Tbl_Device_Parameter where 1=1 %s",PageSize,Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    sqlite3_free_table(pazResult);
    return (int)ceil(atof(pazResult[pnColum]));
}

