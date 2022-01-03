//
// Created by lanwang on 9/28/21.
//
#include "redirection.h"

void sigHandler() {
    write(1, "\n", 1);
    write(1, "mumsh $ ", 8);
}

void sigHandlerChild() {
    write(1, "\n", 1);
}
