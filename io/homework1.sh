#!/bin/bash
BUFSIZE=128
let MAXBUF=2**$1
let i=1
while [ $BUFSIZE -le  $MAXBUF ] 
do
    echo
    echo "$i" 
    let i+=1
    echo "$BUFSIZE"
    gcc mycopy_sys.c -DBUFSIZE=$BUFSIZE
    time ./a.out ~/Documents/first_paper.zip ~/Download
    rm -f ~/Downloads/first_paper.zip 
    let BUFSIZE*=2
done