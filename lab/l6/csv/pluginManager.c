//
// Created by lanwang on 11/2/21.
//

#include <stdlib.h>
#include <string.h>
#include "pluginManager.h"

pluginManager *newManager() {
    pluginManager *m = malloc(sizeof(pluginManager));
    m->hook_list = NULL;
    return m;
}

void freeManager(pluginManager *m) {
    struct hookList_t *node = m->hook_list;
    while (node) {
        struct hookList_t *next = node->next;
        free(node->type);
        free(node);
        node = next;
    }
    free(m);
}

void registerHook(pluginManager *m, char *type, hook_t hook) {
    struct hookList_t *node = malloc(sizeof(struct hookList_t));
    node->type = strdup(type);
    node->hook = hook;
    node->next = m->hook_list;
    m->hook_list = node;
}

int applyHook(pluginManager *pm, char *type, char *fileName, int dataType, int order) {
    hookList *pluginTypeList = pm->hook_list;
    while (pluginTypeList != NULL) {
        if (strcmp(type, pluginTypeList->type) == 0) {
            return pluginTypeList->hook(fileName, type, dataType, order);
        } else {
            pluginTypeList = pluginTypeList->next;
        }
    }
    return 0;
}
