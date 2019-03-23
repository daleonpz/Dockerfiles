FROM frolvlad/alpine-glibc:alpine-3.9

MAINTAINER Daniel Paredes <daleonpz@gmail.com>

# Set up a tools dev directory
WORKDIR /home/dev


RUN apk --update --no-cache add --virtual build-dependencies  \
    w3m \
    wget \
    openssl \
    ca-certificates \
    bzip2-dev \
    tar

RUN apk --update --no-cache add make libusb-dev stlink 

RUN apk add bash

RUN wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/8-2018q4/gcc-arm-none-eabi-8-2018-q4-major-linux.tar.bz2 \
    && tar xvf gcc-arm-none-eabi-8-2018-q4-major-linux.tar.bz2 \
    &&  rm gcc-arm-none-eabi-8-2018-q4-major-linux.tar.bz2 

RUN apk del build-dependencies

# Set up the compiler path
ENV PATH="/home/dev/gcc-arm-none-eabi-8-2018-q4-major/bin:${PATH}" 


