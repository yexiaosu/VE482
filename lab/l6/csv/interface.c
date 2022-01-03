//
// Created by lanwang on 10/18/21.
//

#include "logic.h"
#include "pluginDiscover.h"
#include <time.h>

int getDataType(char *fileName) {
    char arg[80] = {'\0'};
    strcpy(arg, fileName);
    char *dataType;
    dataType = strtok(arg, "_.");
    dataType = strtok(NULL, "_.");
    if (!strcmp(dataType, "char*")) {
        return CHARTYPE;
    } else if (!strcmp(dataType, "int")) {
        return INTTYPE;
    } else if (!strcmp(dataType, "double")) {
        return DOUBLETYPE;
    } else {
        return ERR;
    }
}

int getSortType(char *arg) {
    if (!strcmp(arg, "rand")) {
        return RANDOM;
    } else if (!strcmp(arg, "dec")) {
        return DECREASING;
    } else if (!strcmp(arg, "inc")) {
        return INCREASING;
    } else {
        return ERR;
    }
}

int dispatchCmd(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Input format is not correct.");
        return -1;
    }
    srand((unsigned int) time(NULL));
    pluginManager *manager = newManager();
    pluginHandleList *handleList = discover(".", manager);
    char *fileName = argv[1];
    char *sortTypeStr = argv[2];
    int dataType = getDataType(fileName);
    int sortType = getSortType(sortTypeStr);
    char *dot = strrchr(fileName, '.');
    if (dot == NULL) {
        return -1;
    }
    char *type = dot + 1; // "txt" or "csv"
    applyHook(manager, type, fileName, dataType, sortType);
    freeManager(manager);
    freeHandleList(handleList);
    return 0;
}
