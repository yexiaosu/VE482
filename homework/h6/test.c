//
// Created by lanwang on 11/19/21.
//

#include <limits.h>

int main() {
    static int test[INT_MAX];

    for (int i = 0; i < INT_MAX; ++i) {
        if (i == 0 || i == 1){
            test[i] = 10;
        }else{
            test[i] = test[i-2] * test[i-1];
        }
    }

    return 0;
}
