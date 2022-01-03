//
// Created by lanwang on 10/25/21.
//

#include "list.h"
#include "lab5_dlist.h"

dlist createDlist(dlistValueType type) {
// EFFECTS: allocate and create a new dlist of datatype 'type' object
// returns the created dlist object on success
// returns NULL on error
    if (type == 0x00) {
        return NULL;
    } else {
        return createList(type);
    }
}

int dlistIsEmpty(dlist_const this) {
// REQUIRES: argument 'this' is non-null and is a valid list
// EFFECTS: return whether the list 'this' is empty
    return emptyList(this);
}

void dlistAppend(dlist this, const char *key, dlistValue value) {
// REQUIRES: type instantiated in 'value' corresponds to the datatype in the list
// argument 'this' and 'key' are both non-null and valid lists
// EFFECTS : add a line of form "key=value" to the tail of the dlist
// MODIFIES: modifies 'this'.
    insert(this, key, &value);
}

void dlistSort(dlist_const this, dlist listDst, dlistSortMethod method) {
// REQUIRES: argument 'this' is not null and is a valid list
// argument 'listDst' is not null and is a valid list
// EFFECTS: Sort 'listSrc' using method given by 'method'.
// Put the results in 'listDst' on success
// Leave 'listDst' unchanged on failure
// * Note 'listDst' may be non-empty when invoked.
// * Be very careful with memory management regarding string lists.
// MODIFIES: argument 'listDst'
    if (dlistIsEmpty(listDst)) {
        copyList(this, listDst);
        sortList(listDst, method);
    } else {
        clearList(listDst);
        copyList(this, listDst);
        sortList(listDst, method);
    }
}

void dlistPrint(dlist_const this) {
// REQUIRES: argument 'this' is not null and is a valid list
// EFFECTS: Print the content of 'this' in the required format to standard output.
// A newline must be followed after each line (including the last one).
    printList(this);
}

void dlistFree(dlist this) {
// REQUIRES: argument 'this' is <EITHER> NULL or a valid list
// EFFECTS: if 'this' is NULL do nothing, other wise frees the list
// By freeing the list the user also needs to free the data
// the list manages
    if (this == NULL) {
        return;
    } else {
        deleteList(this);
    }
}
