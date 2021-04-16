#!/bin/bash

IMAGE_NAME="<gitlab-url>/toolchains/toolchain-dialog1468x"
DOCKERFILE_PATH="DIALOG_1468X_toolchain.Dockefile"

sudo docker build -t $IMAGE_NAME -f $DOCKERFILE_PATH .
sudo docker push $IMAGE_NAME 
