//
// Created by lanwang on 10/26/21.
//

#include "list.h"

list *createList(dlistValueType dataType) {
    list *target = (list *) (malloc(sizeof(list)));
    target->preHead = (node *) malloc(sizeof(node)); // will contain no data
    target->size = 0;
    target->preHead->next = NULL;
    target->dataType = dataType;
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

void clearList(list *target) {
    node *now = target->preHead->next;
    for (int i = 0; i < target->size; ++i) {
        node *tmp = now->next;
        free(now->val);
        free(now->key);
        free(now);
        now = tmp;
    }
    target->preHead->next=NULL;
    target->size=0;
}

void insert(list *target, const char *key, dlistValue *val) {
    node *newNode = (node *) malloc(sizeof(node));
    newNode->key = (char *) (malloc(sizeof(char) * (strlen(key) + 5)));
    strcpy(newNode->key, key);
    void *data;
    dlistValueType dataType = target->dataType;
    switch (dataType) {
        case 1:
            data = malloc(sizeof(int));
            *((int *) data) = val->intValue;
            newNode->val = data;
            break;
        case 2:
            data = malloc(sizeof(char) * (strlen(val->strValue) + 5));
            strcpy((char *) data, val->strValue);
            newNode->val = data;
            break;
        case 3:
            data = malloc(sizeof(double));
            *((double *) data) = val->doubleValue;
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

int strCmp(const void *a, const void *b, dlistSortMethod sortType) {
    if (sortType == 2) {
        return (strcmp(a, b) >= 0);
    } else if (sortType == 3) {
        return (strcmp(a, b) <= 0);
    } else {
        return (rand() % 2);
    }
}

int intCmp(const void *a, const void *b, dlistSortMethod sortType) {
    if (sortType == 2) {
        return (*((int *) (a)) >= *((int *) (b)));
    } else if (sortType == 3) {
        return (*((int *) (a)) <= *((int *) (b)));
    } else {
        return (rand() % 2);
    }
}

int (*cmpFuncArr[])(const void *, const void *, dlistSortMethod) = {intCmp, strCmp, doubleCmp};

int doubleCmp(const void *a, const void *b, dlistSortMethod sortType) {
    if (sortType == 2) {
        return (*((double *) (a)) >= *((double *) (b)));
    } else if (sortType == 3) {
        return (*((double *) (a)) <= *((double *) (b)));
    } else {
        return (rand() % 2);
    }
}

struct Node *
sortedMerge(node *a, node *b, dlistSortMethod sortType, int (*cmp)(const void *, const void *, dlistSortMethod)) {
    struct Node *result = NULL;

    // base
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    if (cmp(a->val, b->val, sortType) == 0) {
        result = a;
        result->next = sortedMerge(a->next, b, sortType, cmp);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next, sortType, cmp);
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

void mergeSort(node **src, dlistSortMethod sortType, int (*cmp)(const void *, const void *, dlistSortMethod)) {
    node *head = *src;
    node *left = NULL;
    node *right = NULL;

    if ((head == NULL) || (head->next == NULL)) {
        return; // base
    }

    frontBackSplit(head, &left, &right);

    mergeSort(&left, sortType, cmp);
    mergeSort(&right, sortType, cmp);

    *src = sortedMerge(left, right, sortType, cmp);
}

void copyList(const list *src, list *target) {
    node *tmpSrc = src->preHead->next;
    node *preTar = target->preHead;
    dlistValue val;
    dlistValueType dataType = src->dataType;
    while (tmpSrc != NULL) {
        char *key = tmpSrc->key;
            preTar->next = (node *) malloc(sizeof(node));
            preTar->next->key = (char *) (malloc(sizeof(char) * (strlen(key) + 5)));
            strcpy(preTar->next->key, key);
            switch (dataType) {
                case 1:
                    val.intValue = *((int *) (tmpSrc->val));
                    preTar->next->val = malloc(sizeof(int));
                    *((int *) preTar->next->val) = val.intValue;
                    break;
                case 2:
                    val.strValue = ((char *) (tmpSrc->val));
                    preTar->next->val = malloc(sizeof(char) * (strlen((char *) (tmpSrc->val)) + 5));
                    strcpy((char *) preTar->next->val, val.strValue);
                    break;
                case 3:
                    val.doubleValue = *((double *) tmpSrc->val);
                    preTar->next->val = malloc(sizeof(double));
                    *((double *) preTar->next->val) = val.doubleValue;
                    break;
                default:
                    break;
            }
            preTar->next->next = NULL;

        preTar = preTar->next;
        tmpSrc = tmpSrc->next;
    }
    target->dataType = src->dataType;
    target->size = src->size;
    fprintf(stderr, "copy\n");
}

void sortList(list *target, dlistSortMethod sortType) {
    mergeSort(&target->preHead->next, sortType, cmpFuncArr[(int) target->dataType - 1]);
    fprintf(stderr, "sort\n");
}

void printList(const list *src) {
    node *tmp = src->preHead->next;
    fprintf(stderr, "print start\n");
    while (tmp != NULL) {
        switch (src->dataType) {
            case 1:
                printf("%s=%d\n", tmp->key, *(int *) tmp->val);
                break;
            case 2:
                printf("%s=%s\n", tmp->key, (char *) tmp->val);
                break;
            case 3:
                printf("%s=%f\n", tmp->key, *(double *) tmp->val);
                break;
            default:
                return;
        }
        tmp = tmp->next;
    }
    fprintf(stderr, "print finish\n");
}

int emptyList(const list *src) {
    if (src->size == 0) {
        return 1;
    } else {
        return 0;
    }
}
