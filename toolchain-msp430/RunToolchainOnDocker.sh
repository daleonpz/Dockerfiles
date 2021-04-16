#!/bin/bash

DEVICE_NAME="msp430fr2433"
IMAGE_NAME=""

LOCAL_WORKING_DIR="$(pwd)/project/"
DOCKER_WORKING_DIR="/usr/myapp"

COMMAND_TO_RUN_ON_DOCKER=(sh -c "rake clean DEVICE=${DEVICE_NAME} && rake DEVICE=${DEVICE_NAME} ")

echo "###############################"

echo -e "Working Directory: \r\n\t ${LOCAL_WORKING_DIR}"
echo -e "Executing: \r\n\t ${COMMAND_TO_RUN_ON_DOCKER}"

echo "###############################"


sudo docker run \
    --rm \
    -v $LOCAL_WORKING_DIR:$DOCKER_WORKING_DIR\
    -w $DOCKER_WORKING_DIR\
    --name my_container $IMAGE_NAME  \
    "${COMMAND_TO_RUN_ON_DOCKER[@]}"
