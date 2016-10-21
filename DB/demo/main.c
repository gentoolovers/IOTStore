//
//  main.c
//  SqliteTest
//
//  Created by 张家铭 on 16/10/12.
//  Copyright © 2016年 zjm. All rights reserved.
//

#include <stdio.h>
#include "Tbl_User_InfoDAL.h"

void add_test(void) {
    Tbl_User_Info user;
    puts("增加一个用户test1，密码test1，RoleID=2，昵称：test1");
    user=Tbl_User_InfoInit(0,"test1", "test1", 2, "test1");
    if(Tbl_User_InfoAdd(user)){
        puts("添加成功");
    }else{
        puts("添加失败");
    }
    puts("增加一个用户test2，密码test2，RoleID=2，昵称：test2");
    user=Tbl_User_InfoInit(0,"test2", "test2", 2, "test2");
    if(Tbl_User_InfoAdd(user)){
        puts("添加成功");
    }else{
        puts("添加失败");
    }
}

void deleted_test(void) {
    puts("****************");
    puts("删除test1用户！");
    if (Tbl_User_InfoDelete(" and UserName='test1'")) {
        puts("删除成功");
    }else{
        puts("删除失败");
    }
}

void findsingle_test(void) {
    puts("**************");
    puts("查询单条用户名为test2的用户");
    Tbl_User_Info user=Tbl_User_InfoFindSingle(" and UserName='test2'");
    printf("查询结果UserID=%d,UserName=%s,Password=%s,RoleID=%d,NickName=%s\n",user.UserID,user.UserName,user.Password,user.RoleID,user.NickName);
}

void extracted_function(void) {
    puts("**************");
    puts("修改用户test2，为test3");
    Tbl_User_Info user=Tbl_User_InfoFindSingle(" and UserName='test2'");
    strcpy(user.UserName, "test3");
    if (Tbl_User_InfoModify(user)) {
        puts("修改成功");
    }else{
        puts("修改失败");
    }
}

void find_test(void) {
    puts("**************");
    puts("查找表Tbl_User_Info");
    SqlLinkQueue list=init_linkqueue();
    Tbl_User_InfoFind(list, " ");
    INode p=list->front;
    while (p!=list->rear) {
        p=p->next;
        Tbl_User_Info user=p->data->_Tbl_User_Info;
        printf("%d %s %s %d %s\n",user.UserID,user.UserName,user.Password,user.RoleID,user.NickName);
    }
    free_linkqueue(list);
}

void findpage_test(void) {
    puts("***************");
    puts("分页查找UserID排序，每页2条，第二页");
    SqlLinkQueue list=init_linkqueue();
    Tbl_User_InfoFindPage(list, " ", " order by UserID", 2, 2);
    INode p=list->front;
    
    while (p!=list->rear) {
        p=p->next;
        Tbl_User_Info user=p->data->_Tbl_User_Info;
        printf("%d %s %s %d %s\n",user.UserID,user.UserName,user.Password,user.RoleID,user.NickName);
    }
    free_linkqueue(list);
}

void totalpage_test(void) {
    puts("*************");
    puts("获取总页数，每页2条");
    int iTotalPage=Tbl_User_InfoGetTotalPageCount(" ", 2);
    printf("总页数：%d\n",iTotalPage);
}

int main(int argc, const char * argv[]) {
//    测试增加
    puts("数据库测试模块！");
    puts("Tbl_User_Info表");
    add_test();
    deleted_test();
    findsingle_test();
    extracted_function();
    find_test();
    findpage_test();
    totalpage_test();
   
    return 0;
}
