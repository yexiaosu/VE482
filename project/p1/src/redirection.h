//
// Created by lanwang on 9/21/21.
//

#ifndef VE482P1_REDIRECTION_H
#define VE482P1_REDIRECTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <setjmp.h>
#include <errno.h>
#include "constant.h"
#include "var.h"


typedef struct {
    int in;  // 1 for input redirection, 0 for no redirection
    int out;  // 1 for output redirection by overwriting,
              // 2 for output redirection by appending, 0 for no redirection
    int pipe;  // 1 for existing pipe, 0 for no pipe
    size_t pipeNum;  // number of pipes
    int pipeFlag[MUMSH_PIPE_NUM];  // 0 for pipe symbol, 1 for | in quotes
    char inputFile[FILE_NAME_BUFSIZE];
    char outputFile[FILE_NAME_BUFSIZE];
} redirectInfo;

#endif //VE482P1_REDIRECTION_H
