# VE482 Lab 3 Report

## The `rsync` command

- **In Minix 3 install the `rsync` software**

```shell
pkgin install rsync
```

- **Install `rsync` on you Linux system**

```shell
sudo apt install rsync
```

- **Read `rsync` manpage**

```shell
man rsync
```

- **Create an exact copy of the directory `/usr/src` into the directory `/usr/src_orig`**

```shell
rsync -av /usr/src/ /usr/src_orig
```

- **If you have already altered Minix 3 source code for homework 2 undo your changes from `/usr/src_orig`**

```shell
rsync -av /usr/src_orig/ /usr/src
```

- **Create an exact copy of the Minix 3 directory `/usr/src` into your Linux system, using `rsync` and ssh (note that the ssh server must be activated under Linux)**

```shell
rsync -av minix:/usr/src/ ~/Desktop/VE482/src_orig
```

## The `diff` and `patch` commands

- **Read the manpages of `diff` and `patch`**

```shell
man diff
man patch
```

- **Using the `diff` command, create a patch corresponding to the above changes**

```shell
diff -u /usr/src_orig /usr/src > patch
```

- **Retrieve your patch on your Linux system**

```shell
rsync minix:/usr/patch ~/Desktop/VE482
```

- **Apply your patch to the copy of `/usr/src_orig` on your Linux system**

```shell
cd ~/Desktop/VE482
patch -p2 < patch
```

- **Revert the patch**

```shell
patch -p2 -RE < patch
```

## Basic git usage

![image-20211004004628899](D:\王澜\2021fall\VE482\l3\image-20211004004628899.png)

![image-20211004004654786](D:\王澜\2021fall\VE482\l3\image-20211004004654786.png)

## Scripting and regular expressions

- **Using `curl` or `wget` retrieve information on shanghai air quality and pipe it to `sed` which should parse the output in order to display the information in the terminal following the format below:**
  **AQ: value Temp: value ºC (e.g. AQ: 55 Temp: 24 ºC).**

```shell
wget -O - "http://aqicn.org/?city=Shanghai&widgetscript&size=large&id=52b39d71decf07.20261781" | sed 's/<[^>]*>//g; s/v[^"]*"//g; s/ Shanghai Air Quality./AQ: /g; s/[GMUVH].*Temp. / Temp: /g; s/".*/ºC/g; 2,3d'
```

![image-20211005003715319](D:\王澜\2021fall\VE482\l3\image-20211005003715319.png)

- Pipelining the output of `ifconfig` to `awk` return only the ip address of your current active network connection (the active network interface can be passed to `ifconfig`).

```shell
ifconfig | awk '/inet / {print $0}' | awk -F' +' '{print $3}'
```

![image-20211005010629487](D:\王澜\2021fall\VE482\l3\image-20211005010629487.png)

