//
// Created by lanwang on 10/18/21.
//

#include "list.h"
#include <time.h>

// fun_ptr_arr is an array of function pointers
int (*cmpFuncArr[])(const void *, const void *, int) = {strCmp, intCmp, doubleCmp};

int getDataType(char *fileName) {
    char arg[80];
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
    char outputFile[MAXLINE]= {'\0'};
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

int main(int argc, char **argv) {
    if (argc < 3) {
        return -1;
    }
    srand(time(NULL));
    char *fileName = argv[1];
    char *sortTypeStr = argv[2];
    list *test = createList();
    int dataType = getDataType(fileName);
    int sortType = getSortType(sortTypeStr);
    readData(test, fileName, dataType);
    switch (dataType) {
        case CHARTYPE:
            sortList(test,sortType, cmpFuncArr[0]);
            break;
        case INTTYPE:
            sortList(test,sortType, cmpFuncArr[1]);
            break;
        case DOUBLETYPE:
            sortList(test,sortType, cmpFuncArr[2]);
            break;
        default:
            return -1;
    }
    char *outputFile = getOutFileName(dataType, sortType);
    writeData(test, outputFile, dataType);
    deleteList(test);
    return 0;
}