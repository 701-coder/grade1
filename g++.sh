#!/bin/bash
if [[ $# != 1 ]]; then
    echo 'g++.sh: invalid number of arguments'
    exit 1
fi
g++ $1 -o a.out -Wall -Wextra -std=c++17
if [[ $? == 0 ]]; then
    echo 'Congratulations! The program has been compiled sucessfully.'
    echo 'Running...'
    echo
    ./a.out
    echo
fi
