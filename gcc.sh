#!/bin/bash
if [[ $# != 1 ]]; then
    echo 'gcc.sh: invalid number of arguments'
    exit 1
fi
gcc $1 -o a.out -Wall -Wextra -static -O2 -std=c11
if [[ $? == 0 ]]; then
    echo 'Congratulations! The program has been compiled sucessfully.'
    echo 'Running...'
    echo
    ./a.out
    echo
fi
