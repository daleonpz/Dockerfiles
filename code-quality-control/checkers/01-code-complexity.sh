#!/bin/bash

usage() { echo "Usage: [-h help] [-n num_lines_of_code ] [-c code_complexity] " >&2; exit 1; }

NLOC=255
CCN=15

while getopts n:c:h option
do
    case "${option}"
        in
        n) NLOC=${OPTARG};;
        c) CCN=${OPTARG};;
        h) usage;;
        *) usage;;
    esac
done

echo "==========================================================="
echo "      Running Complexity Analysis ...                      "
echo " Thresholds:                                               "
echo "     NLOC: $NLOC                                           "
echo "     Complexity: $CCN                                      "
echo "==========================================================="

results=$(lizard -Tnloc=$NLOC -Tcyclomatic_complexity=$CCN -w --languages c src/  | \
    sed 's/: warning:/: function/g')

if [[ $? != 0 ]]; then
    echo "Lizard Command failed."
elif [[ $results ]]; then
    echo "             Results                                       " >&2
    echo "  FAIL                                                     " >&2
    echo "  Refactor the following modules:                          " >&2
    echo "===========================================================" >&2
    echo "$results">&2
    exit 1
else
    echo "             Results                                      "
    echo "  SUCCESS                                                 "
    echo "  Your code doesn't exceed the thresholds.                "
    echo "===========================================================" 
    exit 0
fi

