//
//  文件名：SqlHelper_Sqlite3.h
//  项目名称：物联仓储
//
//  Created by 张家铭 on 2016-10-19.
//  Copyright © 2016年 zjm. All rights reserved.
//

#ifndef SqlHelper_Sqlite3_h
#define SqlHelper_Sqlite3_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sqlite3.h>

#define DB_NAME "/var/www/cgi-bin/QMSSLSJ.db"

//物品表
typedef struct{
    int ArticleID;
    char ArticleName[50];
    int StorageID;
    int TypeID;
}Tbl_Article_Info;

//物品种类表
typedef struct{
    int TypeID;
    char TypeName[50];
}Tbl_Article_Type;

//视频历史记录表
typedef struct{
    int CameraID;
    int StorageID;
    char CameraPath[50];
    char CameraDate[30];
}Tbl_Camera_Info;

//设备控制表
typedef struct{
    int DeviceID;
    bool RFIDSet;
    bool AlarmSet;
    bool LedSet;
    bool BeepSet;
    int FanSet;
    int SegSet;
    bool IsSet;
}Tbl_Device_Control;

//设备上传历史记录表
typedef struct{
    int HistoryID;
    int DeviceID;
    char HistoryDate[30];
    float Temperature;
    float Humidity;
    float Luminosity;
    int Electricity;
    bool IsAlarm;
}Tbl_Device_History;

//设备表
typedef struct{
    int DeviceID;
    int StorageID;
    char DeviceName[50];
    char Identification[20];
    bool IsOnLine;
    bool IsAlarm;
}Tbl_Device_Info;

//设备参数表
typedef struct{
    int DeviceID;
    float MinTem;
    float MaxTem;
    float MinHum;
    float MaxHum;
    float MinLit;
    float MaxLit;
    int TimeSet;
    bool IsSet;
}Tbl_Device_Parameter;

//射频表
typedef struct{
    int RFID_ID;
    int ArticleID;
    char RFID[20];
}Tbl_RFID_Info;

//射频卡刷卡表
typedef struct{
    int RFID_HistoryID;
    int RFID_ID;
    char Date[30];
}Tbl_RFID_History;

//用户权限表
typedef struct{
    int RoleID;
    char RoleName[20];
}Tbl_Role_Info;

//仓库表
typedef struct{
    int StorageID;
    char StorageName[50];
    char StorageAddress[200];
}Tbl_Storage_Info;

//系统参数表
typedef struct{
    char key[20];
    char value[20];
}Tbl_System_Parameter;

//用户表
typedef struct{
    int UserID;
    char UserName[20];
    char Password[20];
    char NickName[50];
    int RoleID;
}Tbl_User_Info;

//联合结构体
typedef union {
    Tbl_Article_Info _Tbl_Article_Info;
    Tbl_Article_Type _Tbl_Article_Type;
    Tbl_Camera_Info _Tbl_Camera_Info;
    Tbl_Device_Control _Tbl_Device_Control;
    Tbl_Device_History _Tbl_Device_History;
    Tbl_Device_Info _Tbl_Device_Info;
    Tbl_Device_Parameter _Tbl_Device_Parameter;
    Tbl_RFID_Info _Tbl_RFID_Info;
    Tbl_Role_Info _Tbl_Role_Info;
    Tbl_Storage_Info _Tbl_Storage_Info;
    Tbl_System_Parameter _Tbl_System_Parameter;
    Tbl_User_Info _Tbl_User_Info;
    Tbl_RFID_History _Tbl_RFID_History;
}datetype;

//链表节点
typedef struct node{
    datetype *data;
    struct node *next;
}Node,*INode;

//链表
typedef struct {
    INode front;
    INode rear;
    int lengh;
}SqlQueue,*SqlLinkQueue;

//创建链表
SqlLinkQueue init_linkqueue();
//插入链表
bool in_linkqueue(SqlLinkQueue q,datetype *value);
//判断链表是否为空
bool is_empty_linkqueue(SqlLinkQueue q);
//取出链表
bool out_linkqueue(SqlLinkQueue q);
//释放链表资源
bool free_linkqueue(SqlLinkQueue q);


//创建数据库
sqlite3* connent_database();

//执行sql
bool exec_sql(char *sql);

//封装get_table
void my_get_table(int *pnColum_p, int *pnRow_p, char ***pazResult_p, char* sql);


#endif /* SqlHelper_Sqlite3_h */

