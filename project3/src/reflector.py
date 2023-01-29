#!/usr/bin/env python3

import argparse
from scapy.all import *
from scapy.all import TCP, UDP, IP, ARP

# add parser for command line args
parser = argparse.ArgumentParser()
parser.add_argument('--interface')
parser.add_argument('--victim-ip')
parser.add_argument('--victim-ethernet')
parser.add_argument('--reflector-ip')
parser.add_argument('--reflector-ethernet')
args = parser.parse_args()

interface = args.interface
victim_ip = args.victim_ip
victim_ethernet = args.victim_ethernet
reflector_ip = args.reflector_ip
reflector_ethernet = args.reflector_ethernet


def packet_sniffer():
    # sniff all packets on network interface
    sniff(iface=interface, prn=packet_callback, count=0)


# victim IP of 10.0.0.3 and a reflector IP of 10.0.0.4
def packet_callback(packet):
    # handle ARP
    if ARP in packet:
        # check if attacker -> victim
        if (packet[ARP].pdst == victim_ip):
            res = ARP(psrc=victim_ip, pdst=packet[ARP].psrc, op=2, hwsrc=victim_ethernet, hwdst=packet[ARP].hwdst)
            send(res)
        
        if (packet[ARP].pdst == reflector_ip):
            res = ARP(psrc=reflector_ip, pdst=packet[ARP].psrc, op=2, hwsrc=reflector_ethernet, hwdst=packet[ARP].hwdst)
            send(res)
    
    # handle IP, TCP, UDP
    elif IP in packet:
        if (packet[IP].dst == victim_ip):
            ip_packet = packet.getlayer(IP)
            # reflect packet: reflector_ip -> src_ip
            ip_packet[IP].src, ip_packet[IP].dst = reflector_ip, packet[IP].src
            
            # delete chksum
            del ip_packet[IP].chksum
            if TCP in ip_packet:
                del packet[TCP].chksum
            if UDP in ip_packet:
                del packet[UDP].chksum
            
            send(ip_packet)
        
        if (packet[IP].dst == reflector_ip):
            ip_packet = packet.getlayer(IP)
            # reflect packet: vitim_ip -> src_ip
            ip_packet[IP].src, ip_packet[IP].dst = victim_ip, packet[IP].src
            
            # delete chksum
            del ip_packet[IP].chksum
            if TCP in ip_packet:
                del packet[TCP].chksum
            if UDP in ip_packet:
                del packet[UDP].chksum
            
            send(ip_packet)


def main():
    packet_sniffer()


if __name__ == "__main__":
    main()