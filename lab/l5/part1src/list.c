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
    newNode->key = (char *) (malloc(sizeof(char) * (strlen(key) + 5)));
    strcpy(newNode->key, key);
    void *data;
    switch (dataType) {
        case CHARTYPE:
            data = malloc(sizeof(char) * (strlen(val) + 5));
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
    target->preHead->next = newNode;
    target->size++;
}

int strCmp(const void *a, const void *b, int sortType) {
    if (sortType == INCREASING) {
        return (strcmp(a, b) >= 0);
    } else if (sortType == DECREASING) {
        return (strcmp(a, b) <= 0);
    } else {
        return (rand() % 2);
    }
}

int intCmp(const void *a, const void *b, int sortType) {
    if (sortType == INCREASING) {
        return (*((int *) (a)) >= *((int *) (b)));
    } else if (sortType == DECREASING) {
        return (*((int *) (a)) <= *((int *) (b)));
    } else {
        return (rand() % 2);
    }
}

int doubleCmp(const void *a, const void *b, int sortType) {
    if (sortType == INCREASING) {
        return (*((double *) (a)) >= *((double *) (b)));
    } else if (sortType == DECREASING) {
        return (*((double *) (a)) <= *((double *) (b)));
    } else {
        return (rand() % 2);
    }
}

struct Node *sortedMerge(node *a, node *b, int dataType, int (*cmp)(const void *, const void *, int)) {
    struct Node *result = NULL;

    // base
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    if (cmp(a->val, b->val, dataType) == 0) {
        result = a;
        result->next = sortedMerge(a->next, b, dataType, cmp);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next, dataType, cmp);
    }
    return (result);
}

void frontBackSplit(node *source, node **front, node **back) {
    node *fast;
    node *slow;
    slow = source;
    fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // 'slow' is before the midpoint
    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

void sortList(node **src, int dataType, int (*cmp)(const void *, const void *, int)) {
    node *head = *src;
    node *left = NULL;
    node *right = NULL;

    if ((head == NULL) || (head->next == NULL)) {
        return; // base
    }

    frontBackSplit(head, &left, &right);

    sortList(&left, dataType, cmp);
    sortList(&right, dataType, cmp);

    *src = sortedMerge(left, right, dataType, cmp);
}

void readData(list *target, char *fileName, int dataType) {
    FILE *rsc = fopen(fileName, "r");
    printf("reading %s\n", fileName);
    char line[MAXLINE] = {'\0'};
    while (fgets(line, MAXLINE, rsc) != NULL) {
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
    fclose(target);
}
