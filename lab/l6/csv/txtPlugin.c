//
// Created by lanwang on 11/2/21.
//

#include "pluginManager.h"
#include "logic.h"

int txtHook(char *filename, char *type, int dataType, int order) {
    (void) type;
    return run(filename, dataType, order);
}

int libtxt(pluginManager *pm) {
    char *type = "txt";
    registerHook(pm, type, txtHook);
    return 0;
}
