//
// Created by lanwang on 9/22/21.
//

#ifndef VE482P1_BUILDIN_H
#define VE482P1_BUILDIN_H

#include "redirection.h"

// declare builtin shell command
int mumshExit();
int mumshPwd(char **args, redirectInfo *re);
int mumshCd(char **args, redirectInfo *re);

// built-in command list
char *builtinStr[] = {
        "exit",
        "pwd",
        "cd"
};

int (*builtinFunc[])(char **, redirectInfo *) = {
        &mumshExit,
        &mumshPwd,
        &mumshCd
};

int mumshNumBuiltins() {
    return sizeof(builtinStr) / sizeof(char *);
}

#endif //VE482P1_BUILDIN_H
