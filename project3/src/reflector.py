import argparse
from scapy.all import *
from scapy.all import sr1
from scapy.all import TCP, UDP, IP, ARP

# add parser for command line args
parser = argparse.ArgumentParser()
parser.add_argument('--interface')
parser.add_argument('--victim-ip')
parser.add_argument('--victim-ethernet')
parser.add_argument('--reflector-ip')
parser.add_argument('--reflector-ethernet')
args = parser.parse_args()