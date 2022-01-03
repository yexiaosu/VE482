//
// Created by lanwang on 10/27/21.
//

#include "logic.h"

int getDataType(char *fileName) {
    char arg[80]={'\0'};
    strcpy(arg, fileName);
    char *dataType;
    dataType = strtok(arg, "_.");
    dataType = strtok(NULL, "_.");
    if (!strcmp(dataType, "char*")) {
        return CHARTYPE;
    } else if (!strcmp(dataType, "int")) {
        return INTTYPE;
    } else if (!strcmp(dataType, "double")) {
        return DOUBLETYPE;
    } else {
        return ERR;
    }
}

int getSortType(char *arg) {
    if (!strcmp(arg, "rand")) {
        return RANDOM;
    } else if (!strcmp(arg, "dec")) {
        return DECREASING;
    } else if (!strcmp(arg, "inc")) {
        return INCREASING;
    } else {
        return ERR;
    }
}

char *getOutFileName(int dataType, int sortType) {
    char *outputFile = (char *) (malloc(sizeof(char) * 20));
    switch (dataType) {
        case CHARTYPE:
            switch (sortType) {
                case INCREASING:
                    strcpy(outputFile, "inc_char*.txt");
                    break;
                case DECREASING:
                    strcpy(outputFile, "dec_char*.txt");
                    break;
                case RANDOM:
                    strcpy(outputFile, "rand_char*.txt");
                    break;
                default:
                    break;
            }
            break;
        case INTTYPE:
            switch (sortType) {
                case INCREASING:
                    strcpy(outputFile, "inc_int.txt");
                    break;
                case DECREASING:
                    strcpy(outputFile, "dec_int.txt");
                    break;
                case RANDOM:
                    strcpy(outputFile, "rand_int.txt");
                    break;
                default:
                    break;
            }
            break;
        case DOUBLETYPE:
            switch (sortType) {
                case INCREASING:
                    strcpy(outputFile, "inc_double.txt");
                    break;
                case DECREASING:
                    strcpy(outputFile, "dec_double.txt");
                    break;
                case RANDOM:
                    strcpy(outputFile, "rand_double.txt");
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return outputFile;
}
