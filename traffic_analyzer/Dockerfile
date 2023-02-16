FROM ubuntu:18.04

RUN apt-get update && apt-get install -y python3 python3-pip iproute2 net-tools tcpdump iputils-ping \ 
  && apt-get --no-install-recommends install -y build-essential=12.4ubuntu1 && apt-get clean && rm -rf /var/lib/apt/lists/*

COPY ./src /usr/src

WORKDIR /usr/src