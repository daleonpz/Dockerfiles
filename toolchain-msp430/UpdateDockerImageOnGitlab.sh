#!/bin/bash

IMAGE_NAME="toolchains/toolchain-msp430"
DOCKERFILE_PATH="MSP430_toolchain.Dockerfile"

sudo docker build -t $IMAGE_NAME -f $DOCKERFILE_PATH .

# IMAGE_NAME="<gitlab-url>/toolchains/toolchain-msp430"
# DOCKERFILE_PATH="MSP430_toolchain.Dockerfile"
# 
# sudo docker build -t $IMAGE_NAME -f $DOCKERFILE_PATH .
# sudo docker push $IMAGE_NAME 
