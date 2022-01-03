//
// Created by lanwang on 10/18/21.
//

#include "list.h"

list *createList(void) {
    list *target = (list *) (malloc(sizeof(list)));
    target->preHead = (node *) malloc(sizeof(node)); // will contain no data
    target->size = 0;
    target->preHead->next = NULL;
    return target;
}

void deleteList(list *target) {
    node *now = target->preHead->next;
    for (int i = 0; i < target->size; ++i) {
        node *tmp = now->next;
        free(now->val);
        free(now->key);
        free(now);
        now = tmp;
    }
    free(target->preHead);
    free(target);
}

void insert(list *target, char *key, char *val, int dataType) {
    node *newNode = (node *) malloc(sizeof(node));
    newNode->key = (char *) (malloc(sizeof(char) * strlen(key)));
    strcpy(newNode->key, key);
    void *data;
    switch (dataType) {
        case CHARTYPE:
            data = malloc(sizeof(char) * strlen(val));
            strcpy((char *) data, val);
            newNode->val = data;
            break;
        case INTTYPE:
            data = malloc(sizeof(int));
            *((int *) data) = (int) (strtol(val, NULL, 10));
            newNode->val = data;
            break;
        case DOUBLETYPE:
            data = malloc(sizeof(double));
            *((double *) data) = strtod(val, NULL);
            newNode->val = data;
            break;
        default:
            break;
    }
    newNode->next = target->preHead->next;
    target->preHead->next = newNode;
    target->size++;
}

int strCmp(const void *a, const void *b, int sortType) {
    if (sortType == INCREASING) {
        return (strcmp(a, b) > 0);
    } else if (sortType == DECREASING) {
        return (strcmp(a, b) < 0);
    } else {
        return (rand() % 2);
    }
}

int intCmp(const void *a, const void *b, int sortType) {
    if (sortType == INCREASING) {
        return (*((int *) (a)) > *((int *) (b)));
    } else if (sortType == DECREASING) {
        return (*((int *) (a)) < *((int *) (b)));
    } else {
        return (rand() % 2);
    }
}

int doubleCmp(const void *a, const void *b, int sortType) {
    if (sortType == INCREASING) {
        return (*((double *) (a)) > *((double *) (b)));
    } else if (sortType == DECREASING) {
        return (*((double *) (a)) < *((double *) (b)));
    } else {
        return (rand() % 2);
    }
}

void sortList(list *src, int dataType, int (*cmp)(const void *, const void *, int)) {
    int swapped;
    struct Node *itr;
    struct Node *rightItr = NULL;

    /* Checking for empty list */
    if (src->preHead->next == NULL)
        return;

    do {
        swapped = 0;
        itr = src->preHead->next;

        while (itr->next != rightItr) {
            if (cmp(itr->val, itr->next->val, dataType) > 0) {
                void *tmpVal = itr->val;
                itr->val = itr->next->val;
                itr->next->val = tmpVal;
                void *tmpStr = itr->key;
                itr->key = itr->next->key;
                itr->next->key = tmpStr;
                swapped = 1;
            }
            itr = itr->next;
        }
        rightItr = itr;
    } while (swapped);
    printf("sorting elements\n");
}

void readData(list *target, char *fileName, int dataType) {
    FILE *rsc = fopen(fileName, "r");
    printf("reading %s\n", fileName);
    char line[MAXLINE] = {'\0'};
    while (1) {
        fgets(line, MAXLINE, rsc);
        if (line[0] == '\n') {
            // empty line
            break;
        }
        char *tmpKey = strtok(line, "=");
        char *tmpVal = strtok(NULL, "\n");
        insert(target, tmpKey, tmpVal, dataType);
    }
    fclose(rsc);
}

void writeData(list *src, char *fileName, int dataType) {
    FILE *target = fopen(fileName, "w");
    printf("writing %s\n", fileName);
    node *now = src->preHead->next;
    for (int i = 0; i < src->size; ++i) {
        switch (dataType) {
            case CHARTYPE:
                fprintf(target, "%s=%s\n", now->key, ((char *) (now->val)));
                break;
            case INTTYPE:
                fprintf(target, "%s=%d\n", now->key, *((int *) (now->val)));
                break;
            case DOUBLETYPE:
                fprintf(target, "%s=%lf\n", now->key, *((double *) (now->val)));
                break;
        }
        now = now->next;
    }
    fprintf(target, "\n");
    fclose(target);
}
