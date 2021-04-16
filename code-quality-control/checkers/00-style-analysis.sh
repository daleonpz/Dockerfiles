#!/bin/bash

usage() { echo "Usage: [-h help] [-I includes_folder ] [-s source_folder ] " >&2; exit 1; }

INCLUDES="include"
SOURCES="src"

while getopts n:c:h option
do
    case "${option}"
        in
        I) INCLUDES=${OPTARG};;
        s) SOURCES=${OPTARG};;
        h) usage;;
        *) usage;;
    esac
done


echo "==========================================================="
echo "      Running Style checking ...                           "
echo "         Processing *.c and *.h files                      "
echo "==========================================================="

results=$(astyle --style=allman --xC60 -xL --mode=c \
    -s4 -S -xW  -Y -p -xg -D -xe -f -k3 -n \
    $INCLUDES/*.h $SOURCES/*.c | \
    sed  -r '/Unchanged/d' | sed 's/Formatted  //g')

if [[ $? != 0 ]]; then
    echo "AStyle Command failed."
    exit 1
fi


echo "             Results                                      "

if [[ $results ]]; then
    echo "  FAIL                                                    " >&2
    echo "  Format correctly the following files:                   " >&2
    echo "===========================================================" >&2
    echo "$results">&2
    exit 1
else
    echo "  SUCCESS         "
    echo "  Everything is ok."
    echo "==========================================================="
    exit 0
fi

