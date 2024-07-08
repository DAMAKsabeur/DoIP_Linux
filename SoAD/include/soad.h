#ifndef SOAD_H
#define SOAD_H
#include "soad_error_code.h"
#include "soad_types.h"
#define soad_handler uint32_t  
int soad_initalize();
soad_ctx_t soad_openSocket(ip_protocol_t protocol, char* ip ,uint32_t port );
soad_ctx_t soad_openRXSocket(ip_protocol_t protocol, char* ip ,uint32_t port );
int soad_sendmsg(soad_ctx_t* soad_ctx, uint8_t* msg , size_t size, int port);
int soad_recieve(soad_ctx_t* soad_ctx, uint8_t* msg , size_t* size, int* port);
soad_closeSocket(soad_ctx_t *soad_ctx);
int soad_finilize();

#endif /* SOAD_H */
