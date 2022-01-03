# VE482 Homework 8

Lan Wang 519370910084

## Ex. 1

1. **Is it possible to scan a document and send it through a wireless network at full speed? Explain why, why not.**

  Yes if the input job done by the scanner and output job done by network can be separated completely.

2. **How can an OS facilitate the installation of a new device without any need to recompile the OS or even to reboot it?**

  OS maintains a table for device drivers to make it possible to load and unload devices dynamically, which is similar to the way to manage plugins.

3. **In the slides four I/O software layers are listed; in which layers are the following operations done:**
    **a) Computing the track, sector, and head for a disk read**
    **b) Writing command to the device registers**
    **c) Checking is the user is allowed to use the device**
    **d) Converting binary integers to ASCII for printing**

  a) Device Drivers
  b) Interrupt Handlers
  c) Device Independent OS Software
  d) User Level IO Software

4. **A DMA controller has four channels. The controller is able to request a 32bit word every 100 nsec. A respond takes equally long. How fats should the bus be in order to avoid being a bottleneck?**

  $$\frac{1}{(100+100)\times 10^{-9}}\times 4=2\times 10^{7} \text{ Byte/sec}$$

5. **Briefly explain what a thin client is.**

   A thin client is a simple (low-performance) computer that has been optimized for establishing a remote connection with a server-based computing environment.  [[1]](https://en.wikipedia.org/wiki/Thin_client)

6. **Describe how a hard disk is working and give a few details regarding its geometry.**

   A hard disk is an electro-mechanical data storage device that stores and retrieves digital data using magnetic storage and one or more rigid rapidly rotating platters coated with magnetic material.   The platters are paired with magnetic heads, usually arranged on a moving actuator arm, which read and write data to the platter surfaces.   Data is accessed in a random-access manner, meaning that individual blocks of data can be stored and retrieved in any order. Modern HDDs are typically in the form of a small rectangular box, containing the round shaped platter and other things. [[2]](https://en.wikipedia.org/wiki/Hard_disk_drive)

7. **What are differences between RAID 0, 1, 5, 6, and 10?** [[3]](https://www.dataplugs.com/en/raid-level-comparison-raid-0-raid-1-raid-5-raid-6-raid-10/)

   **RAID 0**: Data are split up into blocks that get written across all the drives in the array. By using at least 2 disks at the same time, it has high read/write perforamnce. All storage capacity can be fully used with no overhead. 
   **RAID 1**: A setup of at least two drives that contain the exact same data, providing higher reliability. Also, it has high read performance but lower write performance. 
   **RAID 5**: RAID 5 requires the use of at least 3 drives, striping the data across multiple drives like RAID 0, but also has a “parity” distributed across the drives, providing higher reliability. There is zero downtime. Read speed is very fast but write speed is somewhat slower due to the parity that has to be calculated. 
   **RAID 6**: RAID 6 is like RAID 5, but the parity data are written to two drives. That means it requires at least 4 drives and can withstand 2 drives dying simultaneously. Read speed is as fast as RAID 5, but write speed is slower than RAID 5 due to the additional parity data that have to be calculated. 
   **RAID 10**: RAID 10 consists of a minimum for four drives and combine the advantages of RAID 0 and RAID 1 in one single system. It provides security by mirroring all data on secondary drives while using striping across each set of drives to speed up data transfers. This means that RAID 10 can provide the speed of RAID 0 with the redundancy of RAID 1.

## Ex. 2

1. **Suppose that the `TSL` instruction was not available for synchronizing a multiprocessor. Instead, another instruction, `SWP` was provided that atomically swapped the contents of a register with a word in memory. How could that be used to provide multiprocessor synchronisation?**

  Preload a 1 to the register. After the `SWP` instruction, the memory word has a value of 1 and is locked, and its previous value is now contained in the register. 

2. **Briefly describe virtualization and the main challenges that need to be overcome.**

   In computing, virtualization is the act of creating a virtual (rather than actual) version of something, including virtual computer hardware platforms, storage devices, and computer network resources. 

   The main challenges contain: Resource distribution, VM Sprawl, Backward compatibility, Performance monitoring, Backup, and Security. [[4]](https://www.techadvisory.org/2019/05/what-are-the-common-challenges-of-virtualization/)

## Ex. 3

1. **Assuming the current working directory is `/usr/share/doc/mutt/examples` what is the absolute path of `../../../doc/../../lib/mutt`?**

     `/usr/lib/mutt`

2. **A Unix system has 1KB blocks and 4B disk addresses. What is the maximum file size if i-nodes contain 13 direct entries, and one single, double , and triple indirect entry each?**

   $$\frac{1024}{4}=256 \Rightarrow 256\text{ KB/block}$$

   $$13+256+256^2+256^3=16843021\text{ KB}$$

3. **The time required to read a certain number of bytes can be approximated by summing the seek, rotation delay, and transfer times. Given a disk with mean seek time of 8 msec, a rotation rate of 15,000 rpm and 262,144 bytes per track what are the data rates for block sizes of (i) 1 KB, (ii) 2 KB, and (iii) 4 KB?**

   $$\frac{1}{15000}\times 60\times 1000 \div 2= 2\text{ ms}$$

   (i) $$8+2+\frac{1024}{\frac{262144}{4}}= 10.016\text{ ms}$$

   (ii) $$8+2+\frac{2048}{\frac{262144}{4}}= 10.031\text{ ms}$$

   (iii) $$8+2+\frac{4096}{\frac{262144}{4}}= 10.063\text{ ms}$$

## Ex. 4

1. **If using only lowercase letters how many possible 8 letter words can be chosen? Explain why a password should always contain lower and uppercase letters, numbers and symbols.**

   $$26^8=208827064576$$

   So that there could be much more combinations, making attackers to spend more time to crack it.

2. **Explain why memory dynamically allocated using malloc is sometimes random and some other times set to 0.**

   When `malloc()` is called, one of two things will happen:

   1. It recycles memory that was previous allocated and freed from the same process. The memory will contain data leftover from previous allocations. So it will be random. 
   2. It requests new page(s) from the operating system. Memory coming from the OS will be zeroed for security reasons, preventing those memory that could contain sensitive information such as a password from being reused directly. So the OS will zero it before it gives the memory.

3. **A computer system is made of several components each featuring a different level of security. How secure is this system?**

   The lowest level of security decides the level of security of the whole system.

4. **Can security be achieved? Explain your answer.**

   No. OS can be affected by many factors, so it's impossible to consider all conditions in advance and prevent all dangerous issues.

## Ex. 5

**Write about a page on the topic of firewalls on Linux systems; include information on `iptables`, `ebtables`, and `arptables`. Do not forget to reference your sources of information.**

#### iptables 

iptables is a user-space utility program that allows a system administrator to configure the IP packet filter rules of the Linux kernel firewall, implemented as different Netfilter modules. The filters are organized in different tables, which contain chains of rules for how to treat network traffic packets.Different kernel modules and programs are currently used for different protocols; iptables applies to IPv4, ip6tables to IPv6, arptables to ARP, and ebtables to Ethernet frames. 
iptables requires elevated privileges to operate and must be executed by user root, otherwise it fails to function. On most Linux systems, iptables is installed as /usr/sbin/iptables and documented in its man pages, which can be opened using man iptables when installed. It may also be found in /sbin/iptables, but since iptables is more like a service rather than an "essential binary", the preferred location remains /usr/sbin. 
The term iptables is also commonly used to inclusively refer to the kernel-level components. x_tables is the name of the kernel module carrying the shared code portion used by all four modules that also provides the API used for extensions; subsequently, Xtables is more or less used to refer to the entire firewall (v4, v6, arp, and eb) architecture. [[4]](https://en.wikipedia.org/wiki/Iptables)

#### ebtables 

ebtables is an application program used to set up and maintain the tables of rules (inside the Linux kernel) that inspect Ethernet frames. It is analogous to the iptables application, but less complicated, due to the fact that the Ethernet protocol is much simpler than the IP protocol. 
There are three ebtables tables with built-in chains in the Linux kernel. These tables are used to divide functionality into different sets of rules. Each set of rules is called a chain. Each chain is an ordered list of rules that can match Ethernet frames. If a rule matches an Ethernet frame, then a processing specification tells what to do with that matching frame. The processing specification is called a 'target'. However, if the frame does not match the current rule in the chain, then the next rule in the chain is examined and so forth. The user can create new (user-defined) chains that can be used as the 'target' of a rule. User-defined chains are very useful to get better performance over the linear traversal of the rules and are also essential for structuring the filtering rules into well-organized and maintainable sets of rules. [[5]](https://linux.die.net/man/8/ebtables) 

#### arptables

Arptables is used to set up, maintain, and inspect the tables of ARP packet filter rules in the Linux kernel. Several different tables may be defined. Each table contains a number of built-in chains and may also contain user-defined chains. 
Each chain is a list of rules which can match a set of packets. Each rule specifies what to do with a packet that matches. This is called a 'target', which may be a jump to a user-defined chain in the same table. 
A firewall rule specifies criteria for a packet, and a target. If the packet does not match, the next rule in the chain is the examined; if it does match, then the next rule is specified by the value of the target, which can be the name of a user-defined chain or one of the special values ACCEPT, DROP, QUEUE, or RETURN.  ACCEPT means to let the packet through. DROP means to drop the packet on the floor. QUEUE means to pass the packet to userspace (if supported by the kernel). RETURN means stop traversing this chain and resume at the next rule in the previous (calling) chain. If the end of a built-in chain is reached or a rule in a built-in chain with target RETURN is matched, the target specified by the chain policy determines the fate of the packet. [[6]](https://linux.die.net/man/8/arptables)

## Ex. 6

**What is a kernel panic? Generate one on your Linux system and troubleshoot it. Provide all the details.**

A kernel panic is a safety measure taken by an operating system's kernel upon detecting an internal fatal error in which either it is unable to safely recover or continuing to run the system would have a higher risk of major data loss.

To generate it, run:

```sh
echo c > /proc/sysrq-trigger  # as root user
```

![image-20211212165208390](.\image-20211212165208390.png)

Then reboot.
