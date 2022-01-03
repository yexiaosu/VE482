//
// Created by lanwang on 9/25/21.
//
#include "redirection.h"
#include "functions.h"
#include "var.h"

int mumshPipe(char *line, redirectInfo *re) {
    size_t cmdNum = 0, pipeNum = re->pipeNum;
    pid_t pid;
    // fd[2] for one pipe
    int *fd = (int *) malloc((2 * pipeNum) * sizeof(int));
    char *token;
    char **cmds;
    // divide by '|'
    cmds = mumshPipeDivider(line, re);
    token = cmds[cmdNum];
    for (size_t i = 0; i < pipeNum; i++) {
        // create pipe; the file descriptors are stored in fd sequentially for each pipe
        if (pipe(fd + i * 2) < 0) {
            perror("pipe creation failed");
            return 1;
        }
    }
    do {
        pid = fork();
        signal(SIGINT, sigHandlerChild);
        if (pid == 0) {
            // child process
            // deal with redirection
            if (cmdNum == 0) {
                // input redirection
                if (re->in) {
                    int file = open(re->inputFile, O_RDWR);
                    if (dup2(file, 0) < 0) {
                        exit(1);
                    }
                    close(file);
                }
            }
            if (cmdNum == pipeNum) {
                // output redirection
                if (re->out == 1) {
                    int file = open(re->outputFile, O_RDWR | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
                    if (dup2(file, 1) < 0) {
                        exit(1);
                    }
                    close(file);
                } else if (re->out == 2) {
                    int file = open(re->outputFile, O_RDWR | O_APPEND | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
                    if (dup2(file, 1) < 0) {
                        exit(1);
                    }
                    close(file);
                }
            }
            // deal with pipe
            if (cmdNum != 0) {
                // find the file description in fd and redirect input
                if (dup2(fd[(cmdNum - 1) * 2], 0) < 0) {
                    exit(1);
                }
            }
            if (cmdNum != pipeNum) {
                // find the file description in fd and redirect output
                if (dup2(fd[cmdNum * 2 + 1], 1) < 0) {
                    exit(1);
                }
            }
            for (size_t i = 0; i < 2 * pipeNum; i++) {
                close(fd[i]);
            }
            char **args = mumshParse(token);
            if (args[0] == NULL || strcmp(args[0], " ") == 0) {
                // missing command
                mumshError(MISS_PROGRAM_AFTER, "");
            }
            if (strncmp(args[0], "pwd", 3) == 0) {
                char *pwd = malloc(sizeof(char) * MUMSH_BUFSIZE);
                memset(pwd, '\0', MUMSH_BUFSIZE);
                getcwd(pwd, MUMSH_BUFSIZE);
                PWD = pwd;
                printf("%s\n", PWD);
                free(pwd);
            } else {
                if (execvp(args[0], args) == -1) {
                    mumshError(NO_PROGRAM, args[0]);
                }
            }
            fflush(stdout);
            free(args);
            exit(1);
        } else if (pid < 0) {
            // fork error
            return 1;
        }
        cmdNum++;  // parent process
    } while (cmdNum < (pipeNum + 1) && (token = cmds[cmdNum]));
    for (size_t i = 0; i < 2 * pipeNum; i++) {
        close(fd[i]);
    }
    free(fd);
    free(cmds);
    errno = 0;
    wait(NULL);
    while (errno == 0) {
        wait(NULL);
        if (errno == ECHILD) {
            return 1;
        }
    }
    return 1;
}

char **mumshPipeDivider(char *line, redirectInfo *re) {
    char *token;
    size_t pipePos = 0, pipeNum = re->pipeNum;
    char **cmd = malloc((pipeNum * 2) * sizeof(char *));
    // divide by '|'
    token = strtok_r(line, "|", &line);
    for (size_t i = 0; i < (pipeNum + 1); ++i) {
        cmd[i] = token;
        token = strtok_r(line, "|", &line);
        while (re->pipeFlag[pipePos] == 1) {
            strcat(cmd[i], "|");
            strcat(cmd[i], token);
            pipePos++;
            token = strtok_r(line, "|", &line);
        }
    }
    return cmd;
}
