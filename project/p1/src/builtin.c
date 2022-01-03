//
// Created by lanwang on 9/22/21.
//
#include "redirection.h"
#include "var.h"
#include "functions.h"

// implementation of built-in command
int mumshExit() {
    printf("exit\n");
    return 0;
}

int mumshPwd(char **args, redirectInfo *re) {
    char *pwd = malloc(sizeof(char) * MUMSH_BUFSIZE);
    memset(pwd, '\0', MUMSH_BUFSIZE);
    getcwd(pwd,MUMSH_BUFSIZE);
    PWD = pwd;
    if (re->out == 1) {
        int file = open(re->outputFile, O_RDWR | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
        strcat(pwd, "\n");
        if (write(file, pwd, strlen(pwd)) == -1) {
            perror(args[0]);
            exit(1);
        }
        close(file);
    } else if (re->out == 2) {
        int file = open(re->outputFile, O_RDWR | O_APPEND | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
        strcat(pwd, "\n");
        if (write(file, pwd, strlen(pwd)) == -1) {
            perror(args[0]);
            exit(1);
        }
        close(file);
    } else {
        printf("%s\n", PWD);
    }
    free(pwd);
    return 1;
}

int mumshCd(char **args, redirectInfo *re) {
    if (args[1] == NULL) {
        mumshError(NO_DIRECTORY,"");
    } else {
        if (args[2] != NULL) {
            fprintf(stderr, "cd: too many arguments\n");
            return 1;
        }
        if (strcmp(args[1], "~") == 0) {
            chdir(HOME);
            OLDPWD = PWD;
            PWD = HOME;
        } else if (strcmp(args[1], "-") == 0) {
            char *tmp = OLDPWD;
            if (tmp != NULL) {
                chdir(tmp);
                int file;
                if (re->out == 1) {
                    file = open(re->outputFile, O_RDWR | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
                    dup2(file, 1);
                    printf("%s\n", tmp);
                    close(file);
                } else if (re->out == 2) {
                    file = open(re->outputFile, O_RDWR | O_APPEND | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
                    dup2(file, 1);
                    printf("%s\n", tmp);
                    close(file);
                } else {
                    printf("%s\n", tmp);
                }
                OLDPWD = PWD;
                PWD = tmp;
            }
        } else {
            if (chdir(args[1]) != 0) {
                mumshError(NO_DIRECTORY,args[1]);
            } else {
                OLDPWD = PWD;
                PWD = args[1];
            }
        }
    }
    return 1;
}
