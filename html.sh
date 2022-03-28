#!/bin/bash
if [[ $# != 1 ]]; then
    echo 'html.sh: invalid number of arguments'
    exit 1
fi
open $1 &> out
