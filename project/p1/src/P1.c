#include "redirection.h"
#include "functions.h"

int main() {
    char *line;
    char **args;
    int status = 1;
    redirectInfo re = {0};
    ERR = 0;

    HOME = getenv("HOME");
    OLDPWD = getenv("OLDPWD");

    do {
        signal(SIGINT, sigHandler);
        write(1, "mumsh $ ", 8);
        re.out = 0;
        re.in = 0;
        re.pipe = 0;
        ERR = 0;
        line = mumshGetLine(&re);
        if (ERR == 1) {
            free(line);
            continue;
        }
        if (strcmp(line, "") == 0 && (re.pipe != 0 || re.out != 0 || re.in != 0)) {
            mumshError(MISS_PROGRAM, "");
            free(line);
            continue;
        }else if (strcmp(line, "") == 0){
            free(line);
            continue;
        }
        if (re.pipe != 1) {
            args = mumshParse(line);
            if (args[0] == NULL) {
                mumshError(MISS_PROGRAM, "");
                free(args);
                free(line);
                continue;
            }
            status = mumshExecute(args, &re);
            free(args);
        } else {
            status = mumshPipe(line, &re);
        }
        fflush(stdout);
        free(line);
        ERR = 0;
    } while (status);

    return 0;
}
