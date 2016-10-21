// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_RFID_History.c
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#ifndef Tbl_RFID_HistoryDAL_h
#define Tbl_RFID_HistoryDAL_h

#include "SqlHelper_Sqlite3.h"

//增加
bool Tbl_RFID_HistoryAdd(Tbl_RFID_History _Tbl_RFID_History);
//删除
bool Tbl_RFID_HistoryDelete(char *Con);
//修改
bool Tbl_RFID_HistoryModify(Tbl_RFID_History _Tbl_RFID_History);
//查询
int Tbl_RFID_HistoryFind(SqlLinkQueue list,char *Con);
//查询单条
Tbl_RFID_History Tbl_RFID_HistoryFindSingle(char *Con);
/*
 * 分页查找
 * Con 查找条件
 * Sort 排序条件
 * PageSize 每页多少条
 * CurrentPageIndex 第几页
 */
int Tbl_RFID_HistoryFindPage(SqlLinkQueue list,char *Con,char *Sort,int PageSize,int CurrentPageIndex);
//获取总页数
int Tbl_RFID_HistoryGetTotalPageCount(char *Con,int PageSize);


#endif /* Tbl_RFID_HistoryDAL_h */




