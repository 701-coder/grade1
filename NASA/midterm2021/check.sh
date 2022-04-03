#!/bin/bash

wrong(){
    echo 'Wrong'
    exit 1
}

NEWLINE='@'
a=''
while IFS= read -r line; do
    a=$a$NEWLINE$line
done <<< `zipinfo -1 $1`

b=''
now=''
files=0
while IFS= read -r line; do
    tmp2=`echo $line | grep -o "[\[{]"`
    tmp3=`echo $line | grep -o "[]}]"`
    tmp=`echo $line | grep -o "[_A-Za-z0-9./^]*"`
    if [[ $tmp == '_files' ]]; then
        files=1
    elif [[ $tmp != '' ]] && [[ $tmp2 != '' ]]; then
        now="$now$tmp/"
        b="$b$NEWLINE$now"
    elif [[ $tmp != '' ]]; then
        b="$b$NEWLINE$now$tmp"
    elif [[ $tmp3 != '' ]] && [[ $files == 0 ]]; then
        now=`echo $now | grep -o "[_A-Za-z0-9./^]*/" | sed "s/.$//g"`
        now=`echo $now | grep -o "[_A-Za-z0-9./^]*/"`
    elif [[ $tmp3 != '' ]] && [[ $files != 0 ]]; then
        files=0
    fi
done <<< `jq . $2`

ifs0=$IFS
IFS="$NEWLINE"
read -ra A <<< "$b"
read -ra B <<< "$a"
for j in "${A[@]}"; do
    echo $j
done
IFS=$ifs0
for i in "${A[@]}"; do
    if [[ $i =~ '^' ]]; then
        k=`echo $i | grep -o "[^\^]*"`
        K=''
        while IFS= read -r line; do
            K=$K$line
        done <<< $k
        for j in "${B[@]}"; do
            if [[ $K == $j ]]; then
                wrong
            fi
        done
    else
        ok=0
        for j in "${B[@]}"; do
            if [[ $i == $j ]]; then
                ok=1
            fi
        done
        if [[ $ok == 0 ]]; then
            wrong
        fi
    fi
done
exit 0
