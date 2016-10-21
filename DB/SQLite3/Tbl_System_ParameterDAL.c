// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_System_Parameter.c
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#include <math.h>
#include "Tbl_System_ParameterDAL.h"

//填充结构体
Tbl_System_Parameter Populate_Tbl_System_Parameter(Tbl_System_Parameter _Tbl_System_Parameter){
    if(strlen(_Tbl_System_Parameter.key)==0)strcpy(_Tbl_System_Parameter.key, " ");
    if(strlen(_Tbl_System_Parameter.value)==0)strcpy(_Tbl_System_Parameter.value, " ");
    
    return _Tbl_System_Parameter;
}


//增加
bool Tbl_System_ParameterAdd(Tbl_System_Parameter _Tbl_System_Parameter){
    _Tbl_System_Parameter=Populate_Tbl_System_Parameter(_Tbl_System_Parameter);
    char sql[256];
    sprintf(sql,"insert into Tbl_System_Parameter (value) values('%s')",_Tbl_System_Parameter.value);
    return exec_sql(sql)?true:false;
}
//删除
bool Tbl_System_ParameterDelete(char *Con){
    char sql[256];
    sprintf(sql,"delete from Tbl_System_Parameter where 1=1 %s",Con);
    return exec_sql(sql)?true:false;
}
//修改
bool Tbl_System_ParameterModify(Tbl_System_Parameter _Tbl_System_Parameter){
    _Tbl_System_Parameter=Populate_Tbl_System_Parameter(_Tbl_System_Parameter);
    char sql[256];
    sprintf(sql,"update Tbl_System_Parameter set value='%s' where key=%d",_Tbl_System_Parameter.value,_Tbl_System_Parameter.key);
    return exec_sql(sql)?true:false;
}


//查询
int Tbl_System_ParameterFind(SqlLinkQueue list,char *Con){
    char sql[256];
    sprintf(sql,"select key,value from Tbl_System_Parameter where 1=1 %s",Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    if(pnRow==0)return 0;
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        strcpy(data->_Tbl_System_Parameter.key, pazResult[pnColum+i*pnColum+0]);
        strcpy(data->_Tbl_System_Parameter.value, pazResult[pnColum+i*pnColum+1]);
        data->_Tbl_System_Parameter=Populate_Tbl_System_Parameter(data->_Tbl_System_Parameter);
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
Tbl_System_Parameter Tbl_System_ParameterFindSingle(char *Con){
    char sql[256];
    sprintf(sql,"select key,value from Tbl_System_Parameter where 1=1 %s",Con);
    char **pazResult;
    int pnRow,pnColum;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    //只返回第一条
    Tbl_System_Parameter _Tbl_System_Parameter;
    strcpy(_Tbl_System_Parameter.key, " ");
    strcpy(_Tbl_System_Parameter.value, " ");
    if (pnRow<=0) {
        return _Tbl_System_Parameter;
    }
    strcpy(_Tbl_System_Parameter.key, pazResult[pnColum+0]);
    strcpy(_Tbl_System_Parameter.value, pazResult[pnColum+1]);
    sqlite3_free_table(pazResult);
    return _Tbl_System_Parameter;
}
/*
 * 分页查找
 * Con 查找条件
 * Sort 排序条件
 * PageSize 每页多少条
 * CurrentPageIndex 第几页
 */
int Tbl_System_ParameterFindPage(SqlLinkQueue list,char *Con,char *Sort,int PageSize,int CurrentPageIndex){
    char sql[256];
    sprintf(sql,"select key,value from Tbl_System_Parameter where 1=1 %s %s LIMIT %d OFFSET %d",Con,Sort,PageSize,PageSize*(CurrentPageIndex-1));
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    if(pnRow==0)return 0;
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        strcpy(data->_Tbl_System_Parameter.key, pazResult[pnColum+i*pnColum+0]);
        strcpy(data->_Tbl_System_Parameter.value, pazResult[pnColum+i*pnColum+1]);
        data->_Tbl_System_Parameter=Populate_Tbl_System_Parameter(data->_Tbl_System_Parameter);
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
int Tbl_System_ParameterGetTotalPageCount(char *Con,int PageSize){
    char sql[256];
    sprintf(sql,"SELECT (count(*)*1.0/%d) from Tbl_System_Parameter where 1=1 %s",PageSize,Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    sqlite3_free_table(pazResult);
    return (int)ceil(atof(pazResult[pnColum]));
}

