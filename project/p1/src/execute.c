//
// Created by lanwang on 9/22/21.
//
#include "buildin.h"
#include "functions.h"

int mumshLaunch(char **args, redirectInfo *re) {
    pid_t pid;
    pid = fork();
    signal(SIGINT, sigHandlerChild);

    if (pid == 0) {
        // child process
        // deal with redirection
        if (re->in == 1) {
            int file = open(re->inputFile, O_RDWR);
            if (file == -1){
                mumshError(NO_FILE,re->inputFile);
            }
            dup2(file, 0);
            close(file);
        }
        if (re->out == 1) {
            int file = open(re->outputFile, O_RDWR | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
            if (file == -1){
                mumshError(FAIL_TO_OPEN,re->outputFile);
            }
            dup2(file, 1);
            close(file);
        } else if (re->out == 2) {
            int file = open(re->outputFile, O_RDWR | O_APPEND | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
            if (file == -1){
                mumshError(FAIL_TO_OPEN,re->outputFile);
            }
            dup2(file, 1);
            close(file);
        }
        // execute
        if (execvp(args[0], args) == -1) {
            mumshError(NO_PROGRAM,args[0]);
        }
        exit(1);
    } else if (pid < 0) {
        // error
        perror("mumsh");
    } else {
        // parent process
        wait(NULL);  // wait for child process executing
    }

    return 1;
}

int mumshExecute(char **args, redirectInfo *re) {
    if (args[0] == NULL) {
        // empty command
        return 1;
    }

    for (int i = 0; i < mumshNumBuiltins(); i++) {
        if (strcmp(args[0], builtinStr[i]) == 0) {
            return (*builtinFunc[i])(args, re);
        }
    }

    return mumshLaunch(args, re);
}
