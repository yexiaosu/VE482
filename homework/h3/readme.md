# ReadMe

## Files

All the files for ex2 are in the `ex2` directory.

`h3.c`,`list.h` and `list.c` are codes for VE482 h3 ex2. `CMakeLists.txt` is a cmakelist for them.

`hw3` is an executable file which is compiled from the source code.

`generate.cpp` is the code to generate random input files, and `generateFile` is the corresponding executable file.

Source codes and cmakelist are provided. You can also compile the executable files on your own.

## How to use

Run:

```shell
./generateFile int # generate rand_int.txt
./generateFile double # generate rand_double.txt
./generateFile "char*" # generate rand_char*.txt
```

and

```shell
./hw3 rand_int.txt inc # refer to descrption in h3 ex2
```

You can use the sorted result to check `rand` mode.