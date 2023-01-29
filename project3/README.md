# Project 3: Reflector Assignment

### Purpose

This is a Python script that uses the Scapy library to perform a network attack called ARP spoofing. The script takes in several command line arguments, such as the network interface to use, the victim's IP and Ethernet addresses, and the reflector's IP and Ethernet addresses. 

The script defines a function called packet_sniffer() that uses Scapy's sniff() function to listen for all packets on the specified network interface and passes each packet to a callback function packet_callback().

The packet_callback() function first checks if the packet is an ARP packet by checking if the ARP layer is present in the packet. If it is, it checks whether the packet is targeted at the victim's IP or the reflector's IP. If it is targeted at the victim's IP, the script creates a new ARP packet with the source IP set to the victim's IP and the destination IP set to the packet's source IP. It also sets the source and destination Ethernet addresses accordingly. Then, it sends the packet. The same process is repeated if the packet is targeted at the reflector's IP.

If the packet is not an ARP packet, the script checks if the IP layer is present in the packet. If it is, it checks whether the packet is targeted at the victim's IP or the reflector's IP. If it is targeted at the victim's IP, the script creates a new IP packet with the source IP set to the reflector's IP and the destination IP set to the packet's source IP. Then, it sends the packet. The same process is repeated if the packet is targeted at the reflector's IP.

### Getting Started

1. Build the image with ubuntu 18.04

```sh
docker build . -t ubuntu:reflector
```

2. Run container

```sh
docker run --rm --privileged -it ubuntu:reflector
```

3. Test

```sh
root@4ec440285fa4:/usr/src# ./test_reflector.sh
```
