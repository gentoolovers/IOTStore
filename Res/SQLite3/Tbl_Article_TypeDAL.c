// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Article_Type.c
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#include <math.h>
#include "Tbl_Article_TypeDAL.h"

//填充结构体
Tbl_Article_Type Populate_Tbl_Article_Type(Tbl_Article_Type _Tbl_Article_Type){
    _Tbl_Article_Type.TypeID=_Tbl_Article_Type.TypeID;
    if(strlen(_Tbl_Article_Type.TypeName)==0)strcpy(_Tbl_Article_Type.TypeName, " ");
    
    return _Tbl_Article_Type;
}


//增加
bool Tbl_Article_TypeAdd(Tbl_Article_Type _Tbl_Article_Type){
    _Tbl_Article_Type=Populate_Tbl_Article_Type(_Tbl_Article_Type);
    char sql[256];
    sprintf(sql,"insert into Tbl_Article_Type (TypeName) values('%s')",_Tbl_Article_Type.TypeName);
    return exec_sql(sql)?true:false;
}
//删除
bool Tbl_Article_TypeDelete(char *Con){
    char sql[256];
    sprintf(sql,"delete from Tbl_Article_Type where 1=1 %s",Con);
    return exec_sql(sql)?true:false;
}
//修改
bool Tbl_Article_TypeModify(Tbl_Article_Type _Tbl_Article_Type){
    _Tbl_Article_Type=Populate_Tbl_Article_Type(_Tbl_Article_Type);
    char sql[256];
    sprintf(sql,"update Tbl_Article_Type set TypeName='%s' where TypeID=%d",_Tbl_Article_Type.TypeName,_Tbl_Article_Type.TypeID);
    return exec_sql(sql)?true:false;
}


//查询
int Tbl_Article_TypeFind(SqlLinkQueue list,char *Con){
    char sql[256];
    sprintf(sql,"select TypeID,TypeName from Tbl_Article_Type where 1=1 %s",Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    if(pnRow==0)return 0;
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        data->_Tbl_Article_Type.TypeID=atoi(pazResult[pnColum+i*pnColum+0]);
        strcpy(data->_Tbl_Article_Type.TypeName, pazResult[pnColum+i*pnColum+1]);
        data->_Tbl_Article_Type=Populate_Tbl_Article_Type(data->_Tbl_Article_Type);
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
Tbl_Article_Type Tbl_Article_TypeFindSingle(char *Con){
    char sql[256];
    sprintf(sql,"select TypeID,TypeName from Tbl_Article_Type where 1=1 %s",Con);
    char **pazResult;
    int pnRow,pnColum;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    //只返回第一条
    Tbl_Article_Type _Tbl_Article_Type;
    _Tbl_Article_Type.TypeID=0;
    strcpy(_Tbl_Article_Type.TypeName, " ");
    if (pnRow<=0) {
        return _Tbl_Article_Type;
    }
    _Tbl_Article_Type.TypeID=atoi(pazResult[pnColum+0]);
    strcpy(_Tbl_Article_Type.TypeName, pazResult[pnColum+1]);
    sqlite3_free_table(pazResult);
    return _Tbl_Article_Type;
}
/*
 * 分页查找
 * Con 查找条件
 * Sort 排序条件
 * PageSize 每页多少条
 * CurrentPageIndex 第几页
 */
int Tbl_Article_TypeFindPage(SqlLinkQueue list,char *Con,char *Sort,int PageSize,int CurrentPageIndex){
    char sql[256];
    sprintf(sql,"select TypeID,TypeName from Tbl_Article_Type where 1=1 %s %s LIMIT %d OFFSET %d",Con,Sort,PageSize,PageSize*(CurrentPageIndex-1));
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    if(pnRow==0)return 0;
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        data->_Tbl_Article_Type.TypeID=atoi(pazResult[pnColum+i*pnColum+0]);
        strcpy(data->_Tbl_Article_Type.TypeName, pazResult[pnColum+i*pnColum+1]);
        data->_Tbl_Article_Type=Populate_Tbl_Article_Type(data->_Tbl_Article_Type);
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
int Tbl_Article_TypeGetTotalPageCount(char *Con,int PageSize){
    char sql[256];
    sprintf(sql,"SELECT (count(*)*1.0/%d) from Tbl_Article_Type where 1=1 %s",PageSize,Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    sqlite3_free_table(pazResult);
    return (int)ceil(atof(pazResult[pnColum]));
}

