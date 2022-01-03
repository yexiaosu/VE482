//
// Created by lanwang on 9/22/21.
//

#ifndef VE482P1_CONSTANT_H
#define VE482P1_CONSTANT_H

#define MUMSH_BUFSIZE 1024
#define FILE_NAME_BUFSIZE 100
#define MUMSH_ARG_BUFSIZE 400
#define MUMSH_WORD_BUFSIZE 100
#define MUMSH_PIPE_NUM 20

typedef enum error {
    NO_PROGRAM             = 0,
    NO_FILE                = 1,
    FAIL_TO_OPEN           = 2,
    DUP_IN                 = 3,
    DUP_OUT                = 4,
    SYN_ERR                = 5,
    MISS_PROGRAM           = 6,
    NO_DIRECTORY           = 7,
    MISS_PROGRAM_AFTER     = 8
} error_t;

#endif //VE482P1_CONSTANT_H
