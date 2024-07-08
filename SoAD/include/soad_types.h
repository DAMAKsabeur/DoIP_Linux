#ifndef SOAD_TYPES_H
#define SOAD_TYPES_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // for sleep()

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

typedef struct 
{
    uint8_t proto_version;
    uint8_t inverse_proto_version;
	uint16_t type;
    uint32_t length;
} doip_header_t;

typedef struct 
{
	doip_header_t doip_header;
    uint8_t payload[256];
} doip_msg_t;

typedef enum
{
    IP_TCP_PROTOCOL       =0x00,
    IP_UDP_PROTOCOL       =0x01,
    IP_MULTICAST_PROTOCOL =0x02,
    IP_LAST_PROTOCOL
}ip_protocol_t;

typedef struct 
{
    int fd;
    struct sockaddr_in addr;
    int port;
} soad_ctx_t;


#endif /* SOAD_TYPES_H */
