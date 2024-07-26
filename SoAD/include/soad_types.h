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
#define soad_handler_t uint64_t  

typedef enum
{
    IP_TCP_PROTOCOL       =0x00,
    IP_UDP_PROTOCOL       =0x01,
    IP_MULTICAST_PROTOCOL =0x02,
    IP_LAST_PROTOCOL
}ip_protocol_t;

typedef int (*callback_fct)(soad_handler_t soad_handler, uint8_t* doip_msg, ip_protocol_t src_protocole);

typedef struct 
{
    int sock;
    int connfd;
    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;
    ip_protocol_t ip_protocol;
    callback_fct callback;
} soad_ctx_t;

#endif /* SOAD_TYPES_H */
