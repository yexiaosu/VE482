# ReadMe

## Files

### Ex 3

All the files for Ex 3 are in the `ex3` directory.

`banker.cpp` is the source code. `ex3` is a pre-compiled file.

## How to use

### Ex 3

Compile:

```
g++ banker.cpp -o ex3
```

Run:

```
./ex3
```

You need to input the number of processes and number of resource types following the instruction. The inputs must be integers.

The number of available resources of each type, the number of resources of each type currently allocated to each process and the maximum demand of each process in a system are all randomly generated.

The output will print `Available`, `Allocated`, and `Max`, then judge whether it's in a safe state and print the message.

![image-20211105143356659](.\image-20211105143356659.png)

![image-20211105162733120](.\image-20211105143627136.png)

