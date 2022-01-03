//
// Created by lanwang on 9/22/21.
//
#include "redirection.h"
#include "functions.h"

char *mumshGetLine(redirectInfo *re) {
    size_t bufsize = MUMSH_BUFSIZE;
    size_t pos = 0, pipePos = 0;
    char *line = malloc(sizeof(char) * bufsize);
    memset(line, '\0', bufsize);
    int c;

    do {
        // Read a character
        c = getchar();

        if (pos == 0 && c == EOF){
            free(line);
            write(1, "exit\n", 5);
            exit(0);
        }

        if (pos == 0 && c == ' ') {
            c = getchar();
            while (c == ' ') {
                c = getchar();
            }
        }

        // the end of a line
        if (c == '\n') {
            line[pos] = '\0';
            return line;
        } else {
            if (c == '"') {
                c = getchar();
                while (c != '"') {
                    if (c == '\n') {
                        line[pos] = (char) c;
                        pos++;
                        write(1, "> ", 2);
                        c = getchar();
                        continue;
                    }
                    if (c == '|') {
                        re->pipeFlag[pipePos] = 1;
                        pipePos++;
                        line[pos] = (char) c;
                        line[pos + 1] = ' ';
                        pos++;
                    } else {
                        line[pos] = (char) c;
                    }
                    pos++;
                    c = getchar();
                }
                continue;
            }
            if (c == '\'') {
                c = getchar();
                while (c != '\'') {
                    if (c == '\n') {
                        line[pos] = (char) c;
                        pos++;
                        write(1, "> ", 2);
                        c = getchar();
                        continue;
                    }
                    if (c == '|') {
                        re->pipeFlag[pipePos] = 1;
                        pipePos++;
                        line[pos + 1] = ' ';
                        pos++;
                    } else {
                        line[pos] = (char) c;
                    }
                    pos++;
                    c = getchar();
                }
                continue;
            }
            if (c == '|') {
                if (pos == 0) {
                    mumshError(MISS_PROGRAM, "");
                    memset(line, '\0', bufsize);
                    while ((c = getchar()) != '\n' && c != EOF) {}
                    return line;
                }
                re->pipe = 1;
                re->pipeNum++;
                re->pipeFlag[pipePos] = 0;
                pipePos++;
                line[pos] = (char) c;
                pos++;
                c = getchar();
                if (c == '\n') {
                    write(1, "> ", 2);
                    c = getchar();
                }
                while (c == ' ') {
                    c = getchar();
                }
                if (c == '|') {
                    mumshError(MISS_PROGRAM, "");
                    memset(line, '\0', bufsize);
                    while ((c = getchar()) != '\n' && c != EOF) {}
                    return line;
                }
                if (re->out == 1 || re->out == 2) {
                    mumshError(DUP_OUT, "");
                    memset(line, '\0', bufsize);
                    while ((c = getchar()) != '\n' && c != EOF) {}
                    return line;
                }
            }
            // deal with redirection
            if (c == '<') {
                // Input redirection
                if (re->in == 1 || re->pipe == 1) {
                    mumshError(DUP_IN, "");
                    memset(line, '\0', bufsize);
                    while ((c = getchar()) != '\n' && c != EOF) {}
                    return line;
                }
                re->in = 1;
                c = getchar();
                while (c == ' ') {
                    c = getchar();
                }
                if (c == '\n') {
                    write(1, "> ", 2);
                    c = getchar();
                }
                if (c == '>' || c == '<' || c == '|') {
                    char *tmp = malloc(sizeof(char) * 5);
                    memset(tmp, '\0', 5);
                    tmp[0] = ((char) c);
                    mumshError(SYN_ERR, tmp);
                    free(tmp);
                    memset(line, '\0', bufsize);
                    while ((c = getchar()) != '\n' && c != EOF) {}
                    return line;
                }
                char *fileName = malloc(sizeof(char) * FILE_NAME_BUFSIZE);
                memset(fileName, '\0', FILE_NAME_BUFSIZE);
                int i = 0;
                while (c != ' ' && c != '>' && c != '<' && c != '\n' && c != EOF) {
                    if (c == '"') {
                        c = getchar();
                        while (c != '"') {
                            fileName[i] = (char) c;
                            i++;
                            c = getchar();
                        }
                        c = getchar();
                        continue;
                    }
                    if (c == '\'') {
                        c = getchar();
                        while (c != '\'') {
                            fileName[i] = (char) c;
                            i++;
                            c = getchar();
                        }
                        c = getchar();
                        continue;
                    }
                    fileName[i] = (char) c;
                    i++;
                    c = getchar();
                }
                fileName[i] = '\0';
                strcpy(re->inputFile, fileName);
                free(fileName);
            }
            if (c == '>') {
                // Output redirection
                if (re->out == 1 || re->out == 2) {
                    mumshError(DUP_OUT, "");
                    memset(line, '\0', bufsize);
                    while ((c = getchar()) != '\n' && c != EOF) {}
                    return line;
                }
                re->out = 1;
                c = getchar();
                if (c == '>') {
                    re->out = 2;
                    c = getchar();
                }
                while (c == ' ') {
                    c = getchar();
                }
                if (c == '\n') {
                    write(1, "> ", 2);
                    c = getchar();
                }
                if (c == '>' || c == '<' || c == '|') {
                    char *tmp = malloc(sizeof(char) * 5);
                    memset(tmp, '\0', 5);
                    tmp[0] = ((char) c);
                    mumshError(SYN_ERR, tmp);
                    free(tmp);
                    memset(line, '\0', bufsize);
                    while ((c = getchar()) != '\n' && c != EOF) {}
                    return line;
                }
                char *fileName = malloc(sizeof(char) * FILE_NAME_BUFSIZE);
                memset(fileName, '\0', FILE_NAME_BUFSIZE);
                int i = 0;
                while (c != ' ' && c != '>' && c != '<' && c != '\n' && c != EOF) {
                    if (c == '"') {
                        c = getchar();
                        while (c != '"') {
                            fileName[i] = (char) c;
                            i++;
                            c = getchar();
                        }
                        c = getchar();
                        continue;
                    }
                    if (c == '\'') {
                        c = getchar();
                        while (c != '\'') {
                            fileName[i] = (char) c;
                            i++;
                            c = getchar();
                        }
                        c = getchar();
                        continue;
                    }
                    fileName[i] = (char) c;
                    i++;
                    c = getchar();
                }
                fileName[i] = '\0';
                strcpy(re->outputFile, fileName);
                free(fileName);
            }
            if (c == '\n') {
                line[pos] = '\0';
            } else {
                line[pos] = (char) c;
            }
        }
        pos++;

        // If we have exceeded the buffer, reallocate.
        if (pos >= bufsize) {
            bufsize += MUMSH_BUFSIZE;
            char *tmp = realloc(line, bufsize);
            if (tmp == NULL) {
                free(tmp);
            } else {
                line = tmp;
            }
        }
    } while (c != EOF && c != '\n');
    return line;
}

char **mumshParse(char *line) {
    size_t bufSize = MUMSH_ARG_BUFSIZE, pos = 0;
    char **args = malloc(bufSize * sizeof(char *));
    char *token;

    token = strtok(line, " ");  // split the input by space
    while (token != NULL) {
        args[pos] = token;
        pos++;
        // reallocate if the current size is bigger than what has been allocated
        if (pos >= bufSize) {
            bufSize += MUMSH_ARG_BUFSIZE;
            char **tmp = realloc(args, bufSize * sizeof(char *));
            if (tmp == NULL) {
                free(tmp);
            } else {
                args = tmp;
            }
        }
        // get next token
        token = strtok(NULL, " ");
    }
    args[pos] = NULL;
    return args;
}
