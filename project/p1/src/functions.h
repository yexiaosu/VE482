//
// Created by lanwang on 9/22/21.
//

#ifndef VE482P1_FUNCTIONS_H
#define VE482P1_FUNCTIONS_H

/*--------------------
 *---- readline.c ----
 *--------------------*/
char *mumshGetLine(redirectInfo *re);

char **mumshParse(char *line);

/*--------------------
 *---- execute.c -----
 *--------------------*/
int mumshLaunch(char **args, redirectInfo *re);

int mumshExecute(char **args, redirectInfo *re);

/*--------------------
 *------ pipe.c ------
 *--------------------*/
char **mumshPipeDivider(char *line, redirectInfo *re);

int mumshPipe(char *line, redirectInfo *re);

/*--------------------
 *----- signal.c -----
 *--------------------*/
void sigHandler(int sigNo);

void sigHandlerChild();

/*--------------------
 *----- error.c ------
 *--------------------*/
void mumshError(int error, char *str);

#endif //VE482P1_FUNCTIONS_H
