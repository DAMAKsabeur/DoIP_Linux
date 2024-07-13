#ifndef SOAD_H
#define SOAD_H
#include "soad_error_code.h"
#include "soad_types.h"


soad_handler_t soad_open_udp_Socket(void* read_callback, ip_protocol_t protocol, char* ip ,uint32_t port );
soad_handler_t soad_open_tcp_Socket(void* read_callback, ip_protocol_t protocol, char* ip ,uint32_t port );
int soad_send_msg(soad_handler_t soad_handler, uint8_t* msg , size_t size, int port);
#endif /* SOAD_H */
