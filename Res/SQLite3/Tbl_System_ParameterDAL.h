// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_System_Parameter.c
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#ifndef Tbl_System_ParameterDAL_h
#define Tbl_System_ParameterDAL_h

#include "SqlHelper_Sqlite3.h"

//增加
bool Tbl_System_ParameterAdd(Tbl_System_Parameter _Tbl_System_Parameter);
//删除
bool Tbl_System_ParameterDelete(char *Con);
//修改
bool Tbl_System_ParameterModify(Tbl_System_Parameter _Tbl_System_Parameter);
//查询
int Tbl_System_ParameterFind(SqlLinkQueue list,char *Con);
//查询单条
Tbl_System_Parameter Tbl_System_ParameterFindSingle(char *Con);
/*
 * 分页查找
 * Con 查找条件
 * Sort 排序条件
 * PageSize 每页多少条
 * CurrentPageIndex 第几页
 */
int Tbl_System_ParameterFindPage(SqlLinkQueue list,char *Con,char *Sort,int PageSize,int CurrentPageIndex);
//获取总页数
int Tbl_System_ParameterGetTotalPageCount(char *Con,int PageSize);


#endif /* Tbl_System_ParameterDAL_h */




