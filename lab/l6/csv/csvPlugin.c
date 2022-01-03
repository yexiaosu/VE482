//
// Created by lanwang on 11/2/21.
//

#include "pluginManager.h"
#include "logic.h"

int csvHook(char *filename, char *type, int dataType, int order) {
    (void) filename;
    (void) type;
    (void) dataType;
    (void) order;
    fprintf(stderr, "No support for csv files.\n");
    return -1;
}

int libcsv(pluginManager *pm) {
    char *type = "csv";
    registerHook(pm, type, csvHook);
    return 0;
}
