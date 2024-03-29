/*
 * table.c - Functions to manipulate generic tables.
 * Copyright (c) 1997 Andrew W. Appel.
 */

#include <stdio.h>
#include "util.h"
#include "table.h"

#define TABSIZE 127

typedef struct binder_ *binder;
struct binder_ {void *key; int value; int scope; binder next; void *prevtop;};
struct TAB_table_ {
    binder table[TABSIZE];
    void *top;
};


static binder Binder(void *key, int value, int scope, binder next, void *prevtop) {
    binder b = checked_malloc(sizeof(*b));
    b->key = key; 
    b->value=value; 
    b->scope=scope;
    b->next=next; 
    b->prevtop = prevtop; 
    return b;
}

/********************************************************
 * create an empty table, when creating a new function
 ********************************************************/
TAB_table TAB_empty(void) {
    TAB_table t = checked_malloc(sizeof(*t));
    int i;
    t->top = NULL;
    for (i = 0; i < TABSIZE; i++)
     t->table[i] = NULL;
    return t;
}

/* The cast from pointer to integer in the expression
 *   ((unsigned)key) % TABSIZE
 * may lead to a warning message.  However, the code is safe,
 * and will still operate correctly.  This line is just hashing
 * a pointer value into an integer value, and no matter how the
 * conversion is done, as long as it is done consistently, a
 * reasonable and repeatable index into the table will result.
 */

/********************************************************
 * create a new binding for the symbol;
 ********************************************************/
void TAB_enter(TAB_table t, void *key, int value, int scope) {
    int index;
    assert(t && key);
    index = ((unsigned)key) % TABSIZE;
    t->table[index] = Binder(key, value, scope, t->table[index], t->top);
    t->top = key;
}
/******************************************************
 * always return the one that's the first
 * that's the one in the current environment
 ******************************************************/
int TAB_look(TAB_table t, void *key) {
    int index;
    binder b;
    assert(t && key);
    index=((unsigned)key) % TABSIZE;
    for(b=t->table[index]; b; b=b->next)
        if (b->key==key) return b->value;
    return -1;
}
/********************************************************
 * pop the symbol and its related binding
 ********************************************************/
void *TAB_pop(TAB_table t) {
    void *k; binder b; int index;
    assert (t);
    k = t->top;
    assert (k);
    index = ((unsigned)k) % TABSIZE;
    b = t->table[index];
    assert(b);
    t->table[index] = b->next;
    t->top=b->prevtop;
    return b->key;
}

int TAB_scope(TAB_table t, void *key, int scope) {
    int index;
    binder b;
    assert(t && key);
    index=((unsigned)key) % TABSIZE;
    for(b=t->table[index]; b; b=b->next)
        if (b->key==key && b->scope==scope) return 0;
    return 1;
}
