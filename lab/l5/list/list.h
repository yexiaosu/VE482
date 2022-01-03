//
// Created by lanwang on 10/25/21.
//

#ifndef H3_LIST_H
#define H3_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab5_dlist.h"

typedef struct Node {
    char *key;
    void *val;
    struct Node *next;
} node;

typedef struct List {
    node *preHead;
    int size;
    dlistValueType dataType;
} list;

list *createList(dlistValueType dataType);

void deleteList(list *target);

void clearList(list *target);

void insert(list *target, const char *key, dlistValue *val);

int strCmp(const void *a, const void *b, dlistSortMethod sortType);

int intCmp(const void *a, const void *b, dlistSortMethod sortType);

int doubleCmp(const void *a, const void *b, dlistSortMethod sortType);

void copyList(const list *src, list *target);

void sortList(list *target, dlistSortMethod sortType);

void printList(const list *src);

int emptyList(const list *src);

#endif //H3_LIST_H
