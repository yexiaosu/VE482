//
// Created by lanwang on 11/27/21.
//

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "mproc.h"
#include "glo.h"

#define OK 0

int getnchpid(int n, pid_t *childpid) {
    struct mproc *mp;
    int count = 0;
    if (n > NR_PROCS) {
        return -1;  // err
    } else {
        for (mp = &mproc[0]; mp < &mproc[NR_PROCS]; ++mp) {
            if (mp->mp_parent == who_p) {
                ++count;
                if (count == n) {
                    *childpid = mp->mp_pid;
                    return OK; // return 0
                }
            }
        }
    }
    return -1; // err
}

int getchpids(int n, pid_t *childpid) {
    int count = 0, ret = 0;
    for (count = 0; count < n; ++count) {
        ret = getnchpid(count, childpid + count);
        if (ret == -1) {
            childpid = NULL;
            return -1;
        }
    }
    return count;
}

int main() {
    int n = 10;
    pid_t chPid[10];

    for (int i = 0; i < n; ++i) {
        pid_t pid = fork();
        if (pid == 0) {
            sleep(1000);
            return 0;
        } else {
            chPid[i] = pid;
        }
    }
    while (waitpid(-1, NULL, 0));

    pid_t childpid[10];
    int ret = getchpids(n, childpid);

    if (ret != -1) {
        for (int i = 0; i < n; i++) {
            printf("%d, %d\n", chPid[i], childpid[i]);
        }
    } else {
        printf("Error\n");
    }

    return 0;
}
