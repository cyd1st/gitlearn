#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

// 定义hash结构体。key为int，value为char[]
struct my_struct {
    int id;
    char name[20];
    UT_hash_handle hh;
};

// 定义哈希表头
struct my_struct *users = NULL;

// 定义添加元素函数
void add_user(const int user_id, char *name)
{
    struct my_struct *s; // 用来存放新添加的数据
    HASH_FIND_INT(users, &user_id, s); // 注意：这里传int需要指针，这点可能容易忘记。应该是为了能和string使用同一套代码
    // 如果key不存在，新建并添加元素
    if (s == NULL) {
        s = (struct my_struct *)malloc(sizeof(struct my_struct));
        if (s == NULL) {
            // 申请内存失败直接退出
            fprintf(stderr, "malloc failed.\n");
            exit(EXIT_FAILURE);
        }
        s->id = user_id;
        HASH_ADD_INT(users, id, s); // 注意：这里的id是指结构体中表示key的字段名，不是变量名
    }
    // 更新值
    strncpy(s->name, name, sizeof(s->name) - 1);
    s->name[sizeof(s->name)-1] = '\0';
}

void delete_all()
{
    struct my_struct *cur, *tmp;

    HASH_ITER(hh, users, cur, tmp)
    {
        HASH_DEL(users, cur);
        free(cur);
    }
}

void print_all()
{
    struct my_struct *s;

    for (s = users; s != NULL; s = s->hh.next) {
        printf("id: %d - name: %s\n", s->id, s->name);
    }
}


int cmp_name(struct my_struct *a, struct my_struct *b)
{
    return strcmp(b->name, a->name);
}
void sort_by_name()
{
    HASH_SORT(users, cmp_name);
}

