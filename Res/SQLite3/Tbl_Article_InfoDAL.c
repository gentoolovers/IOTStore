// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Article_Info.c
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#include <math.h>
#include "Tbl_Article_InfoDAL.h"

//填充结构体
Tbl_Article_Info Populate_Tbl_Article_Info(Tbl_Article_Info _Tbl_Article_Info){
    _Tbl_Article_Info.ArticleID=_Tbl_Article_Info.ArticleID;
    if(strlen(_Tbl_Article_Info.ArticleName)==0)strcpy(_Tbl_Article_Info.ArticleName, " ");
    _Tbl_Article_Info.StorageID=_Tbl_Article_Info.StorageID;
    _Tbl_Article_Info.TypeID=_Tbl_Article_Info.TypeID;
    
    return _Tbl_Article_Info;
}


//增加
bool Tbl_Article_InfoAdd(Tbl_Article_Info _Tbl_Article_Info){
    _Tbl_Article_Info=Populate_Tbl_Article_Info(_Tbl_Article_Info);
    char sql[256];
    sprintf(sql,"insert into Tbl_Article_Info (ArticleName,StorageID,TypeID) values('%s',%d,%d)",_Tbl_Article_Info.ArticleName,_Tbl_Article_Info.StorageID,_Tbl_Article_Info.TypeID);
    return exec_sql(sql)?true:false;
}
//删除
bool Tbl_Article_InfoDelete(char *Con){
    char sql[256];
    sprintf(sql,"delete from Tbl_Article_Info where 1=1 %s",Con);
    return exec_sql(sql)?true:false;
}
//修改
bool Tbl_Article_InfoModify(Tbl_Article_Info _Tbl_Article_Info){
    _Tbl_Article_Info=Populate_Tbl_Article_Info(_Tbl_Article_Info);
    char sql[256];
    sprintf(sql,"update Tbl_Article_Info set ArticleName='%s',StorageID=%d,TypeID=%d where ArticleID=%d",_Tbl_Article_Info.ArticleName,_Tbl_Article_Info.StorageID,_Tbl_Article_Info.TypeID,_Tbl_Article_Info.ArticleID);
    return exec_sql(sql)?true:false;
}


//查询
int Tbl_Article_InfoFind(SqlLinkQueue list,char *Con){
    char sql[256];
    sprintf(sql,"select ArticleID,ArticleName,StorageID,TypeID from Tbl_Article_Info where 1=1 %s",Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    if(pnRow==0)return 0;
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        data->_Tbl_Article_Info.ArticleID=atoi(pazResult[pnColum+i*pnColum+0]);
        strcpy(data->_Tbl_Article_Info.ArticleName, pazResult[pnColum+i*pnColum+1]);
        data->_Tbl_Article_Info.StorageID=atoi(pazResult[pnColum+i*pnColum+2]);
        data->_Tbl_Article_Info.TypeID=atoi(pazResult[pnColum+i*pnColum+3]);
        data->_Tbl_Article_Info=Populate_Tbl_Article_Info(data->_Tbl_Article_Info);
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
Tbl_Article_Info Tbl_Article_InfoFindSingle(char *Con){
    char sql[256];
    sprintf(sql,"select ArticleID,ArticleName,StorageID,TypeID from Tbl_Article_Info where 1=1 %s",Con);
    char **pazResult;
    int pnRow,pnColum;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    //只返回第一条
    Tbl_Article_Info _Tbl_Article_Info;
    _Tbl_Article_Info.ArticleID=0;
    strcpy(_Tbl_Article_Info.ArticleName, " ");
    _Tbl_Article_Info.StorageID=0;
    _Tbl_Article_Info.TypeID=0;
    if (pnRow<=0) {
        return _Tbl_Article_Info;
    }
    _Tbl_Article_Info.ArticleID=atoi(pazResult[pnColum+0]);
    strcpy(_Tbl_Article_Info.ArticleName, pazResult[pnColum+1]);
    _Tbl_Article_Info.StorageID=atoi(pazResult[pnColum+2]);
    _Tbl_Article_Info.TypeID=atoi(pazResult[pnColum+3]);
    sqlite3_free_table(pazResult);
    return _Tbl_Article_Info;
}
/*
 * 分页查找
 * Con 查找条件
 * Sort 排序条件
 * PageSize 每页多少条
 * CurrentPageIndex 第几页
 */
int Tbl_Article_InfoFindPage(SqlLinkQueue list,char *Con,char *Sort,int PageSize,int CurrentPageIndex){
    char sql[256];
    sprintf(sql,"select ArticleID,ArticleName,StorageID,TypeID from Tbl_Article_Info where 1=1 %s %s LIMIT %d OFFSET %d",Con,Sort,PageSize,PageSize*(CurrentPageIndex-1));
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    if(pnRow==0)return 0;
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        data->_Tbl_Article_Info.ArticleID=atoi(pazResult[pnColum+i*pnColum+0]);
        strcpy(data->_Tbl_Article_Info.ArticleName, pazResult[pnColum+i*pnColum+1]);
        data->_Tbl_Article_Info.StorageID=atoi(pazResult[pnColum+i*pnColum+2]);
        data->_Tbl_Article_Info.TypeID=atoi(pazResult[pnColum+i*pnColum+3]);
        data->_Tbl_Article_Info=Populate_Tbl_Article_Info(data->_Tbl_Article_Info);
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
int Tbl_Article_InfoGetTotalPageCount(char *Con,int PageSize){
    char sql[256];
    sprintf(sql,"SELECT (count(*)*1.0/%d) from Tbl_Article_Info where 1=1 %s",PageSize,Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    sqlite3_free_table(pazResult);
    return (int)ceil(atof(pazResult[pnColum]));
}

