# Project 2: Backdoor Web Server Assignment
### Purpose
A critical part of establishing persistence on a system is to leave a “backdoor” that allows the hacker access to the system at a later date, without exploiting the same vulnerabilities (they may be fixed in the meantime). In this assignment, you will explore writing a backdoor that pretends to be a web server. A web server makes a great pretense for a backdoor because web traffic is so prevalent it does not raise alarms and ports 80 and 443 are frequently permitted through firewalls. In addition, you will become familiar with network programming in C with only the C standard library as well as reading technical specifications.

Your goal is to create, in C, a minimal HTTP 1.1 server, based on RFC 2616 from scratch, without using any libraries except for the C standard library.

### Getting Started
1. Build the image with ubuntu 18.04
```sh
docker build . -t ubuntu:web-server
```

2. Run container and expose port 3000 on OS port 3000
```sh
docker run --rm -it -p 3000:3000 ubuntu:web-server
```