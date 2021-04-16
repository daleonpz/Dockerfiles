#!/bin/bash

TEST="all"
IMAGE_NAME="toolchain/dialog1468x"
DOCKERFILE_PATH="DIALOG_1468X_toolchain.Dockefile"

echo "###############################"

if [ "$1" != "" ]; then
    echo "Running test: " $1 
    TEST="$1"
else
    echo "Running all tests"
fi

echo "###############################"
sudo docker build -t $IMAGE_NAME -f $DOCKERFILE_PATH .


sudo docker run \
    --rm \
    -v $(pwd):/usr/src/myapp \
    -w /usr/src/myapp \
    --name my_container $IMAGE_NAME  \
    make $TEST
