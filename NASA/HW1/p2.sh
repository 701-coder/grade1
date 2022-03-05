#!/bin/bash

c='ls'
I=''
que0=''
que1=''
NEWLINE='@'

dfs(){
    s=''
    for (( i=0; i+1<$1; ++i )); do
        s="$s---"
    done
    if [[ $1 -gt 0 ]]; then
        s="|$s "
    fi
    if [[ $I == '' ]] || [[ $3 =~ $I ]]; then
        ifs0=$IFS
        IFS="$NEWLINE"
        read -ra A0 <<< "$que0"
        read -ra A1 <<< "$que1"
        que2=0
        for i in "${!A1[@]}"; do
            if [[ $que2 == 1 ]] || [[ $i -ge ${#A0[@]} ]] || [[ "${A0[$i]}" != "${A1[$i]}" ]]; then
                echo "${A1[$i]}"
                que2=1
            fi
        done
        echo "$s$3"
        #echo "$que1$s$3"
        que0="$que1$s$3"
        IFS=$ifs0
    fi

    que1="$que1$s$3$NEWLINE"

    if [[ -d $3 ]]; then
        cd $3
        if [[ $1 -le $2 ]]; then
            for i in `$c`; do
                if [[ $i != '.' ]] && [[ $i != '..' ]]; then
                    dfs $(($1+1)) $2 $i
                fi
            done
        fi
        cd ..
    fi
    que1="${que1%\|*}"
}

pth=$1
if [[ ${pth:0:1} == '-' ]]; then
    pth='.'
else
    shift
fi

l=""

while getopts ":l:rai:?" argc; do
    case $argc in
        l)
            l=$OPTARG
            ;;
        r)
            c="$c -r"
            ;;
        a)
            c="$c -a"
            ;;
        i)
            I=$OPTARG
            ;;
        ?)
            ;;
    esac
done

dfs 0 $l $pth
