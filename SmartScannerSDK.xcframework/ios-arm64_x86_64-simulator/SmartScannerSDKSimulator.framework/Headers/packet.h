/*
 * This file is (c) 2018, 2019 Securing SAM Ltd.
 *
 * It may not be reproduced, used, sold or transferred to any third party
 * without the prior written consent of Securing SAM Ltd. All rights reserved.
 */

#ifndef _SAM_PACKET_H_INCLUDED
#   define _SAM_PACKET_H_INCLUDED

#   include <string.h>
#   include <netinet/in.h>
#   include <netinet/ip.h>
#   include <netinet/ip6.h>
#   include <netinet/tcp.h>
#   include <netinet/udp.h>
#   include <netinet/ip_icmp.h>
#   include <arpa/inet.h>
#   include <sys/types.h>
#   include "errors.h"
#   include <sys/socket.h>
#   include <stdbool.h>
#   include <errno.h>

#ifndef APPLE
#define APPLE
#endif

#ifdef APPLE


struct iphdr 
  { 
    unsigned int ihl:4;
    unsigned int version:4;
    u_int8_t tos;
    u_int16_t tot_len;
    u_int16_t id;
    u_int16_t frag_off;
    u_int8_t ttl;
    u_int8_t protocol;
    u_int16_t check;
    u_int32_t saddr;
    u_int32_t daddr;
    /*The options start here. */
  };

struct icmphdr
{
  u_int8_t type;		/* message type */
  u_int8_t code;		/* type sub-code */
  u_int16_t checksum;
  union
  {
    struct
    {
      u_int16_t	id;
      u_int16_t	sequence;
    } echo;			/* echo datagram */
    u_int32_t	gateway;	/* gateway address */
    struct
    {
      u_int16_t	__unused;
      u_int16_t	mtu;
    } frag;			/* path mtu discovery */
  } un;
};

typedef u_int16_t __u16;
typedef u_int32_t __u32;
typedef u_int16_t __be16;
typedef u_int16_t __sum16;

struct udphdr2 {
	__be16	source;
	__be16	dest;
	__be16	len;
	__sum16	check;
};



struct tcphdr2 {
    __u16   source;
    __u16   dest;
    __u32   seq;
    __u32   ack_seq;
    __u16   res1:4,
        doff:4,
        fin:1,
        syn:1,
        rst:1,
        psh:1,
        ack:1,
        urg:1,
        ece:1,
        cwr:1;
    __u16   window;
    __u16   check;
    __u16   urg_ptr;
};

#define tcphdr tcphdr2
#define udphdr udphdr2

#define s6_addr __u6_addr.__u6_addr8
#define s6_addr8 __u6_addr.__u6_addr8
#define s6_addr16 __u6_addr.__u6_addr16
#define s6_addr32 __u6_addr.__u6_addr32

#endif /* APPLE */

#define SAM_LEVEL_ERROR
#define SAM_DEBUG(x)
#define SAM_LOG(x, y)
#define SAM_LOG_DEBUG(x)

enum sam_packet_peer {
    SAM_PACKET_PEER_DST,
    SAM_PACKET_PEER_SRC
};

struct sam_ip_addr {
    /* Specify whether the address is AF_INET/IF_INET6 */
    sa_family_t addr_family;

    union {
        struct in_addr  ip;
        struct in6_addr ip6;
    } addr;
};

#define sia_ip_addr  addr.ip
#define sia_ip6_addr addr.ip6

struct sam_raw_ip_addr {
    /* Specify whether the address is AF_INET/IF_INET6 */
    sa_family_t addr_family;

    union {
        in_addr_t *ip;
        uint8_t  *ip6;
    } raw_addr;
};

#define sria_raw_ip_addr  raw_addr.ip
#define sria_raw_ip6_addr raw_addr.ip6

struct sam_packet {
    unsigned char *buf;
    union {
        struct iphdr *ip;
        struct ip6_hdr *ip6;
        unsigned char *any;
    } l3;
    union {
        struct tcphdr *tcp;
        struct udphdr *udp;
        struct icmphdr *icmp;
        unsigned char *any;
    } l4;
    unsigned char *l5;
    const unsigned char *end;
};

/** Returns the L3 protocol of a packet */
#   define sam_packet_l3_proto(pkt) \
    (((pkt)->l3.ip->version == 4) ? AF_INET : AF_INET6)

/** Returns the L4 protocol of a packet */
#   define sam_packet_l4_proto(pkt) \
    ((sam_packet_l3_proto(pkt) == AF_INET) ? \
                                (pkt)->l3.ip->protocol : (pkt)->l3.ip6->ip6_nxt)

/**
 * @brief Locates L3, L4 and L5 data in an IPv4 or IPv6 packet and verifies its
 *        sanity
 * @param   pkt     The parsed packet
 * @param   buf     The raw packet data, L3 and above
 * @param   len     The raw packet size
 * @return A sam_errno_t
 */
int sam_packet_parse(struct sam_packet *pkt,
                     const unsigned char *buf,
                     const size_t len);

/**
 * Set the checksum of an IPv4 or IPv6 packet
 */
int sam_packet_fix_l3_checksum(struct sam_packet *pkt);

/**
 * Set the checksum of a TCP or UDP packet
 */
int sam_packet_fix_l4_checksum(struct sam_packet *pkt);

/**
 * Set both L3 and L4 checksums of a packet
 */
int sam_packet_fix_checksums(struct sam_packet *pkt);

/**
 * @brief compare 2 ips
 * @param   a     first ip to compare
 * @param   b     second ip to compare
 *
 * @return zero in case two ip addresses are equals, positive number if a > b
 *         and negative number if b > a
 */
static inline int sam_ip_addr_cmp(const struct sam_ip_addr *a,
                                  const struct sam_ip_addr *b)
{
    if (a->addr_family != b->addr_family) {
        return a->addr_family -  b->addr_family;
    }

    if (a->addr_family == AF_INET) {
        if (a->addr.ip.s_addr > b->addr.ip.s_addr) {
            return 1;
        } else if (a->addr.ip.s_addr < b->addr.ip.s_addr) {
            return -1;
        }
        return 0;
    }

    return memcmp(&a->addr.ip6, &b->addr.ip6, sizeof(a->addr.ip6));
}


/**
 * @brief converts the ip_addr to string representation
 * @param   ip_addr    ip_addr to convert to string
 * @param   ip_str     output buffer to write ip string to.
 * @param   ip_str_len output buffer len.
 *
 * @return SAM_OK on success or sam_err_t in case of error.
 */
static inline int sam_ip_addr_to_str(struct sam_ip_addr *ip_addr,
                                     char *ip_str,
                                     size_t ip_str_len)
{
    switch (ip_addr->addr_family) {
    case AF_INET:
        if (!inet_ntop(AF_INET, &ip_addr->addr.ip, ip_str, ip_str_len)) {
            return sam_syserr2samerr(errno);
        }
        break;
    case AF_INET6:
        if (!inet_ntop(AF_INET6, &ip_addr->addr.ip6, ip_str, ip_str_len)) {
            return sam_syserr2samerr(errno);
        }
        break;
    default:
        return SAM_EINVAL;
    }

    return SAM_OK;
}

/**
 * @brief Efficiently initializes a struct sam_packet for a copied packet
 * @param   buf     The copied packet contents
 * @param   len     The packet size
 * @param   from    The parsed packet
 * @param   to      A copy of from that points to the copied contents
 */
static inline void sam_packet_rebase(const unsigned char *buf,
                                     const size_t len,
                                     const struct sam_packet *from,
                                     struct sam_packet *to)
{
    to->buf = (unsigned char *)buf;
    to->l3.any = to->buf + (from->l3.any - from->buf);
    to->l4.any = to->buf + (from->l4.any - from->buf);
    to->l5 = to->buf + (from->l5 - from->buf);
    to->end = to->buf + len;
}

/**
 * @brief Copies a packet
 * @param[in]   pkt     The packet to copy
 * @param[out]  copy    The copy
 */
int sam_packet_copy(const struct sam_packet *pkt, struct sam_packet *copy);

/**
 * Verifies the checksum of a packet
 */
int sam_packet_verify_checksum(const struct sam_packet *pkt);

/**
 * Closes the TCP session a packet belongs to
 */
int sam_packet_kill_tcp_session(struct sam_packet *pkt);

/**
 * @brief Creates a raw TCP socket for sending crafted packets
 */
int sam_packet_raw_tcp_socket(int *s);

/**
 * Turn the rst flag of tcp packet on.
 */
int sam_packet_tcp_turn_rst_on(struct sam_packet *pkt);

/**
 * @brief   Parse ip address of given packet according to packet family and
 *          given sam_ip_addr_peer
 * @param   pkt       The packet to parse ip_addr from.
 * @param   ip_addr   The struct to fill ip_addr to.
 * @param   addr_peer Specify if the parse the ip_addr of the src/dst
 *
 * @return  Zero on success or sam_errno_t on error
 */
int sam_packet_extract_addr(const struct sam_packet *pkt,
                            struct sam_ip_addr *ip_addr,
                            enum sam_packet_peer packet_peer);

bool sam_packet_parse_ip(char *str, size_t size, struct sam_ip_addr *ip);

/**
  * @brief copy ip address from src to dest
  * @param[out] dst destination buffer of copied ip
  * @param[in]  src copies the ip from src
  * @returns Zero on success or samm_errno_t on error
  */
void sam_copy_sam_addr(struct sam_ip_addr *dst, struct sam_ip_addr *src);

#endif
