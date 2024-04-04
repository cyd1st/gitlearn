#include <stdio.h>
#include <stdalign.h>

#define STR_VAL(x) #x
#define PRINT_ALIGN(x) do { \
    printf("sizeof(%s) = %u\t", STR_VAL(x), sizeof(x)); \
    printf("alignof(%s) = %u\n", STR_VAL(x), alignof(x)); \
} while (0)

int main() {
    typedef struct T {
        char a;
        double b;
        char c;
        int d;
    } test;
    PRINT_ALIGN(test);

#pragma pack(push, 2)
    typedef struct T1 {
        char a;
        double b;
        char c;
        int d;
    } test1;
#pragma pack(pop)
    PRINT_ALIGN(test1);

    typedef struct T2 {
        char a;
        double b;
        char c;
        int d;
    } __attribute__((aligned(16))) test2;
    PRINT_ALIGN(test2);

#pragma pack(push, 2)
    typedef struct T3 {
        char a;
        double b;
        char c;
        int d;
    } __attribute__((aligned(32))) test3;
#pragma pack(pop)
    PRINT_ALIGN(test3);

#pragma pack(push, 4)
    typedef struct T4 {
        char a;
        double b;
        char c;
        int d;
    } __attribute__((aligned(2))) test4;
#pragma pack(pop)
    PRINT_ALIGN(test4);

#pragma pack(push, 2)
    typedef struct T5 {
        char a;
        double b;
        char c;
        int d;
    } __attribute__((aligned(4))) test5;
#pragma pack(pop)
    PRINT_ALIGN(test5);

    return 0;
}