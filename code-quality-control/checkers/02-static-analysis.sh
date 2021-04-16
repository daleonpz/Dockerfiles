#!/bin/bash

usage() { echo "Usage: [-h help] [-c checker] [-i ingore [true|false]] " >&2; exit 1; }

dummy_file=___dummyfile
c_checker=cppcheck
ignore_flag=false

while getopts c:i:h option
do
    case "${option}"
        in
        c) c_checker=${OPTARG};;
        i) ignore_flag=${OPTARG};;
        h) usage;;
        *) usage;;
    esac
done

echo "==========================================================="
echo "      Running Static Code Analysis ...                     "
echo "              with $c_checker                              "
echo "==========================================================="

$c_checker --enable=warning --enable=performance --enable=unusedFunction \
    --enable=information --language=c  --inconclusive \
    --output-file=$dummy_file -I include/ src/  

if [[ $? != 0 ]]; then
    echo "$c_checker Command failed."
    exit 1
fi

echo "==========================================================="
echo "             Results                                       "
echo "==========================================================="

# ignoring possible ISR 
results=$(cat $dummy_file | \
    sed "/^$/d" | \
    sed -r "/[A-Z]+_ISR.*\[unusedFunction\]/,+1d" | \
    sed "/^nofile:0:0.*[missingInclude]/d")

if [[ $? != 0 ]]; then # This line evaluates the previus command
    rm $dummy_file
    echo "Result processing failed." &>2
    exit 1
fi

rm $dummy_file
if [[ $results ]]; then
    echo "  FAIL                                                     " 
    echo "  Refactor the following files:                            " 
    echo "==========================================================="
    echo "$results"
    if [[ $ignore_flag == false ]]; then exit 1; fi
    echo ""
    echo ""
    echo "  Static Analysis EXIT ERROR was IGNORED !"
    echo ""
else
    echo "  SUCCESS                                                 "
    echo "  The static analyzer approves your code."
fi

echo "==========================================================="
exit 0
