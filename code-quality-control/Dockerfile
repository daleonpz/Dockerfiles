FROM frolvlad/alpine-glibc:alpine-3.12
MAINTAINER Daniel Paredes <daleonpz@gmail.com>

# Set up a tools dev directory
WORKDIR /home/dev

# Installing bash
RUN apk add --update --no-cache bash

# Cyclomatic Complexity Tool
RUN apk add --update --no-cache python3 py3-pip
RUN pip install lizard
RUN lizard --version

# Static code analyzer 
RUN apk add --update --no-cache cppcheck 
RUN cppcheck --version

# Style formatter
RUN apk add --update --no-cache astyle
RUN astyle --version 

COPY checkers /usr/checkers/


