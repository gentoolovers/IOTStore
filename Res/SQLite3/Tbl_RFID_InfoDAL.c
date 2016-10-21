// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_RFID_Info.c
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#include <math.h>
#include "Tbl_RFID_InfoDAL.h"

//填充结构体
Tbl_RFID_Info Populate_Tbl_RFID_Info(Tbl_RFID_Info _Tbl_RFID_Info){
    _Tbl_RFID_Info.RFID_ID=_Tbl_RFID_Info.RFID_ID;
    _Tbl_RFID_Info.ArticleID=_Tbl_RFID_Info.ArticleID;
    if(strlen(_Tbl_RFID_Info.RFID)==0)strcpy(_Tbl_RFID_Info.RFID, " ");
    
    return _Tbl_RFID_Info;
}


//增加
bool Tbl_RFID_InfoAdd(Tbl_RFID_Info _Tbl_RFID_Info){
    _Tbl_RFID_Info=Populate_Tbl_RFID_Info(_Tbl_RFID_Info);
    char sql[256];
    sprintf(sql,"insert into Tbl_RFID_Info (ArticleID,RFID) values(%d,'%s')",_Tbl_RFID_Info.ArticleID,_Tbl_RFID_Info.RFID);
    return exec_sql(sql)?true:false;
}
//删除
bool Tbl_RFID_InfoDelete(char *Con){
    char sql[256];
    sprintf(sql,"delete from Tbl_RFID_Info where 1=1 %s",Con);
    return exec_sql(sql)?true:false;
}
//修改
bool Tbl_RFID_InfoModify(Tbl_RFID_Info _Tbl_RFID_Info){
    _Tbl_RFID_Info=Populate_Tbl_RFID_Info(_Tbl_RFID_Info);
    char sql[256];
    sprintf(sql,"update Tbl_RFID_Info set ArticleID=%d,RFID='%s' where RFID_ID=%d",_Tbl_RFID_Info.ArticleID,_Tbl_RFID_Info.RFID,_Tbl_RFID_Info.RFID_ID);
    return exec_sql(sql)?true:false;
}


//查询
int Tbl_RFID_InfoFind(SqlLinkQueue list,char *Con){
    char sql[256];
    sprintf(sql,"select RFID_ID,ArticleID,RFID from Tbl_RFID_Info where 1=1 %s",Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    if(pnRow==0)return 0;
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        data->_Tbl_RFID_Info.RFID_ID=atoi(pazResult[pnColum+i*pnColum+0]);
        data->_Tbl_RFID_Info.ArticleID=atoi(pazResult[pnColum+i*pnColum+1]);
        strcpy(data->_Tbl_RFID_Info.RFID, pazResult[pnColum+i*pnColum+2]);
        data->_Tbl_RFID_Info=Populate_Tbl_RFID_Info(data->_Tbl_RFID_Info);
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
Tbl_RFID_Info Tbl_RFID_InfoFindSingle(char *Con){
    char sql[256];
    sprintf(sql,"select RFID_ID,ArticleID,RFID from Tbl_RFID_Info where 1=1 %s",Con);
    char **pazResult;
    int pnRow,pnColum;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    //只返回第一条
    Tbl_RFID_Info _Tbl_RFID_Info;
    _Tbl_RFID_Info.RFID_ID=0;
    _Tbl_RFID_Info.ArticleID=0;
    strcpy(_Tbl_RFID_Info.RFID, " ");
    if (pnRow<=0) {
        return _Tbl_RFID_Info;
    }
    _Tbl_RFID_Info.RFID_ID=atoi(pazResult[pnColum+0]);
    _Tbl_RFID_Info.ArticleID=atoi(pazResult[pnColum+1]);
    strcpy(_Tbl_RFID_Info.RFID, pazResult[pnColum+2]);
    sqlite3_free_table(pazResult);
    return _Tbl_RFID_Info;
}
/*
 * 分页查找
 * Con 查找条件
 * Sort 排序条件
 * PageSize 每页多少条
 * CurrentPageIndex 第几页
 */
int Tbl_RFID_InfoFindPage(SqlLinkQueue list,char *Con,char *Sort,int PageSize,int CurrentPageIndex){
    char sql[256];
    sprintf(sql,"select RFID_ID,ArticleID,RFID from Tbl_RFID_Info where 1=1 %s %s LIMIT %d OFFSET %d",Con,Sort,PageSize,PageSize*(CurrentPageIndex-1));
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    if(pnRow==0)return 0;
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        data->_Tbl_RFID_Info.RFID_ID=atoi(pazResult[pnColum+i*pnColum+0]);
        data->_Tbl_RFID_Info.ArticleID=atoi(pazResult[pnColum+i*pnColum+1]);
        strcpy(data->_Tbl_RFID_Info.RFID, pazResult[pnColum+i*pnColum+2]);
        data->_Tbl_RFID_Info=Populate_Tbl_RFID_Info(data->_Tbl_RFID_Info);
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
int Tbl_RFID_InfoGetTotalPageCount(char *Con,int PageSize){
    char sql[256];
    sprintf(sql,"SELECT (count(*)*1.0/%d) from Tbl_RFID_Info where 1=1 %s",PageSize,Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    sqlite3_free_table(pazResult);
    return (int)ceil(atof(pazResult[pnColum]));
}

