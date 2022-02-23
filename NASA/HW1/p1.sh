#!/bin/bash

temp=`mktemp -d`

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
all=`cat $5`

if ! [[ -z $6 ]]; then
    all=`cat $6`$all
fi

if ! [[ -z $7 ]]; then
    all=`cat $7`$all
fi

sall=''
while IFS= read -r line; do
    t=`echo $line | grep -o -P '(?<=\[).*?(?=\])' | head -n 1`
    T=`date --date="$t" '+%s'`
    f=`echo $line | awk '{out=$6; for(i=7;i<=NF;i++){out=out" "$i}; print out}'`
    NEWLINE=$'\n'
    sall="$sall$T $f$NEWLINE"
done <<< $all

sall=`echo "$sall" | head -n -1`
sall=`echo "$sall" | sort --stable -k 1,1`

while IFS= read -r line; do
    t=`echo $line | awk '{print $1}'`
    if [[ $t -ge $s ]] && [[ $t -le $e ]]; then
        echo $line
    fi
done <<< $sall

#sort --stable -k 5,5 -k 2,4 $temp/out

rm -r $temp
