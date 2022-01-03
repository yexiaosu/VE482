//
// Created by lanwang on 11/2/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <dlfcn.h>
#include <stdint.h>
#include "pluginDiscover.h"

pluginHandleList *newHandleList() {
    pluginHandleList *handleList = malloc(sizeof(pluginHandleList));
    handleList->list = NULL;
    return handleList;
}

void freeHandleList(pluginHandleList *handleList) {
    if (handleList == NULL) {
        return;
    } else {
        pluginHandleNode *tmp = handleList->list;
        while (tmp != NULL) {
            pluginHandleNode *next = tmp->next;
            dlclose(tmp->handle);
            free(tmp);
            tmp = next;
        }
        free(handleList);
    }
}

void *registerPlugin(char *fileName, char *pluginName, pluginManager *pm) {
    char *path = malloc(sizeof(char *) * (strlen(pluginName) + 10));
    strcpy(path, "./");
    strcat(path, fileName);

    // Attempt to open the plugin
    void *handle = dlopen(path, RTLD_NOW); // There is no dependency between the plugins
    free(path);
    if (!handle) {
        fprintf(stderr, "Cannot load plugin: %s\n", dlerror());
        return NULL;
    }

    // Attempt to find the function and then call it
    char *funcName = malloc(sizeof(char *) * (strlen(pluginName) + 5));
    strcpy(funcName, pluginName);

    // Register the function
    fileTypePlugin fileTypeFunc = (fileTypePlugin) (intptr_t) dlsym(handle, funcName);
    if (!fileTypeFunc) {
        fprintf(stderr, "Cannot load register function: %s\n", dlerror());
        exit(-1);
    }
    fileTypeFunc(pm);
    free(funcName);
    return handle;
}

pluginHandleList *discover(char *dirName, pluginManager *pm) {
    // Go through the directory to find all .so files
    DIR *dir;
    struct dirent *dp;
    pluginHandleList *handleList = newHandleList(); // Use a list to close handles one by one
    dir = opendir(dirName);
    if (!dir) {
        fprintf(stderr, "Cannot open: %s\n", dirName);
        return NULL;
    }

    while ((dp = readdir(dir)) != NULL) {
        char *dot = strrchr(dp->d_name, '.');
        if (!dot || strcmp(dot, ".so") != 0) { // not .so file
            continue;
        }
        *dot = '\0';
        char *pluginName = malloc(sizeof(char *));
        strcpy(pluginName, dp->d_name); // get pluginName, which equals the register function name
        *dot = '.';
        if (!pluginName)
            continue;
        // Register the plugin, get the handle and add it to the handle list
        void *pluginHandle = registerPlugin(dp->d_name, pluginName, pm);
        if (pluginHandle) {
            pluginHandleNode *newPluginHandleNode = malloc(sizeof(pluginHandleNode));
            newPluginHandleNode->handle = pluginHandle;
            newPluginHandleNode->next = handleList->list;
            handleList->list = newPluginHandleNode;
        }
        free(pluginName);
    }
    closedir(dir);
    if (handleList->list != NULL)
        return handleList;
    else {
        free(handleList);
        return NULL;
    }
}
