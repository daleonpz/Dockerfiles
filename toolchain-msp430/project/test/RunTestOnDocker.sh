#!/bin/bash

TEST="all"

echo "###############################"

if [ "$1" != "" ]; then
    echo "Running test: " $1 
    TEST="$1"
else
    echo "Running all tests"
fi

echo "###############################"

sudo docker build -t test/local .
sudo docker run \
    --rm \
    -v $(pwd):/usr/src/myapp \
    -w /usr/src/myapp \
    --name my_container test/local
    ceedling clobber test:$TEST
