#include <stdio.h>
#include "address_list.h"

#define MAXSIZE 100          /*符号常量，通讯录中最多记录个数*/

/*定义全局变量*/
struct Record  AddressList[MAXSIZE];  /*定义通讯录数组*/
struct nodeAddressList ListHead;      /*定义通讯录链表*/
int TotalNum;                         /*通讯录条目总数*/
int count=0;                          /*count为计数器，记录当前正在处理的记录个数*/
int saveflag=0;                       /*是否需要存盘的标志变量*/

void isExit(int *choice);

int main() {
    int choice;   /* choice变量用于保存用户对功能菜单的选择结果*/
    init();      /*程序开始运行时，首先把存放在外存中的学生信息读入内存*/
    // Show( ); exit(0);  // test
    SET_CT_BG_WHITE(); // 设置终端背景为白色

    /*---------------------------主菜单界面-----------------------*/
    do{
        CLEAR_SCREAN();
        printf("\n*************************************************");
        printf("\n*************************************************");
        printf("\n**       ################################      **");
        printf("\n**       ###欢迎使用员工通讯录管理系统###      **");
        printf("\n**       ###########Total: %03d###########      **", TotalNum);
        printf("\n**                                             **");
        printf("\n**            1.Read    （浏览记录）           **");
        printf("\n**            2.Append  （追加记录）           **");
        printf("\n**            3.Insert  （插入记录）           **");
        printf("\n**            4.Delete  （删除记录）           **");
        printf("\n**            5.Update  （修改记录）           **");
        printf("\n**            6.Search  （查询记录）           **");
        printf("\n**            7.Sort    （记录排序）           **");
        printf("\n**            8.Total   （统计记录）           **");
        printf("\n**            9.Save    （保存记录）           **");
        printf("\n**            0.Exit    （退出程序）           **");
        printf("\n**                                             **");
        printf("\n*************************************************");
        printf("\n*************************************************");
        printf("\n");
        printf("            请选择要执行的操作(0～9):");
        scanf("%d", &choice);
        while (choice <0 || choice >9)       /*判断输入数据*/
        {   printf("数据有误，请重新输入：");
            scanf("%d",&choice);
        }
        switch (choice) /*选择功能*/
        {
            case 1:Show( ); isExit(&choice); break;
            case 2:Append( );break;
            case 3:Append( );break;
            case 4:Delete( );break;
            case 5:Update( );break;
            case 6:Search( );break;
            case 7:Sort( );break;
            case 8:Total( );break;
            case 9:Save( );break;
        }
        while ( getchar( ) != '\n' );   /*为了避免下次输入出错，需要清除键盘缓冲区*/
        printf("choice = %d\n", choice);
    } while(choice!=0);
    printf("您选择了退出系统！！！\n");
    Save();                            /*程序执行完毕时，保存内存的学生信息到外存文件*/
    printf("谢谢使用本系统，再见！\n");
    printf("按任意键退出");
    getchar( );                         /*让屏幕暂停*/
    return 0;
}

void isExit(int *choice)
{
    char c;
    printf("\n是否继续[Y/n]: ");
    while ( getchar( ) != '\n' );
    scanf("%c", &c);
    if (c == 'Y' || c == 'y') return;
    *choice = 0;
}