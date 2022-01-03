//
// Created by lanwang on 10/2/21.
//

#include "constant.h"
#include "redirection.h"

void mumshError(int error, char *str) {
    switch (error) {
        case NO_PROGRAM:
            fputs(str, stderr);
            fputs(": command not found\n", stderr);
            exit(1);
            break;

        case NO_FILE:
            fputs(str, stderr);
            fputs(": No such file or directory\n", stderr);
            exit(1);
            break;

        case FAIL_TO_OPEN:
            fputs(str, stderr);
            fputs(": Permission denied\n", stderr);
            exit(1);
            break;

        case DUP_IN:
            fputs("error: duplicated input redirection\n", stderr);
            break;

        case DUP_OUT:
            fputs("error: duplicated output redirection\n", stderr);
            break;

        case SYN_ERR:
            fputs("syntax error near unexpected token `", stderr);
            fputs(str, stderr);
            fputs("'\n", stderr);
            break;

        case MISS_PROGRAM:
            fputs("error: missing program\n", stderr);
            break;

        case NO_DIRECTORY:
            fputs(str, stderr);
            fputs(": No such file or directory\n", stderr);
            break;

        case MISS_PROGRAM_AFTER:
            fputs("error: missing program\n", stderr);
            exit(1);
            break;

        default:
            break;
    }
    ERR = 1;
}
