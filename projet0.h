#ifndef _PROJET0_H_
#define _PROJET0_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pcap.h>
#include <ctype.h>
#include <string.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <netinet/in.h>

//Protocols
#define	IS_IP 0x0800
#define IS_ARP 0x0806
#define IS_IMAP 143
#define IS_POP 110
#define IS_FTP 21
#define IS_TELNET 23
#define IS_SCTP 132
#define IS_ICMP 0x01
#define IS_TCP 0x06
#define IS_UDP 0x11
#define IS_IP6 0x86DD
#define IS_BOOTP1 67
#define IS_BOOTP2 68
#define IS_DNS 53
#define IS_HTTP 80
#define IS_SMTP 25

//files
#include "verbosity.h"
#include "ascii.h"
#include "f_telnet.c"
#include "f_imap.c"
#include "f_pop.c"
#include "f_ftp.c"
#include "f_sctp.c"
#include "f_icmp.c"
#include "f_smtp.c"
#include "f_dns.c"
#include "f_bootp.c"
#include "f_http.c"
#include "f_udp.c"
#include "f_tcp.c"
#include "f_ipv6.c"
#include "f_arp.c"
#include "f_ip.c"
#include "f_ethernet.c"

//void what_next(void);
void ascii(const u_char* packet, int* size, int size_c);
int f_ethernet(const u_char* packet, int* size);
int f_ip(const u_char* packet, int* size , int* size_c);
int f_arp(const u_char* packet, int* size);
int f_ipv6(const u_char* packet, int* size);
void f_udp(const u_char* packet, int* size) ;
void f_tcp(const u_char* packet, int* size, int* size_c);
void f_bootp(const u_char* packet, int* size);
void f_dns(const u_char* packet, int* size);
void f_http(const u_char* packet, int* size, int* size_c);
void f_smtp(const u_char* packet, int* size, int* size_c);
void f_ftp(const u_char* packet, int* size, int* size_c);
int f_icmp(const u_char* packet, int* size);
void f_pop(const u_char* packet, int* size, int* size_c);
int f_sctp(const u_char* packet, int* size);
void f_imap(const u_char* packet, int* size, int* size_c);
void f_telnet(const u_char* packet, int size, int size_c);




#endif
