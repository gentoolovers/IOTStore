// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Article_Type.c
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#ifndef Tbl_Article_TypeDAL_h
#define Tbl_Article_TypeDAL_h

#include "SqlHelper_Sqlite3.h"

//增加
bool Tbl_Article_TypeAdd(Tbl_Article_Type _Tbl_Article_Type);
//删除
bool Tbl_Article_TypeDelete(char *Con);
//修改
bool Tbl_Article_TypeModify(Tbl_Article_Type _Tbl_Article_Type);
//查询
int Tbl_Article_TypeFind(SqlLinkQueue list,char *Con);
//查询单条
Tbl_Article_Type Tbl_Article_TypeFindSingle(char *Con);
/*
 * 分页查找
 * Con 查找条件
 * Sort 排序条件
 * PageSize 每页多少条
 * CurrentPageIndex 第几页
 */
int Tbl_Article_TypeFindPage(SqlLinkQueue list,char *Con,char *Sort,int PageSize,int CurrentPageIndex);
//获取总页数
int Tbl_Article_TypeGetTotalPageCount(char *Con,int PageSize);


#endif /* Tbl_Article_TypeDAL_h */




