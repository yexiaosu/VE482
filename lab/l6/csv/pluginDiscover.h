//
// Created by lanwang on 11/2/21.
//

#ifndef CSV_PLUGINDISCOVER_H
#define CSV_PLUGINDISCOVER_H

#include "pluginManager.h"

typedef struct pluginHandleNode_t {
    void *handle;
    struct pluginHandleNode_t *next;
} pluginHandleNode;

typedef struct pluginHandleList_t {
    pluginHandleNode *list;
} pluginHandleList;

pluginHandleList *newHandleList();

void freeHandleList(pluginHandleList *handleList);

typedef int(*fileTypePlugin)(pluginManager *);

pluginHandleList *discover(char *dirName, pluginManager *pm);

#endif //CSV_PLUGINDISCOVER_H
