#!/bin/bash

c='ls'
I=''
que0=''
que1=''
Que1=''
NEWLINE='@'
sym=0
sl=0
slFile=''

dfs(){
    s=''
    for (( i=0; i+1<$1; ++i )); do
        s="$s---"
    done
    if [[ $1 -gt 0 ]]; then
        s="|$s "
    fi
    S=`pwd -P`
    Que1="$Que1$NEWLINE$S"
    lp=0

    if [[ $3 != '.' ]] && [[ -d $3 ]]; then
        cd $3
        S=`pwd -P`
        ifs0=$IFS
        IFS="$NEWLINE"
        read -ra A <<< "$Que1"
        for i in "${A[@]}"; do
            if [[ $i == $S ]]; then
                lp=1
            fi
        done
        IFS=$ifs0
        cd ..
    fi

    if [[ $sl == 1 ]]; then
        lp=0
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
        if [[ $lp == 1 ]]; then
            echo "$s$3 (loop)"
        elif [[ $sl == 1 ]]; then
            echo "$s$3 -> $slFile"
        else
            echo "$s$3"
        fi
        que0="$que1$s$3"
        IFS=$ifs0
    fi

    que1="$que1$s$3$NEWLINE"

    if [[ -d $3 ]] && [[ $lp == 0 ]]; then
        cd $3
        if [[ $1 -le $2 ]]; then
            if [[ $sym == 0 ]]; then
                for i in `$c`; do
                    if [[ $i != '.' ]] && [[ $i != '..' ]]; then
                        dfs $(($1+1)) $2 $i
                    fi
                done
            elif [[ $sl == 0 ]]; then
                Line=0
                while IFS= read -r line; do
                    if [[ $Line != 0 ]]; then
                        ifs0=$IFS
                        read -ra A <<< "$line"
                        IFS=$ifs0
                        if [[ ${#A[@]} != 9 ]]; then
                            sl=1
                            slFile=${A[10]}
                        else
                            sl=0
                            slFile=''
                        fi
                        if [[ ${A[8]} != '.' ]] && [[ ${A[8]} != '..' ]]; then
                            dfs $(($1+1)) $2 ${A[8]}
                        fi
                    fi
                    Line=1
                done <<< `$c`
                sl=0
            fi
        fi
        cd ..
    fi
    que1="${que1%\|*}"
    Que1="${Que1%${NEWLINE}*}"
}

if [[ -n $1 ]]; then
    pth=$1
else
    pth='.'
fi
if [[ ${pth:0:1} == '-' ]]; then
    pth='.'
else
    shift
fi

l=1000000007

while getopts ":l:rasi:?" argc; do
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
        s)
            sym=1
            c="$c -l"
            ;;
        ?)
            ;;
    esac
done

dfs 0 $l $pth
