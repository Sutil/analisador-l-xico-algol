//
// Created by Lucas on 1/10/2017.
//

#ifndef PROJETOU_UTIL_H
#define PROJETOU_UTIL_H

#include <assert.h>
#include <stdio.h>

typedef char *_string;
typedef char _bool;

#define TRUE 1
#define FALSE 0


void *checked_malloc(int);
_string String(char *);

typedef struct U_boolList_ *U_boolList;
struct U_boolList_ {
    _bool head;
    U_boolList tail;
};
U_boolList U_BoolList(_bool head, U_boolList tail);
int max(int a, int b);

char *remove_ext (char* mystr, char dot, char sep) ;

void indent(FILE *out, int d) ;

#endif //PROJETOU_UTIL_H
