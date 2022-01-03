//
// Created by lanwang on 11/2/21.
//

#ifndef CSV_PLUGINMANAGER_H
#define CSV_PLUGINMANAGER_H

typedef int (*hook_t)(char *, char *, int, int);

struct hookList_t {
    char* type;
    hook_t hook;
    struct hookList_t *next;
};

struct manager_t {
    struct hookList_t *hook_list;
};

typedef struct hookList_t hookList;
typedef struct manager_t pluginManager;

pluginManager *newManager();

void freeManager(pluginManager *m);

void registerHook(pluginManager *m, char* type, hook_t hook);

int applyHook(pluginManager *pm, char* type, char* fileName, int dataType, int order);

#endif //CSV_PLUGINMANAGER_H
