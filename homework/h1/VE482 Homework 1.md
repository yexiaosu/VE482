# VE482 Homework 1

## Ex. 1 — Revisions

**Explain the difference between the stack and the heap.**

The stack is the memory set aside as scratch space for a thread of execution. It is automatically created or freed when a function is called or returned.

The heap is memory set aside for dynamic allocation. The blocks in it can be allocated or freed at any time manually.

## Ex. 2 — Personal research

1. **Briefly explain what operations are performed when a computer is powered on. What is the role of the BIOS and how does it interact with the OS?**

   BIOS will first conduct POST (Power On Self Test), which will initialize the hardware devices and check potential issues. Meanwhile the Master Boot Record (MBR) will find the operating system. If POST finds no problems, the bootstrap loader will load the operating system for the computer into memory. Finally, the configuration file is used to determine initial run-level of the system.

   BIOS takes the role of performing hardware initialization and providing runtime services for operating systems and programs. 

2. **In a few words explain what are hybrid and exo kernels.**

   A <u>hybrid kernel</u> is an operating system kernel architecture combining microkernel and monolithic kernel architectures used in computer operating systems.

   Ab <u>exo kernel</u> is a tiny kernel that aims at forcing as few abstraction usage as possible. It's so tiny that it can only ensure protection and multiplexing of resources.

## Ex. 3 — Course application

1. **Which of the following instructions should only be allowed in kernel mode? Explain.**

   **a) Disable all interrupts**
   **b) Read the time-of-day clock**
   **c) Set the time-of-day clock**
   **d) Change the memory map**

   a), c) and d).

   In kernel mode, any CPU instruction and hardware feature are available, which means that the instructions have unrestricted access to the underlying hardware. So this mode should not be switched to unless it's necessary to access the hardware, such as disabling all interrupts, setting the time-of-day clock and changing the memory map .

2. **Consider a system that has two CPUs and each CPU is composed of two threads. Suppose three programs, P0, P1, and P2, are started with run times of 5, 10 and 20 ms, respectively. How long will it take to complete the execution of these programs? Assume that all three programs are 100% CPU bound, do not block during execution, and do not change CPUs once assigned.**

   This depends on how the operating system schedules them. Let (0,1;2) indicate that P0 and P1 are scheduled on the same CPU and P2 is scheduled on the other CPU. The possible arrangements and run time are:

   ​	t(0,1;2) = 20 ms

   ​	t(0,2;1) = 25 ms

   ​	t(1,2;0) = 30 ms

## Ex. 4 — Simple problem

**One reason GUIs were initially slow to be adopted was the cost of the hardware needed to support them. How much video RAM is needed to support a 25 lines by 80 rows character monochrome text screen? How much for a 1024 x 768 pixel 24-bit color bitmap? Assuming the cost of this RAM in the 1980es was $5/KB what was the price of those two solutions? How much is it now?**

1. $$25\times 80 = 2000 \text{ Bytes} = 1.95 \text{ KB} \Rightarrow \$9.77$$

2. $$1024\times 768\times 24 = 18874368 \text{ bits} = 2359296 \text{ Bytes} = 2304 \text{ KB} \Rightarrow \$11520$$ 

The current price is less than $1/KB. Then the two solutions will cost:

1. $\$1.95$
2. $\$2304$

## Ex. 5 — Command lines on a Unix system

See attached file.

