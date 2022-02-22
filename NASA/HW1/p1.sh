function WA(){
    echo 'usage: ./p1.sh -s <Unix timestamp > -e <Unix timestamp > <input file>' >&2
    echo 'ex: ./p1.sh -s 1133642864 -e 1133643505 log1.txt log3.txt' >&2
    exit 1
}

declare -A args
i=0
for arg in $@; do
    args[$i]=$arg
    ((i++))
done
s=""
e=""
is=0
ie=0
rem='\-'
for ((i=0; i < $#; i++)); do
    if [[ ${args[$i]} == '-s' ]]; then
        if [[ -z ${args[$(($i+1))]} ]]; then
            WA
        fi
        s=${args[$(($i+1))]}
        is=$i
    elif [[ ${args[$i]} == '-e' ]]; then
        if [[ -z ${args[$(($i+1))]} ]]; then
            WA
        fi
        e=${args[$(($i+1))]}
        ie=$i
    elif [[ ${args[$i]} =~ $rem ]]; then
        WA
    fi
done

if [[ $s == "" ]] || [[ $e == "" ]]; then
    WA
fi

re='^[0-9]+$';

if ! [[ $s =~ $re ]] || ! [[ $e =~ $re ]]; then
    WA
fi

if [[ $s -gt $e ]]; then
    WA
fi

f=-1

for ((i=0; i < $#; i++)); do
    if ! [[ ${args[$i]} =~ $rem ]] && [[ $i != $(($is+1)) ]] && [[ $i != $(($ie+1)) ]]; then
        f=$i
    fi
done
if [[ $f == -1 ]]; then
    WA
fi
