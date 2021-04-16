# FROM frolvlad/alpine-glibc:alpine-3.9
FROM i386/ubuntu

MAINTAINER Daniel Paredes <daleonpz@gmail.com>

# Set up a tools dev directory
WORKDIR /home/dev

RUN apt-get -y update && apt-get -y upgrade
RUN apt-get -y install wget

RUN wget https://software-dl.ti.com/codegen/esd/cgt_public_sw/MSP430/20.2.2.LTS/ti_cgt_msp430_20.2.2.LTS_linux_installer_x86.bin && ls -la && pwd

RUN chmod +x ./ti_cgt_msp430_20.2.2.LTS_linux_installer_x86.bin 
RUN echo | /home/dev/ti_cgt_msp430_20.2.2.LTS_linux_installer_x86.bin --prefix /usr/toolchain/

RUN apt-get install -y rake

COPY ccs_base /usr/toolchain/ccs_base/

COPY tools /usr/toolchain/tools/
