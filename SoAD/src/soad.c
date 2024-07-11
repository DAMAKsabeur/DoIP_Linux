#include "soad.h"
#include "doip_types.h"
#include <pthread.h>
#define PORT 13400

static void *read_udp_fct(void *arg)
{

	int count = 0x00;
	uint8_t buffer [256] = {0x00};
	soad_ctx_t* soad_ctx_p = (soad_ctx_t*)arg;
	soad_handler_t soad_handler = soad_ctx_p;
    int addr_len = sizeof(struct sockaddr);
    int rc = 0x00;

    callback_fct pf= (callback_fct)soad_ctx_p->callback;
    
    printf("pf = %p \n",pf);
	while (1) {
        count = recvfrom(soad_ctx_p->sock, &buffer, sizeof(buffer), 0, (struct sockaddr*)&soad_ctx_p->client_addr, &addr_len);
        printf("count = %d\n", count);
        if (count != 0)
        {
			for (int i=0x00; i<10 ; i++)
			{
				printf("buffer[%d] = 0x%x\n",i,buffer[i]);
			}
			rc =pf(&buffer, 0, NULL, soad_handler);
		}
		usleep(500);
    }
    return NULL;
}

static void *read_tcp_fct(void *arg)
{

	printf("Thread read_tcp_fct\n");
	int count = 0x00;
	uint8_t buffer [256] = {0x00};
	soad_ctx_t* soad_ctx_p = (soad_ctx_t*)arg;
	soad_handler_t soad_handler = soad_ctx_p;
    int addr_len = sizeof(struct sockaddr);
    int rc = 0x00;

    callback_fct pf= (callback_fct)soad_ctx_p->callback;
    
    printf("pf = %p \n",pf);
	while (1) {
        //~ count = recvfrom(soad_ctx_p->sock, &buffer, sizeof(buffer), 0, (struct sockaddr*)&soad_ctx_p->client_addr, &addr_len);
        count = read(soad_ctx_p->connfd, &buffer, sizeof(buffer)); 
        printf("count = %d\n", count);
        if (count != 0)
        {
			for (int i=0x00; i<10 ; i++)
			{
				printf("buffer[%d] = 0x%x\n",i,buffer[i]);
			}
			rc =pf(&buffer, 0, NULL, soad_handler);
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
    printf("bind %d\n",soad_ctx->server_addr.sin_port);
    ret = bind(soad_ctx->sock, (struct sockaddr*)&soad_ctx->server_addr, addr_len);																																												
    if (ret < 0) {
      perror("bind error\n");
    }
    soad_ctx->callback = callback;
	pthread_create(&th, &attr, read_udp_fct, soad_ctx);
    return((uint32_t)soad_ctx);
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
    else
        printf("Socket successfully created..\n"); 
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
    else
        printf("Socket successfully binded..\n"); 
   
    // Now server is ready to listen and verification 
    if ((listen(soad_ctx->sock, 5)) != 0) { 
        printf("Listen failed...\n"); 
    } 
    else
        printf("Server listening..\n"); 
    len = sizeof(struct sockaddr); 
   
    // Accept the data packet from client and verification 
    soad_ctx->connfd = accept(soad_ctx->sock, (struct sockaddr*)&soad_ctx->client_addr, &len); 
    if (soad_ctx->connfd < 0) { 
        printf("server accept failed...\n"); 
    } 
    else
        printf("server accept the client...\n"); 
    
    soad_ctx->callback = callback;
    pthread_create(&th, &attr, read_tcp_fct, soad_ctx);
    return(soad_ctx);
}

int soad_send_udp_msg(soad_handler_t soad_handler, uint8_t* msg , size_t size, int port)
{
	int result = 0x00;
	doip_msg_t doip_msg;
	memcpy(&doip_msg, msg, size);
	soad_ctx_t* soad_ctx = (soad_ctx_t*)soad_handler;
	printf("hello to soad_send_udp_msg \n");
    sendto(soad_ctx->sock, &doip_msg, 33 + sizeof(doip_header_t), 0, (struct sockaddr*)&soad_ctx->client_addr, sizeof(struct sockaddr));
	return (result);
}

int soad_send_tcp_msg(soad_ctx_t* soad_ctx, uint8_t* msg , size_t size, int port)
{
	int result = 0x00;
	return (result);
}