#!/bin/bash

WA(){
    echo 'usage: ./p1.sh -s <Unix timestamp > -e <Unix timestamp > <input file>'
    echo 'ex: ./p1.sh -s 1133642864 -e 1133643505 log1.txt log3.txt'
    exit 1
}

isNumber(){
    local __res=$1
    local re='^[0-9]+$'
    local ret=0
    if [[ $2 =~ $re ]]; then
        ret=1
    fi
    eval $__res="'$ret'"
}

while getopts ":s:e:?" argc; do
    case $argc in
        s)
            s=$OPTARG
            isNumber res $s
            if [[ $res == 0 ]]; then
                WA
            fi
            ;;
        e)
            e=$OPTARG
            isNumber res $e
            if [[ $res == 0 ]]; then
                WA
            fi
            ;;
        ?)
            WA
            ;;
    esac
done

if ! [[ $s ]] || ! [[ $e ]] || [[ $s -gt $e ]]; then
    WA
fi

if [[ -z $5 ]]; then
    WA
fi
