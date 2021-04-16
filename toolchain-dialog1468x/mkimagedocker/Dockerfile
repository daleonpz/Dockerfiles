FROM ubuntu:20.04

MAINTAINER Daniel Paredes <daleonpz@gmail.com>

# Set up a tools dev directory
WORKDIR /home/dev

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get -y update && apt-get -y upgrade
RUN apt-get -y install wget

COPY binaries /usr/toolchain/binaries

RUN chmod +x /usr/toolchain/binaries/mkimage

