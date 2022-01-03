//
// Created by lanwang on 10/18/21.
//

#ifndef H3_LIST_H
#define H3_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024

#define ERR -1

#define CHARTYPE 0
#define INTTYPE 1
#define DOUBLETYPE 2

#define RANDOM 0
#define INCREASING 1
#define DECREASING 2

typedef struct Node {
    char *key;
    void *val;
    struct Node *next;
} node;

typedef struct List {
    node *preHead;
    int size;
} list;

list *createList(void);

void deleteList(list *target);

void insert(list *target, char *key, char *val, int dataType);

int strCmp(const void *a, const void *b, int sortType);

int intCmp(const void *a, const void *b, int sortType);

int doubleCmp(const void *a, const void *b, int sortType);

void sortList(list *src,int dataType, int (*cmp)(const void *, const void *, int));

void readData(list *target, char *fileName, int dataType);

void writeData(list *src, char *fileName, int dataType);

#endif //H3_LIST_H
