#ifndef __ADDRESS_LIST_H__
#define __ADDRESS_LIST_H__

#include <stdlib.h>

#ifdef __WIN32__

#define CLEAR_SCREAN() do {system("cls");} while (0)
#define SET_CT_BG_WHITE() do {system("color F0");} while (0)

#elif defined (__linux__)

#define CLEAR_SCREAN() do {system("clear");} while (0)
#define SET_CT_BG_WHITE() do { \
    printf("\033[47m\n");      \
} while (0)

#endif // __WIN32__

struct Record{               /*员工通讯信息结构体*/
    char number[10];             /*员工编号*/
    char name[11];               /*员工姓名*/
    char department[20] ;        /*所属部门*/
    char position[20] ;          /*职务/岗位*/
    char office_telephone[12] ;  /*座机*/
    char mobile_telephone[12] ;  /*移动电话*/
    char email[30] ;             /*电子邮箱*/
    char QQ[12];                 /*工作QQ*/
};

/*自定义函数原型说明*/
void init( );     /*初始化操作*/
void Show( );     /*浏览记录*/
void Append( );   /*添加记录*/
void Insert( );   /*插入记录*/
void Delete( );   /*删除记录*/
void Update( );   /*修改记录*/
void Search( );   /*查询记录*/
void Total( );    /*统计记录*/
void Sort( );     /*记录排序*/
void Save( );     /*保存记录*/

#endif // __ADDRESS_LIST_H__