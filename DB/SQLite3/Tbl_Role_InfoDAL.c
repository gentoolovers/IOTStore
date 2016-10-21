// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Role_Info.c
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#include <math.h>
#include "Tbl_Role_InfoDAL.h"

//填充结构体
Tbl_Role_Info Populate_Tbl_Role_Info(Tbl_Role_Info _Tbl_Role_Info){
    _Tbl_Role_Info.RoleID=_Tbl_Role_Info.RoleID;
    if(strlen(_Tbl_Role_Info.RoleName)==0)strcpy(_Tbl_Role_Info.RoleName, " ");
    
    return _Tbl_Role_Info;
}


//增加
bool Tbl_Role_InfoAdd(Tbl_Role_Info _Tbl_Role_Info){
    _Tbl_Role_Info=Populate_Tbl_Role_Info(_Tbl_Role_Info);
    char sql[256];
    sprintf(sql,"insert into Tbl_Role_Info (RoleName) values('%s')",_Tbl_Role_Info.RoleName);
    return exec_sql(sql)?true:false;
}
//删除
bool Tbl_Role_InfoDelete(char *Con){
    char sql[256];
    sprintf(sql,"delete from Tbl_Role_Info where 1=1 %s",Con);
    return exec_sql(sql)?true:false;
}
//修改
bool Tbl_Role_InfoModify(Tbl_Role_Info _Tbl_Role_Info){
    _Tbl_Role_Info=Populate_Tbl_Role_Info(_Tbl_Role_Info);
    char sql[256];
    sprintf(sql,"update Tbl_Role_Info set RoleName='%s' where RoleID=%d",_Tbl_Role_Info.RoleName,_Tbl_Role_Info.RoleID);
    return exec_sql(sql)?true:false;
}


//查询
int Tbl_Role_InfoFind(SqlLinkQueue list,char *Con){
    char sql[256];
    sprintf(sql,"select RoleID,RoleName from Tbl_Role_Info where 1=1 %s",Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    if(pnRow==0)return 0;
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        data->_Tbl_Role_Info.RoleID=atoi(pazResult[pnColum+i*pnColum+0]);
        strcpy(data->_Tbl_Role_Info.RoleName, pazResult[pnColum+i*pnColum+1]);
        data->_Tbl_Role_Info=Populate_Tbl_Role_Info(data->_Tbl_Role_Info);
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
Tbl_Role_Info Tbl_Role_InfoFindSingle(char *Con){
    char sql[256];
    sprintf(sql,"select RoleID,RoleName from Tbl_Role_Info where 1=1 %s",Con);
    char **pazResult;
    int pnRow,pnColum;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    //只返回第一条
    Tbl_Role_Info _Tbl_Role_Info;
    _Tbl_Role_Info.RoleID=0;
    strcpy(_Tbl_Role_Info.RoleName, " ");
    if (pnRow<=0) {
        return _Tbl_Role_Info;
    }
    _Tbl_Role_Info.RoleID=atoi(pazResult[pnColum+0]);
    strcpy(_Tbl_Role_Info.RoleName, pazResult[pnColum+1]);
    sqlite3_free_table(pazResult);
    return _Tbl_Role_Info;
}
/*
 * 分页查找
 * Con 查找条件
 * Sort 排序条件
 * PageSize 每页多少条
 * CurrentPageIndex 第几页
 */
int Tbl_Role_InfoFindPage(SqlLinkQueue list,char *Con,char *Sort,int PageSize,int CurrentPageIndex){
    char sql[256];
    sprintf(sql,"select RoleID,RoleName from Tbl_Role_Info where 1=1 %s %s LIMIT %d OFFSET %d",Con,Sort,PageSize,PageSize*(CurrentPageIndex-1));
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    if(pnRow==0)return 0;
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        data->_Tbl_Role_Info.RoleID=atoi(pazResult[pnColum+i*pnColum+0]);
        strcpy(data->_Tbl_Role_Info.RoleName, pazResult[pnColum+i*pnColum+1]);
        data->_Tbl_Role_Info=Populate_Tbl_Role_Info(data->_Tbl_Role_Info);
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
int Tbl_Role_InfoGetTotalPageCount(char *Con,int PageSize){
    char sql[256];
    sprintf(sql,"SELECT (count(*)*1.0/%d) from Tbl_Role_Info where 1=1 %s",PageSize,Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    sqlite3_free_table(pazResult);
    return (int)ceil(atof(pazResult[pnColum]));
}

