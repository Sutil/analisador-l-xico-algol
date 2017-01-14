//
// Created by Lucas on 1/10/2017.
//

#ifndef PROJETOU_CONTROLEDETABELA_H
#define PROJETOU_CONTROLEDETABELA_H

#include "table.h"
#include "util.h"

/*
 * symbol.h - Symbols and symbol-tables
 *
 */

typedef struct S_symbol_ *S_symbol;

struct S_symbol_ {
    _string name;
    S_symbol next;
};

/* Make a unique symbol from a given _string.
 *  Different calls to S_Symbol("foo") will yield the same S_symbol
 *  value, even if the "foo" strings are at different locations. */
S_symbol S_Symbol(_string);

/* Extract the underlying _string from a symbol */
_string S_name(S_symbol);

/* S_table is a mapping from S_symbol->any, where "any" is represented
 *     here by void*  */
typedef struct TAB_table_ *S_table;

/* Make a new table */
S_table S_empty(void);

/* Enter a binding "sym->value" into "t", shadowing but not deleting
 *    any previous binding of "sym". */
void S_enter(S_table t, S_symbol sym, void *value);

/* Look up the most recent binding of "sym" in "t", or return NULL
 *    if sym is unbound. */
void *S_look(S_table t, S_symbol sym);

/* Start a new "scope" in "t".  Scopes are nested. */
void S_beginScope(S_table t);

/* Remove any bindings entered since the current scope began,
   and end the current scope. */
void S_endScope(S_table t);

#endif //PROJETOU_CONTROLEDETABELA_H
