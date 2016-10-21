//
//  文件名：SqlHelper_Sqlite3.h
//  项目名称：物联仓储
//
//  Created by 张家铭 on 2016-10-19.
//  Copyright © 2016年 zjm. All rights reserved.
//


#include "SqlHelper_Sqlite3.h"


//创建数据库
sqlite3* connent_database(){
    sqlite3 *DB;
    int ret=sqlite3_open(DB_NAME, &DB);
    if (ret!=SQLITE_OK) {
        printf("%s\n",sqlite3_errmsg(DB));
    }
    return DB;
}

//执行sql
bool exec_sql(char *sql){
    sqlite3* DB=connent_database();
    if (!DB) return false;
    char *errmsg;
    int ret=sqlite3_exec(DB, sql, NULL, NULL, &errmsg);
    if (ret!=SQLITE_OK) {
        printf("%s\n",errmsg);
        sqlite3_close(DB);
        return false;
    }
    sqlite3_close(DB);
    return true;

}

void my_get_table(int *pnColum_p, int *pnRow_p, char ***pazResult_p, char* sql) {
    sqlite3* DB=connent_database();
    char *pzErrmsg;
    int ret=sqlite3_get_table(DB, sql, &(*pazResult_p), &(*pnRow_p), &(*pnColum_p), &pzErrmsg);
    if (ret!=SQLITE_OK) {
        printf("%s\n",pzErrmsg);
        sqlite3_free(pzErrmsg);
    }
    sqlite3_close(DB);
}

SqlLinkQueue init_linkqueue(){
    SqlLinkQueue q=(SqlLinkQueue)malloc(sizeof(SqlQueue));
    if (!q) {
        perror("malloc is fail");
        return NULL;
    }
    INode node=(INode)malloc(sizeof(Node));
    if (!node) {
        perror("malloc is fail");
        free(q);
        q=NULL;
        return NULL;
    }
    node->data=NULL;
    node->next=NULL;
    q->front=node;
    q->rear=node;
    q->lengh=0;
    return q;
}
bool in_linkqueue(SqlLinkQueue q,datetype *value){
    if (!q) {
        perror("queue is null");
        return false;
    }
    INode node=(INode)malloc(sizeof(Node));
    if (!node) {
        perror("malloc is fail");
        return false;
    }
    node->data=value;
    q->rear->next=node;
    q->rear=node;
    q->lengh++;
    return true;
}
bool is_empty_linkqueue(SqlLinkQueue q){
    return q->front==q->rear?true:false;
}
bool out_linkqueue(SqlLinkQueue q){
    if (!q) {
        perror("queue is null");
        return false;
    }
    if (is_empty_linkqueue(q)) {
        perror("queue is empty");
        return false;
    }
    INode p=q->front->next;
    if (p==q->rear) {
        q->rear=q->front;
    }else{
        q->front->next=q->front->next->next;
    }
    free(p->data);
    p->data=NULL;
    free(p);
    p=NULL;
    q->lengh--;
    return true;
}

bool free_linkqueue(SqlLinkQueue q){
    if (!q) {
        perror("queue is null");
        return false;
    }
    while (!is_empty_linkqueue(q)) {
        out_linkqueue(q);
    }
    free(q->front);
    q->front=NULL;
    q->rear=NULL;
    free(q);
    q=NULL;
    return true;
    
}
