#!/bin/bash
if [[ $# != 2 ]]; then
    echo "usage: ./submit.sh [problem_id] [file_name]"
    exit 1
fi
if ! [[ -d ~/Code/C++/DSA/b10902085/$1 ]]; then
    mkdir ~/Code/C++/DSA/b10902085/$1
fi
cp $2 ~/Code/C++/DSA/b10902085/$1/main.c
if [[ $? != 0 ]]; then
    exit 1
fi
cd ~/Code/C++/DSA/b10902085
pwd
git add .
git commit -m "Nothing"
git push
