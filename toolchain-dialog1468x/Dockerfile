FROM i386/ubuntu

MAINTAINER Daniel Paredes <daleonpz@gmail.com>

# Set up a tools dev directory
WORKDIR /home/dev

RUN apt-get -y update && apt-get -y upgrade
RUN apt-get -y install wget
RUN apt-get install -y rake
RUN apt-get -y install gcovr
RUN apt-get -y install gcc

#gem install ceedling

COPY GCC /usr/toolchain/GCC/

COPY boards /usr/toolchain/boards/

COPY tools /usr/toolchain/tools/
