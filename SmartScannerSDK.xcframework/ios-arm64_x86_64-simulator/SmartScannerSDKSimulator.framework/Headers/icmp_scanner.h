//
//  syn_scanner.h
//  SamVPNKit
//
//  Created by Artium on 17/11/2021.
//

#ifndef syn_scanner_h
#define syn_scanner_h

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

#include "packet.h"



struct icmp_response{
    char *ip;
    int ttl;
} ;

int sam_syn_scanner_init(void);

int sam_send_icmp(int fd, char *addr);

int sam_read(int fd, void *result);

int sam_icmp_scanner_loop(char* my_ip_addr, uint32_t local_netmask);
short extract_txid(char *bytes);

#endif /* syn_scanner_h */
