// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_RFID_Info.c
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#ifndef Tbl_RFID_InfoDAL_h
#define Tbl_RFID_InfoDAL_h

#include "SqlHelper_Sqlite3.h"

//增加
bool Tbl_RFID_InfoAdd(Tbl_RFID_Info _Tbl_RFID_Info);
//删除
bool Tbl_RFID_InfoDelete(char *Con);
//修改
bool Tbl_RFID_InfoModify(Tbl_RFID_Info _Tbl_RFID_Info);
//查询
int Tbl_RFID_InfoFind(SqlLinkQueue list,char *Con);
//查询单条
Tbl_RFID_Info Tbl_RFID_InfoFindSingle(char *Con);
/*
 * 分页查找
 * Con 查找条件
 * Sort 排序条件
 * PageSize 每页多少条
 * CurrentPageIndex 第几页
 */
int Tbl_RFID_InfoFindPage(SqlLinkQueue list,char *Con,char *Sort,int PageSize,int CurrentPageIndex);
//获取总页数
int Tbl_RFID_InfoGetTotalPageCount(char *Con,int PageSize);


#endif /* Tbl_RFID_InfoDAL_h */




