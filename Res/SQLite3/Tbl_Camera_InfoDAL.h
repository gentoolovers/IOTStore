// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Camera_Info.c
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#ifndef Tbl_Camera_InfoDAL_h
#define Tbl_Camera_InfoDAL_h

#include "SqlHelper_Sqlite3.h"

//增加
bool Tbl_Camera_InfoAdd(Tbl_Camera_Info _Tbl_Camera_Info);
//删除
bool Tbl_Camera_InfoDelete(char *Con);
//修改
bool Tbl_Camera_InfoModify(Tbl_Camera_Info _Tbl_Camera_Info);
//查询
int Tbl_Camera_InfoFind(SqlLinkQueue list,char *Con);
//查询单条
Tbl_Camera_Info Tbl_Camera_InfoFindSingle(char *Con);
/*
 * 分页查找
 * Con 查找条件
 * Sort 排序条件
 * PageSize 每页多少条
 * CurrentPageIndex 第几页
 */
int Tbl_Camera_InfoFindPage(SqlLinkQueue list,char *Con,char *Sort,int PageSize,int CurrentPageIndex);
//获取总页数
int Tbl_Camera_InfoGetTotalPageCount(char *Con,int PageSize);


#endif /* Tbl_Camera_InfoDAL_h */




