# ReadMe

## Files

### Part 1

All the files for part1 are in the `part1src` directory.

`cmd.c`, `menu.c`, `interface.c`,`list.c`, `list.h`, `logic.c` and `logic.h` are codes for VE482 l3 part1. 

`listCmd` and `listMenu` are executable files which are compiled from the source code. You can also compile them with the source codes.

`rand_char.txt`, `rand_char.txt`, and `rand_char.txt` are some simple test cases. Note that `rand_char.txt` should be modified as `rand_char*.txt` before use.

### Part 2

The files are in `list` directory. They are loaded to JOJ for test.

## How to use

Run:

```shell
./listCmd rand_int.txt inc # command line
./listMenu # menu; follow the instruction
```

You can use the sorted result to check `rand` mode.

To compile:

```shell
gcc -Wall -pedantic -Werror -Wextra cmd.c interface.c interface.h logic.c logic.h list.c list.h -o listCmd
gcc -Wall -pedantic -Werror -Wextra menu.c interface.c interface.h logic.c logic.h list.c list.h -o listMenu
```

