// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Camera_Info.c
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#include <math.h>
#include "Tbl_Camera_InfoDAL.h"

//填充结构体
Tbl_Camera_Info Populate_Tbl_Camera_Info(Tbl_Camera_Info _Tbl_Camera_Info){
    _Tbl_Camera_Info.CameraID=_Tbl_Camera_Info.CameraID;
    _Tbl_Camera_Info.StorageID=_Tbl_Camera_Info.StorageID;
    if(strlen(_Tbl_Camera_Info.CameraPath)==0)strcpy(_Tbl_Camera_Info.CameraPath, " ");
    if(strlen(_Tbl_Camera_Info.CameraDate)==0)strcpy(_Tbl_Camera_Info.CameraDate, " ");
    
    return _Tbl_Camera_Info;
}


//增加
bool Tbl_Camera_InfoAdd(Tbl_Camera_Info _Tbl_Camera_Info){
    _Tbl_Camera_Info=Populate_Tbl_Camera_Info(_Tbl_Camera_Info);
    char sql[256];
    sprintf(sql,"insert into Tbl_Camera_Info (StorageID,CameraPath,CameraDate) values(%d,'%s','%s')",_Tbl_Camera_Info.StorageID,_Tbl_Camera_Info.CameraPath,_Tbl_Camera_Info.CameraDate);
    return exec_sql(sql)?true:false;
}
//删除
bool Tbl_Camera_InfoDelete(char *Con){
    char sql[256];
    sprintf(sql,"delete from Tbl_Camera_Info where 1=1 %s",Con);
    return exec_sql(sql)?true:false;
}
//修改
bool Tbl_Camera_InfoModify(Tbl_Camera_Info _Tbl_Camera_Info){
    _Tbl_Camera_Info=Populate_Tbl_Camera_Info(_Tbl_Camera_Info);
    char sql[256];
    sprintf(sql,"update Tbl_Camera_Info set StorageID=%d,CameraPath='%s',CameraDate='%s' where CameraID=%d",_Tbl_Camera_Info.StorageID,_Tbl_Camera_Info.CameraPath,_Tbl_Camera_Info.CameraDate,_Tbl_Camera_Info.CameraID);
    return exec_sql(sql)?true:false;
}


//查询
int Tbl_Camera_InfoFind(SqlLinkQueue list,char *Con){
    char sql[256];
    sprintf(sql,"select CameraID,StorageID,CameraPath,CameraDate from Tbl_Camera_Info where 1=1 %s",Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    if(pnRow==0)return 0;
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        data->_Tbl_Camera_Info.CameraID=atoi(pazResult[pnColum+i*pnColum+0]);
        data->_Tbl_Camera_Info.StorageID=atoi(pazResult[pnColum+i*pnColum+1]);
        strcpy(data->_Tbl_Camera_Info.CameraPath, pazResult[pnColum+i*pnColum+2]);
        strcpy(data->_Tbl_Camera_Info.CameraDate, pazResult[pnColum+i*pnColum+3]);
        data->_Tbl_Camera_Info=Populate_Tbl_Camera_Info(data->_Tbl_Camera_Info);
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
Tbl_Camera_Info Tbl_Camera_InfoFindSingle(char *Con){
    char sql[256];
    sprintf(sql,"select CameraID,StorageID,CameraPath,CameraDate from Tbl_Camera_Info where 1=1 %s",Con);
    char **pazResult;
    int pnRow,pnColum;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    //只返回第一条
    Tbl_Camera_Info _Tbl_Camera_Info;
    _Tbl_Camera_Info.CameraID=0;
    _Tbl_Camera_Info.StorageID=0;
    strcpy(_Tbl_Camera_Info.CameraPath, " ");
    strcpy(_Tbl_Camera_Info.CameraDate, " ");
    if (pnRow<=0) {
        return _Tbl_Camera_Info;
    }
    _Tbl_Camera_Info.CameraID=atoi(pazResult[pnColum+0]);
    _Tbl_Camera_Info.StorageID=atoi(pazResult[pnColum+1]);
    strcpy(_Tbl_Camera_Info.CameraPath, pazResult[pnColum+2]);
    strcpy(_Tbl_Camera_Info.CameraDate, pazResult[pnColum+3]);
    sqlite3_free_table(pazResult);
    return _Tbl_Camera_Info;
}
/*
 * 分页查找
 * Con 查找条件
 * Sort 排序条件
 * PageSize 每页多少条
 * CurrentPageIndex 第几页
 */
int Tbl_Camera_InfoFindPage(SqlLinkQueue list,char *Con,char *Sort,int PageSize,int CurrentPageIndex){
    char sql[256];
    sprintf(sql,"select CameraID,StorageID,CameraPath,CameraDate from Tbl_Camera_Info where 1=1 %s %s LIMIT %d OFFSET %d",Con,Sort,PageSize,PageSize*(CurrentPageIndex-1));
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    if(pnRow==0)return 0;
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        data->_Tbl_Camera_Info.CameraID=atoi(pazResult[pnColum+i*pnColum+0]);
        data->_Tbl_Camera_Info.StorageID=atoi(pazResult[pnColum+i*pnColum+1]);
        strcpy(data->_Tbl_Camera_Info.CameraPath, pazResult[pnColum+i*pnColum+2]);
        strcpy(data->_Tbl_Camera_Info.CameraDate, pazResult[pnColum+i*pnColum+3]);
        data->_Tbl_Camera_Info=Populate_Tbl_Camera_Info(data->_Tbl_Camera_Info);
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
int Tbl_Camera_InfoGetTotalPageCount(char *Con,int PageSize){
    char sql[256];
    sprintf(sql,"SELECT (count(*)*1.0/%d) from Tbl_Camera_Info where 1=1 %s",PageSize,Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    sqlite3_free_table(pazResult);
    return (int)ceil(atof(pazResult[pnColum]));
}

