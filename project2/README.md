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

3. Test container

```sh
curl localhost:3000
```

### Example Usage

#### execute `ls`

```sh
# execute
curl localhost:3000/exec/ls
```

```sh
# response
Makefile
README
main.c
normal_web_server
submission.tar.gz
```

#### execute `ls -la`

```sh
# execute
curl localhost:3000/exec/ls%20-la
```

```sh
# response
total 56
drwxr-xr-x 1 root root  4096 Jan 22 06:23 .
drwxr-xr-x 1 root root  4096 Dec 15 14:22 ..
-rw-r--r-- 1 root root  6148 Jan 22 02:53 .DS_Store
-rw-r--r-- 1 root root   121 Jan 20 08:33 Makefile
-rw-r--r-- 1 root root    49 Jan 20 07:44 README
-rw-r--r-- 1 root root  5683 Jan 22 06:22 main.c
-rwxr-xr-x 1 root root 14576 Jan 22 06:23 normal_web_server
-rw-r--r-- 1 root root  1770 Jan 22 02:53 submission.tar.gz
```

#### or from the browser

<img src="./uploads/request_headers.png" alt="request_headers" />
<img src="./uploads/response.png" alt="response" />
