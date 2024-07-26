#include "soad.h"
#include "doip_types.h"
#include <pthread.h>
#include <stdbool.h>

#define PORT 13400

static int soad_send_tcp_msg(soad_handler_t soad_handler, uint8_t* msg , size_t size, int port);
static int soad_send_udp_msg(soad_handler_t soad_handler, uint8_t* msg , size_t size, int port);

static void *read_udp_fct(void *arg)
{

	int count = 0x00;
	uint8_t buffer [256] = {0x00};
	soad_ctx_t* soad_ctx_p = (soad_ctx_t*)arg;
	soad_handler_t soad_handler = (soad_handler_t)soad_ctx_p;
    int addr_len = sizeof(struct sockaddr);
    int rc = 0x00;

    callback_fct pf= (callback_fct)soad_ctx_p->callback;

	while (true) {
        count = recvfrom(soad_ctx_p->sock, &buffer, sizeof(buffer), 0, (struct sockaddr*)&soad_ctx_p->client_addr, &addr_len);
        if (count != 0)
        {
			rc =pf(soad_handler, buffer,sizeof(buffer));
		}
		usleep(500);
    }
    return NULL;
}

static void *read_tcp_fct(void *arg)
{

	int count = 0x00;
	uint8_t buffer [256] = {0x00};
	soad_ctx_t* soad_ctx_p = (soad_ctx_t*)arg;
	soad_handler_t soad_handler = (soad_handler_t)soad_ctx_p;
    int addr_len = sizeof(struct sockaddr);
    int rc = 0x00;

    callback_fct pf= (callback_fct)soad_ctx_p->callback;

	while (true) {
        count = read(soad_ctx_p->connfd, &buffer, sizeof(buffer)); 
        if (count != 0)
        {
			rc =pf(soad_handler, buffer, sizeof(buffer));
		}
		usleep(500);
    }
    return NULL;
}

soad_handler_t soad_open_udp_Socket(void* const  callback, ip_protocol_t protocol, char* ip ,uint32_t port )
{
    soad_ctx_t* soad_ctx;
    int yes = 1;
    pthread_t th;
    pthread_attr_t attr;
    
    int addr_len;
    int count;
    int ret;
    fd_set readfd;

    soad_ctx = calloc(1, sizeof(soad_ctx_t));
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    soad_ctx->sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (soad_ctx->sock < 0) {
      perror("sock error\n");
    }
    
    addr_len = sizeof(struct sockaddr_in);
    
    memset((void*)&soad_ctx->server_addr, 0, addr_len);
    soad_ctx->server_addr.sin_family = AF_INET;
    soad_ctx->server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    soad_ctx->server_addr.sin_port = htons(PORT);
    ret = bind(soad_ctx->sock, (struct sockaddr*)&soad_ctx->server_addr, addr_len);																																												
    if (ret < 0) {
      perror("bind error\n");
    }
    soad_ctx->ip_protocol = IP_UDP_PROTOCOL;
    soad_ctx->callback = callback;
	pthread_create(&th, &attr, read_udp_fct, soad_ctx);
    return((soad_handler_t)soad_ctx);
}

soad_handler_t soad_open_tcp_Socket(void* const  callback, ip_protocol_t protocol, char* ip ,uint32_t port )
{
    soad_ctx_t* soad_ctx;
    pthread_t th;
    pthread_attr_t attr;
    soad_ctx = calloc(1, sizeof(soad_ctx_t));
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    int  len , addr_len; 
   
    // socket create and verification 
    soad_ctx->sock = socket(AF_INET, SOCK_STREAM, 0); 
    if (soad_ctx->sock == -1) { 
        printf("socket creation failed...\n"); 
    } 

    addr_len = sizeof(struct sockaddr_in);
    
    memset((void*)&soad_ctx->server_addr, 0, addr_len);
   
    // assign IP, PORT 
    soad_ctx->server_addr.sin_family = AF_INET; 
    soad_ctx->server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    soad_ctx->server_addr.sin_port = htons(PORT); 
   
    // Binding newly created socket to given IP and verification 
    if ((bind(soad_ctx->sock, (struct sockaddr*)&soad_ctx->server_addr, sizeof(soad_ctx->server_addr))) != 0) { 
        printf("socket bind failed...\n"); 
    } 
   
    // Now server is ready to listen and verification 
    if ((listen(soad_ctx->sock, 5)) != 0) { 
        printf("Listen failed...\n"); 
    } 

    len = sizeof(struct sockaddr); 
   
    // Accept the data packet from client and verification 
    soad_ctx->connfd = accept(soad_ctx->sock, (struct sockaddr*)&soad_ctx->client_addr, &len); 
    if (soad_ctx->connfd < 0) { 
        printf("server accept failed...\n"); 
    } 
    
    soad_ctx->callback = callback;
    pthread_create(&th, &attr, read_tcp_fct, soad_ctx);
    soad_ctx->ip_protocol = IP_TCP_PROTOCOL;
    return((soad_handler_t)soad_ctx);
}

int soad_send_msg(soad_handler_t soad_handler, uint8_t* msg , size_t size, int port)
{
	soad_ctx_t* soad_ctx = (soad_ctx_t*)soad_handler;
	int result = 0x00;
	if (IP_UDP_PROTOCOL == soad_ctx->ip_protocol)
	{
		 result = soad_send_udp_msg(soad_handler ,msg ,size ,port);
	}
	else
	{
		 result = soad_send_tcp_msg(soad_handler , msg , size, port);
	}
	return(result);
}

static int soad_send_udp_msg(soad_handler_t soad_handler, uint8_t* msg , size_t size, int port)
{
	int result = 0x00;
	doip_msg_t doip_msg;
	
	memcpy(&doip_msg, msg, size);
	soad_ctx_t* soad_ctx = (soad_ctx_t*)soad_handler;
	size = htonl(doip_msg.doip_header.length);
    sendto(soad_ctx->sock, &doip_msg, size + sizeof(doip_header_t), 0, (struct sockaddr*)&soad_ctx->client_addr, sizeof(struct sockaddr));
	return (result);
}

static int soad_send_tcp_msg(soad_handler_t soad_handler, uint8_t* msg , size_t size, int port)
{
	int result = 0x00 ,count =0x00;
	doip_msg_t doip_msg;
	memcpy(&doip_msg, msg, size);
	soad_ctx_t* soad_ctx = (soad_ctx_t*)soad_handler;
	size = htonl(doip_msg.doip_header.length);
	count = write(soad_ctx->connfd, &doip_msg, size + sizeof(doip_header_t)); 
	return (result);
}
