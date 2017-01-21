#ifndef __UTIL_H
#define __UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <assert.h>
#include <stdio.h>

typedef char* string_;
typedef char bool;

#define TRUE 1
#define FALSE 0

void *checked_malloc(int);
string_ String(char *);

typedef struct U_boolList_ *U_boolList;
struct U_boolList_ {
    char head;
    U_boolList tail;
};
U_boolList U_BoolList(char head, U_boolList tail);
int max(int a, int b);

char *remove_ext (char* mystr, char dot, char sep) ;

void indent(FILE *out, int d) ;

#ifdef __cplusplus
};
#endif

#endif

