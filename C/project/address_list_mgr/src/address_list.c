/*员工通讯录管理系统C语言源代码addresslist.c*/
#include <stdio.h>           /*标准输入/输出函数库*/
#include <stdlib.h>          /*标准函数库*/
#include <string.h>          /*字符串函数库*/
#include <unistd.h>
#include <limits.h>
#include "address_list.h"

#define PER_INFO_LEN 1024
/*自定义函数定义*/
void init( )
{
    char curPath[PATH_MAX] = {0};
    char dataPath[PATH_MAX] = {0};
    char perInfo[PER_INFO_LEN] = {0};
    char *dataDir = "data";
    char *fileName = "list1.txt";

    getcwd(curPath, PATH_MAX);
    size_t curPathLen = strlen(curPath);
    sprintf(dataPath, "%s/%s/%s", curPath, dataDir, fileName);
    
    FILE *fp = fopen(dataPath, "r");
    fgets(perInfo, PER_INFO_LEN, fp);
    // printf("perInfo : %s\n", perInfo);
}
void Show( )
{ 
	/* ……（代码略）*/	
}

void Append( ) {
	/* ……（代码略）*/
}
void Insert( ) {
	/* ……（代码略）*/
}
void Delete( ) {
	/* ……（代码略）*/
}
void Update( ) {
	/* ……（代码略）*/
}
void Search( ) {
	/* ……（代码略）*/
}
void Total( ) {
	/* ……（代码略）*/
}
void Sort( ) {
	/* ……（代码略）*/
}
void Save( ) {
	/* ……（代码略）*/
}
