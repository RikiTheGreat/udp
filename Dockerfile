# Use Ubuntu latest as base image
FROM ubuntu:latest
LABEL authors="mahdi"


RUN apt-get update && apt-get install -y clang cmake make

COPY . /usr/src/udp/
WORKDIR /usr/src/udp/

RUN cmake -Bbuild -H.

WORKDIR build
RUN make

CMD ["./udp_app"]