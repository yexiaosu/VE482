#!/bin/bash

useradd yexiaosu

ps -e

top

cat /dev/urandom | head -n 1 | tee 1.txt > 2.txt

cat 1.txt 2.txt > 3.txt

od -x 3.txt

find /usr/src -name '*semaphore*' | xargs grep -l 'ddekit_sem_down'