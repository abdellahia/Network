 /*
  * Copyright (C) 2017 Kaspar Schleiser <kaspar@schleiser.de>
  *
  * This file is subject to the terms and conditions of the GNU Lesser
  * General Public License v2.1. See the file LICENSE in the top level
  * directory for more details.
  */
 
 #ifndef NET_SOCK_DNS_H
 #define NET_SOCK_DNS_H
 
 #include <errno.h>
 #include <stdint.h>
 #include <unistd.h>
 
 #include "netinet/udp.h"
 
 #ifdef __cplusplus
 extern "C" {
 #endif
 
struct sock_dns_hdr_t {
     uint16_t id;        
     uint16_t flags;     
     uint16_t qdcount;   
     uint16_t ancount;   
     uint16_t nscount;   
     uint16_t arcount;   
     uint8_t payload[];  
 } ;
 
 #define DNS_TYPE_A              (1)
 #define DNS_TYPE_AAAA           (28)
 #define DNS_CLASS_IN            (1)
 
 #define SOCK_DNS_PORT           (53)
 #define SOCK_DNS_RETRIES        (2)
 
 #define SOCK_DNS_MAX_NAME_LEN   (64U)       /* we're in embedded context. */
 #define SOCK_DNS_QUERYBUF_LEN   (sizeof(sock_dns_hdr_t) + 4 + SOCK_DNS_MAX_NAME_LEN)
 
 int sock_dns_query(const char *domain_name, void *addr_out, int family);
 
 //extern sock_udp_ep_t sock_dns_server;
 
 #ifdef __cplusplus
 }
 #endif
 
 #endif /* NET_SOCK_DNS_H */
 
