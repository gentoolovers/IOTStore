// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_User_Info.c
// 项目名称：物联仓储项目
// 创建时间：2016-10-13
// 负责人：张家铭
// ===================================================================
#include "Tbl_User_InfoDAL.h"

//填充结构体
Tbl_User_Info Populate_Tbl_User_Info(Tbl_User_Info _Tbl_User_Info){
    _Tbl_User_Info.UserID=_Tbl_User_Info.UserID;
    if(strlen(_Tbl_User_Info.UserName)==0)strcpy(_Tbl_User_Info.UserName, " ");
    if(strlen(_Tbl_User_Info.Password)==0)strcpy(_Tbl_User_Info.Password, " ");
    _Tbl_User_Info.RoleID=_Tbl_User_Info.RoleID;
    if(strlen(_Tbl_User_Info.NickName)==0)strcpy(_Tbl_User_Info.NickName, " ");
    
    return _Tbl_User_Info;
}

//构造函数
Tbl_User_Info Tbl_User_InfoInit(int UserID,char * UserName,char * Password,int RoleID,char * NickName){
    Tbl_User_Info _Tbl_User_Info;
    _Tbl_User_Info.UserID=0;
    strcpy(_Tbl_User_Info.UserName, UserName);
    strcpy(_Tbl_User_Info.Password, Password);
    _Tbl_User_Info.RoleID=0;
    strcpy(_Tbl_User_Info.NickName, NickName);
    return _Tbl_User_Info;
}
//增加
bool Tbl_User_InfoAdd(Tbl_User_Info _Tbl_User_Info){
    _Tbl_User_Info=Populate_Tbl_User_Info(_Tbl_User_Info);
    char sql[128];
    sprintf(sql,"insert into Tbl_User_Info (UserName,Password,RoleID,NickName) values('%s','%s',%d,'%s')",_Tbl_User_Info.UserName,_Tbl_User_Info.Password,_Tbl_User_Info.RoleID,_Tbl_User_Info.NickName);
    return exec_sql(sql)?true:false;
}
//删除
bool Tbl_User_InfoDelete(char *Con){
    char sql[128];
    sprintf(sql,"delete from Tbl_User_Info where 1=1 %s",Con);
    return exec_sql(sql)?true:false;
}
//修改
bool Tbl_User_InfoModify(Tbl_User_Info _Tbl_User_Info){
    _Tbl_User_Info=Populate_Tbl_User_Info(_Tbl_User_Info);
    char sql[128];
    sprintf(sql,"update Tbl_User_Info set UserName='%s',Password='%s',RoleID=%d,NickName='%s' where UserID=%d",_Tbl_User_Info.UserName,_Tbl_User_Info.Password,_Tbl_User_Info.RoleID,_Tbl_User_Info.NickName,_Tbl_User_Info.UserID);
    return exec_sql(sql)?true:false;
}


//查询
void Tbl_User_InfoFind(SqlLinkQueue list,char *Con){
    char sql[128];
    sprintf(sql,"select UserID,UserName,Password,RoleID,NickName from Tbl_User_Info where 1=1 %s",Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    int i;
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        data->_Tbl_User_Info.UserID=atoi(pazResult[pnColum+i*pnColum+0]);
        strcpy(data->_Tbl_User_Info.UserName, pazResult[pnColum+i*pnColum+1]);
        strcpy(data->_Tbl_User_Info.Password, pazResult[pnColum+i*pnColum+2]);
        data->_Tbl_User_Info.RoleID=atoi(pazResult[pnColum+i*pnColum+3]);
        strcpy(data->_Tbl_User_Info.NickName, pazResult[pnColum+i*pnColum+4]);
        data->_Tbl_User_Info=Populate_Tbl_User_Info(data->_Tbl_User_Info);
        if(!in_linkqueue(list,data))
        {
            perror("fail to in_linkqueue!");
            free_linkqueue(list);
            break;
        }
    }
}


//查询单条
Tbl_User_Info Tbl_User_InfoFindSingle(char *Con){
    char sql[128];
    sprintf(sql,"select UserID,UserName,Password,RoleID,NickName from Tbl_User_Info where 1=1 %s",Con);
    char **pazResult;
    int pnRow,pnColum;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    //只返回第一条
    Tbl_User_Info _Tbl_User_Info;
    if (pnRow<=0) {
        return _Tbl_User_Info;
    }
    _Tbl_User_Info.UserID=atoi(pazResult[pnColum+0]);
    strcpy(_Tbl_User_Info.UserName, pazResult[pnColum+1]);
    strcpy(_Tbl_User_Info.Password, pazResult[pnColum+2]);
    _Tbl_User_Info.RoleID=atoi(pazResult[pnColum+3]);
    strcpy(_Tbl_User_Info.NickName, pazResult[pnColum+4]);
    return _Tbl_User_Info;
}
/*
 * 分页查找
 * Con 查找条件
 * Sort 排序条件
 * PageSize 每页多少条
 * CurrentPageIndex 第几页
 */
void Tbl_User_InfoFindPage(SqlLinkQueue list,char *Con,char *Sort,int PageSize,int CurrentPageIndex){
    char sql[128];
    int i;
    sprintf(sql,"select UserID,UserName,Password,RoleID,NickName from Tbl_User_Info where 1=1 %s %s LIMIT %d OFFSET %d",Con,Sort,PageSize,PageSize*(CurrentPageIndex-1));
    printf("%s\n",sql);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    for (i=0; i<pnRow; i++) {
        datetype *data=(datetype*)malloc(sizeof(datetype));
        data->_Tbl_User_Info.UserID=atoi(pazResult[pnColum+i*pnColum+0]);
        strcpy(data->_Tbl_User_Info.UserName, pazResult[pnColum+i*pnColum+1]);
        strcpy(data->_Tbl_User_Info.Password, pazResult[pnColum+i*pnColum+2]);
        data->_Tbl_User_Info.RoleID=atoi(pazResult[pnColum+i*pnColum+3]);
        strcpy(data->_Tbl_User_Info.NickName, pazResult[pnColum+i*pnColum+4]);
        data->_Tbl_User_Info=Populate_Tbl_User_Info(data->_Tbl_User_Info);
        if(!in_linkqueue(list,data))
        {
            perror("fail to in_linkqueue!");
            free_linkqueue(list);
            break;
        }
    }
}
//获取总页数
int Tbl_User_InfoGetTotalPageCount(char *Con,int PageSize){
    char sql[128];
    sprintf(sql,"SELECT (count(*)*1.0/%d) from Tbl_User_Info where 1=1 %s",PageSize,Con);
    int pnRow,pnColum;
    char **pazResult;
    my_get_table(&pnColum, &pnRow, &pazResult, sql);
    return (int)ceil(atof(pazResult[pnColum]));
}

