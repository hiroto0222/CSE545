# Project 3: Reflector Assignment

### Purpose

The goal of this project is to create a “reflector” that will relaunch attacks sent to a given IP address and ethernet address to the IP address that sent the attack. This acts as a mirror, such that when an adversary is port scanning a network, they will actually be port scanning themselves. When they launch an exploit at the reflector, the attack will be reflected back at them. To accomplish this task, you will improve your skills at network programming: creating raw packets, implementing ARP, and other low-level networking skills.

### Getting Started

1. Build the image with ubuntu 18.04

```sh
docker build . -t ubuntu:web-server
```

2. Run container and expose port 3000 on OS port 3000

```sh
docker run --rm -it -p 3000:3000 ubuntu:web-server
```

3. Test container

```sh
curl localhost:3000
```
