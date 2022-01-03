//
// Created by lanwang on 10/18/21.
//

#include "logic.h"
#include <time.h>

// fun_ptr_arr is an array of function pointers
int (*cmpFuncArr[])(const void *, const void *, int) = {strCmp, intCmp, doubleCmp};

void taskInfo(size_t *dataType, size_t *sortType) {
    char dataTypeTmp[10] = {'\0'};
    char sortTypeTmp[10] = {'\0'};
    printf("Input file type (1, 2, or 3):\n");
    printf("0 - rand_char*.txt\n");
    printf("1 - rand_int.txt\n");
    printf("2 - rand_double.txt\n");
    scanf("%s",dataTypeTmp);
    *dataType = (size_t) (dataTypeTmp[0] - '0');
    printf("Input sort type (0, 1, or 2):\n");
    printf("0 - random\n");
    printf("1 - increasing\n");
    printf("2 - decreasing\n");
    scanf("%s",sortTypeTmp);
    *sortType = (size_t) (sortTypeTmp[0] - '0');
}

int dispatchMenu() {
    srand((unsigned int) time(NULL));
    printf("Welcome! The program can help you sort a list.\n");
    size_t dataType;
    size_t sortType;
    size_t status = 1;
    char statusTmp[10];
    while (status == 1) {
        printf("Exit or continue?\n");
        printf("0 - Exit\n");
        printf("1 - Continue\n");
        scanf("%s",statusTmp);
        status = (size_t) (statusTmp[0] - '0');
        if (status==0){
            return 0;
        }
        taskInfo(&dataType, &sortType);
        list *test = createList();
        switch (dataType) {
            case CHARTYPE:
                readData(test, "rand_char*.txt", dataType);
                sortList(&test->preHead->next, sortType, cmpFuncArr[0]);
                break;
            case INTTYPE:
                readData(test, "rand_int.txt", dataType);
                sortList(&test->preHead->next, sortType, cmpFuncArr[1]);
                break;
            case DOUBLETYPE:
                readData(test, "rand_double.txt", dataType);
                sortList(&test->preHead->next, sortType, cmpFuncArr[2]);
                break;
            default:
                return -1;
        }
        printf("sorting elements\n");
        char *outputFile = getOutFileName(dataType, sortType);
        writeData(test, outputFile, dataType);
        deleteList(test);
        free(outputFile);
    }
    return 0;
}

int dispatchCmd(int argc, char *argv[]) {
    if (argc < 3) return -1;
    srand((unsigned int)time(NULL));
    char *fileName = argv[1];
    char *sortTypeStr = argv[2];
    list *test = createList();
    int dataType = getDataType(fileName);
    int sortType = getSortType(sortTypeStr);
    readData(test, fileName, dataType);
    switch (dataType) {
        case CHARTYPE:
            sortList(&test->preHead->next, sortType, cmpFuncArr[0]);
            break;
        case INTTYPE:
            sortList(&test->preHead->next, sortType, cmpFuncArr[1]);
            break;
        case DOUBLETYPE:
            sortList(&test->preHead->next, sortType, cmpFuncArr[2]);
            break;
        default:
            return -1;
    }
    printf("sorting elements\n");
    char *outputFile = getOutFileName(dataType, sortType);
    writeData(test, outputFile, dataType);
    deleteList(test);
    free(outputFile);
    return 0;
}
