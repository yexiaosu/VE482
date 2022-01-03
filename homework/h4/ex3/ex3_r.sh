#!/bin/bash
if [ ! -f "ex3.txt" ]; then
    (
    	flock -e 200
    	echo "0">>ex3.txt
    ) 200<>ex3.txt
fi
for ((i=0;i<100;i++))
do
    (
        flock -e 200
        last=$( tail -1 ex3.txt )
        echo $(( last+1 ))>>ex3.txt
    ) 200<>ex3.txt
done