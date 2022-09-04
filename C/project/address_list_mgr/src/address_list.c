/*员工通讯录管理系统C语言源代码addresslist.c*/
#include <stdio.h>           /*标准输入/输出函数库*/
#include <stdlib.h>          /*标准函数库*/
#include <string.h>          /*字符串函数库*/
#include <unistd.h>
#include <limits.h>
#include "address_list.h"

#define PER_INFO_LEN 1024
#define RELATIVE_PATH_LEN 128

/* 获取记录的最大长度 */
#define CHANGE_COL_LEN(new, cur) do {if (new > cur) cur = new;} while (0)
/* 打印分隔横线（部分） */
#define PRINT_HOR_LINE(len) do {    \
    for (int i = 0; i < len; i++) { \
        printf("-");                \
    }                               \
    printf("+"); } while (0)

const char NUMBER[] = "number";
const char NAME[]   = "name";
const char DEPARTMENT[] = "department";
const char POSITION[] = "position";
const char OFFICE_TEL[] = "officetelephone";
const char MOBILE_TEL[] = "mobiletelephone";
const char EMAIL[] = "email";
const char QQ[] = "QQ";

/* 输出表格每一列的长度 */
int numberColLen;
int nameColLen;
int departmentColLen;
int positionColLen;
int officeTelColLen;
int mobileTelColLen;
int emailColLen;
int qqColLen;

extern struct nodeAddressList ListHead;      /*定义通讯录链表*/
extern int TotalNum;                         /*通讯录条目总数*/

/* 初始化每一列的长度 */
void InitItermColLen()
{
    numberColLen = sizeof(NUMBER) - 1;
    nameColLen = sizeof(NAME) - 1;
    departmentColLen = sizeof(DEPARTMENT) - 1;;
    positionColLen = sizeof(POSITION) - 1;;
    officeTelColLen = sizeof(OFFICE_TEL) - 1;;
    mobileTelColLen = sizeof(MOBILE_TEL) - 1;;
    emailColLen = sizeof(EMAIL) - 1;;
    qqColLen = sizeof(QQ) - 1;;
}

/* 初始化函数 */
void init( )
{
    char curPath[PATH_MAX];
    char dataPath[PATH_MAX + RELATIVE_PATH_LEN] = {0};
    char perInfo[PER_INFO_LEN] = {0};
    char *dataDir = "data";
    char *fileName = "list1.txt";
    size_t curPathLen, infoLen;

    getcwd(curPath, PATH_MAX);
    curPathLen = strlen(curPath);
    sprintf(dataPath, "%s/%s/%s", curPath, dataDir, fileName);
    FILE *fp = fopen(dataPath, "r");
    struct nodeAddressList *cur = &ListHead;
    TotalNum = 0;

    InitItermColLen();

    while (fgets(perInfo, PER_INFO_LEN, fp)) {
        infoLen = strlen(perInfo);
        if (perInfo[infoLen - 1] == '\n') {
            perInfo[infoLen - 1] = '\0';
        }
        struct nodeAddressList *node = NULL;
        node = malloc(sizeof(struct nodeAddressList));
        if (node == NULL) {
            printf("%s: malloc failed.\n", __FUNCTION__);
            exit(-1);
        }

        sscanf(perInfo, "%s %s %s %s %s %s %s %s", node->record.number,
               node->record.name, node->record.department,
               node->record.position, node->record.officetelephone, 
               node->record.mobiletelephone, 
               node->record.email, node->record.QQ);
        cur->next = node;
        cur = cur->next;
        cur->next = NULL;
        TotalNum++;

        CHANGE_COL_LEN(strlen(node->record.number), numberColLen);
        if ((numberColLen - strlen(NUMBER)) % 2) numberColLen++;
        CHANGE_COL_LEN(strlen(node->record.name), nameColLen);
        if ((nameColLen - strlen(NAME)) % 2) nameColLen++;
        CHANGE_COL_LEN(strlen(node->record.department), departmentColLen);
        if ((departmentColLen - strlen(DEPARTMENT)) % 2) departmentColLen++;
        CHANGE_COL_LEN(strlen(node->record.position), positionColLen);
        if ((positionColLen - strlen(POSITION)) % 2) positionColLen++;
        CHANGE_COL_LEN(strlen(node->record.officetelephone), officeTelColLen);
        if ((officeTelColLen - strlen(OFFICE_TEL)) % 2) officeTelColLen++;
        CHANGE_COL_LEN(strlen(node->record.mobiletelephone), mobileTelColLen);
        if ((mobileTelColLen - strlen(MOBILE_TEL)) % 2) mobileTelColLen++;
        CHANGE_COL_LEN(strlen(node->record.email), emailColLen);
        if ((emailColLen - strlen(EMAIL)) % 2) emailColLen++;
        CHANGE_COL_LEN(strlen(node->record.QQ), qqColLen);
        if ((qqColLen - strlen(QQ)) % 2) qqColLen++;
    }
}

/* 打印分隔横线 */
void PrintHorizontalLines()
{
    printf("+");
    PRINT_HOR_LINE(numberColLen + 2);
    PRINT_HOR_LINE(nameColLen + 2);
    PRINT_HOR_LINE(departmentColLen + 2);
    PRINT_HOR_LINE(positionColLen + 2);
    PRINT_HOR_LINE(officeTelColLen + 2);
    PRINT_HOR_LINE(mobileTelColLen + 2);
    PRINT_HOR_LINE(emailColLen + 2);
    PRINT_HOR_LINE(qqColLen + 2);
    printf("\n");
}

/* 打印每一列的名字 */
#define PRINT_COL_NAME(len, name) do {                           \
        printf("| ");                                            \
        for (int i = 0; i < (len - sizeof(name) + 1) / 2; i++) { \
            printf(" ");                                         \
        }                                                        \
        printf(name);                                          \
        for (int i = 0; i < (len - sizeof(name) + 1) / 2; i++) { \
            printf(" ");                                         \
        }                                                        \
        printf(" ");                                             \
    } while (0)

/* 打印标题行 */
void PrintTitleLine()
{
    PRINT_COL_NAME(numberColLen, NUMBER);
    PRINT_COL_NAME(nameColLen, NAME);
    PRINT_COL_NAME(departmentColLen, DEPARTMENT);
    PRINT_COL_NAME(positionColLen, POSITION);
    PRINT_COL_NAME(officeTelColLen, OFFICE_TEL);
    PRINT_COL_NAME(mobileTelColLen, MOBILE_TEL);
    PRINT_COL_NAME(emailColLen, EMAIL);
    PRINT_COL_NAME(qqColLen, QQ);
    printf("|\n");
}

/* 打印指定长度的指定字符 */
#define PrintSomeChar(ch, num) do {     \
        for (int i = 0; i < num; i++) { \
            printf("%c", ch);           \
        }                               \
    } while (0)

/* 打印一行数据 */
void PrintInstanceLine(struct Record *r)
{
    printf("| %s ", r->number); PrintSomeChar(' ', numberColLen - strlen(r->number));
    printf("| %s ", r->name); PrintSomeChar(' ', nameColLen - strlen(r->name));
    printf("| %s ", r->department); PrintSomeChar(' ', departmentColLen - strlen(r->department));
    printf("| %s ", r->position); PrintSomeChar(' ', positionColLen - strlen(r->position));
    printf("| %s ", r->officetelephone); PrintSomeChar(' ', officeTelColLen - strlen(r->officetelephone));
    printf("| %s ", r->mobiletelephone); PrintSomeChar(' ', mobileTelColLen - strlen(r->mobiletelephone));
    printf("| %s ", r->email); PrintSomeChar(' ', emailColLen - strlen(r->email));
    printf("| %s ", r->QQ); PrintSomeChar(' ', qqColLen - strlen(r->QQ));
    printf("|\n");
}

/* 读取通讯录并输出表格 */
void Show( )
{
    // printf("nameColLen = %d\n", nameColLen);
	PrintHorizontalLines();
    PrintTitleLine();
    PrintHorizontalLines();
    struct nodeAddressList *cur = ListHead.next;
    while (cur != NULL) {
        PrintInstanceLine(&cur->record);
        cur = cur->next;
    }
    PrintHorizontalLines();
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
