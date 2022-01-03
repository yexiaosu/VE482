//
// Created by lanwang on 10/27/21.
//

#include "logic.h"

// fun_ptr_arr is an array of function pointers
int (*cmpFuncArr[])(const void *, const void *, int) = {strCmp, intCmp, doubleCmp};

int run(char *fileName, int dataType, int sortType) {
    list *test = createList();
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
//    printf("sorting elements\n");
//    char *outputFile = getOutFileName(dataType, sortType);
//    writeData(test, outputFile, dataType);
    printList(test, dataType);
    deleteList(test);
//    free(outputFile);
    return 0;
}

void printList(const list *src, int dataType) {
    node *tmp = src->preHead->next;
    fprintf(stderr, "print start\n");
    while (tmp != NULL) {
        switch (dataType) {
            case 0:
                printf("%s=%s\n", tmp->key, (char *) tmp->val);
                break;
            case 1:
                printf("%s=%d\n", tmp->key, *(int *) tmp->val);
                break;
            case 2:
                printf("%s=%f\n", tmp->key, *(double *) tmp->val);
                break;
            default:
                return;
        }
        tmp = tmp->next;
    }
    fprintf(stderr, "print finish\n");
}

//char *getOutFileName(int dataType, int sortType) {
//    char *outputFile = (char *) (malloc(sizeof(char) * 20));
//    switch (dataType) {
//        case CHARTYPE:
//            switch (sortType) {
//                case INCREASING:
//                    strcpy(outputFile, "inc_char*.txt");
//                    break;
//                case DECREASING:
//                    strcpy(outputFile, "dec_char*.txt");
//                    break;
//                case RANDOM:
//                    strcpy(outputFile, "rand_char*.txt");
//                    break;
//                default:
//                    break;
//            }
//            break;
//        case INTTYPE:
//            switch (sortType) {
//                case INCREASING:
//                    strcpy(outputFile, "inc_int.txt");
//                    break;
//                case DECREASING:
//                    strcpy(outputFile, "dec_int.txt");
//                    break;
//                case RANDOM:
//                    strcpy(outputFile, "rand_int.txt");
//                    break;
//                default:
//                    break;
//            }
//            break;
//        case DOUBLETYPE:
//            switch (sortType) {
//                case INCREASING:
//                    strcpy(outputFile, "inc_double.txt");
//                    break;
//                case DECREASING:
//                    strcpy(outputFile, "dec_double.txt");
//                    break;
//                case RANDOM:
//                    strcpy(outputFile, "rand_double.txt");
//                    break;
//                default:
//                    break;
//            }
//            break;
//        default:
//            break;
//    }
//    return outputFile;
//}
