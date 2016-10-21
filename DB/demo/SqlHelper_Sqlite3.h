//
//  SqlHelper_Sqlite3.h
//  SqliteTest
//
//  Created by 张家铭 on 16/10/12.
//  Copyright © 2016年 zjm. All rights reserved.
//

#ifndef SqlHelper_Sqlite3_h
#define SqlHelper_Sqlite3_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <sqlite3.h>

#define DB_NAME "QMSSLSJ.db"

typedef struct{
    int ArticleID;
    char ArticleName[50];
    int StorageID;
    int TypeID;
}Tbl_Article_Info;

typedef struct{
    int TypeID;
    char TypeName[50];
}Tbl_Article_Type;

typedef struct{
    int CameraID;
    int StorageID;
    char CameraPath[50];
    char CameraData[30];
}Tbl_Camera_Info;

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

typedef struct{
    int HistoryID;
    int DeviceID;
    char HistoryDate[30];
    float Temperature;
    float Humidity;
    float Luminosity;
    int Electricity;
}Tbl_Device_History;

typedef struct{
    int DeviceID;
    int StorageID;
    char DeviceName[50];
    char Identification[20];
    bool IsOnLine;
}Tbl_Device_Info;

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

typedef struct{
    int RFID_ID;
    int ArticleID;
    char RFID[20];
}Tbl_RFID_Info;

typedef struct{
    int RoleID;
    char RoleName[20];
}Tbl_Role_Info;

typedef struct{
    int StorageID;
    char StorageName[50];
    char StorageAddress[200];
}Tbl_Storage_Info;

typedef struct{
    char key[20];
    char value[20];
}Tbl_System_Parameter;

typedef struct{
    int UserID;
    char UserName[20];
    char Password[20];
    char NickName[50];
    int RoleID;
}Tbl_User_Info;


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
}datetype;

typedef struct node{
    datetype *data;
    struct node *next;
}Node,*INode;

typedef struct {
    INode front;
    INode rear;
    int lengh;
}SqlQueue,*SqlLinkQueue;

SqlLinkQueue init_linkqueue();
bool in_linkqueue(SqlLinkQueue q,datetype *value);
bool is_empty_linkqueue(SqlLinkQueue q);
bool out_linkqueue(SqlLinkQueue q);
bool free_linkqueue(SqlLinkQueue q);


//创建数据库
sqlite3* connent_database();

//执行sql
bool exec_sql(char *sql);

//封装get_table
void my_get_table(int *pnColum_p, int *pnRow_p, char ***pazResult_p, char* sql);


#endif /* SqlHelper_Sqlite3_h */
