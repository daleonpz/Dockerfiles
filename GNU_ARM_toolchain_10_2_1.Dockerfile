FROM frolvlad/alpine-glibc

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
RUN apk --update --no-cache add cmake 
RUN apk --update --no-cache add  build-base  gcc
RUN apk add bash

RUN wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/10-2020q4/gcc-arm-none-eabi-10-2020-q4-major-x86_64-linux.tar.bz2 \
    && tar xvf gcc-arm-none-eabi-10-2020-q4-major-x86_64-linux.tar.bz2 \
    &&  rm gcc-arm-none-eabi-10-2020-q4-major-x86_64-linux.tar.bz2 

RUN apk del build-dependencies

RUN apk --update --no-cache add git

# Set up the compiler path
ENV PATH="/home/dev/gcc-arm-none-eabi-10-2020-q4-major/bin:${PATH}"
ENV PATH="/home/dev/gcc-arm-none-eabi-10-2020-q4-major/lib/gcc/arm-none-eabi/10.2.1/:${PATH}"

RUN mkdir ~/.local 
RUN mkdir ~/.local/bin
RUN cp --symbolic-link /home/dev/gcc-arm-none-eabi-10-2020-q4-major/bin/* ~/.local/bin/


