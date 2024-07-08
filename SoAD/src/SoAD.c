#include "soad.h"

doip_msg_t doip_msg = {0x00};

int soad_initalize()
{
	//~ // !!! If test requires, make these configurable via args
    //~ //
    //~ const int delay_secs = 1;
    //~ const char *message = "Hello, World!";
    //~ doip_msg.doip_header.proto_version = 0x02;
    //~ doip_msg.doip_header.inverse_proto_version = 0xFD;
    //~ doip_msg.doip_header.type = ntohs(0x0004);
    //~ memcpy(doip_msg.payload , message , strlen(message));
    //~ memset(doip_msg.payload, 0xAA , 17); /* VNI */
    //~ doip_msg.payload[17] = 0x0E;
    //~ doip_msg.payload[18] = 0x1E;
    //~ doip_msg.doip_header.length =  ntohl(33);
    //~ // create what looks like an ordinary UDP socket
    //~ //
    //~ soad_ctx.fd = socket(AF_INET, SOCK_DGRAM, 0);
    //~ if (soad_ctx.fd < 0) {
        //~ perror("socket");
        //~ return 1;
    //~ }
	//~ int on=1;
	//~ setsockopt(soad_ctx.fd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
    //~ // set up destination address
    //~ //
    //~ memset(&soad_ctx.addr, 0, sizeof(soad_ctx.addr));
    //~ soad_ctx.addr.sin_family = AF_INET;
    //~ soad_ctx.addr.sin_addr.s_addr = inet_addr("10.0.2.255");
    //~ soad_ctx.addr.sin_port = htons(13400);

      //~ // now just sendto() our destination!
    //~ //
    //~ for (int i=0 ; i<100000 ; i++) {
        //~ char ch = 0;
        //~ int nbytes = sendto(
            //~ soad_ctx.fd,
            //~ &doip_msg,
            //~ 33 + sizeof(doip_header_t),
            //~ 0,
            //~ (struct sockaddr*) &soad_ctx.addr,
            //~ sizeof(soad_ctx.addr)
        //~ );
        //~ if (nbytes < 0) {
            //~ perror("sendto");
            //~ return 1;
        //~ }

          //~ sleep(delay_secs); // Unix sleep is seconds
     //~ }

    return 0;
}

soad_ctx_t soad_openSocket(ip_protocol_t protocol, char* ip ,uint32_t port )
{
	soad_ctx_t soad_ctx = {0xFF};
	if (IP_TCP_PROTOCOL == protocol)
	{
        soad_ctx.fd = socket(AF_INET, SOCK_STREAM, 0);
	}
	else
	{
		soad_ctx.fd = socket(AF_INET, SOCK_DGRAM, 0);
	}
    int on=1;
    if (soad_ctx.fd < 0) {
        perror("socket");
        //return 1;
    }
    if (IP_MULTICAST_PROTOCOL == protocol)
    {
		printf("IP_MULTICAST_PROTOCOL\n");
	    setsockopt(soad_ctx.fd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
	}
	//~ setsockopt(soad_ctx.fd ,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    // set up destination address
    //
    memset(&soad_ctx.addr, 0, sizeof(soad_ctx.addr));
    soad_ctx.addr.sin_family = AF_INET;
    soad_ctx.addr.sin_addr.s_addr = inet_addr(ip);
    soad_ctx.addr.sin_port = htons(port);
    int addr_len = sizeof(struct sockaddr_in);
    int ret = bind(soad_ctx.fd, (struct sockaddr*)&soad_ctx.addr, addr_len);
    printf("bind\n");
    if (ret < 0) {
      perror("bind error\n");
    }
    if (IP_TCP_PROTOCOL == protocol)
	{
        listen(soad_ctx.fd, 10);
	}
    return(soad_ctx);
}

soad_ctx_t soad_openRXSocket(ip_protocol_t protocol, char* ip ,uint32_t port )
{
  soad_ctx_t soad_ctx = {0xFF};
  int yes = 1;
  struct sockaddr_in client_addr;
  struct sockaddr_in server_addr;
  int addr_len;
  int count;
  int ret;
  fd_set readfd;
  uint8_t buffer[1024];

  soad_ctx.fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (soad_ctx.fd < 0) {
    perror("sock error\n");

  }

  addr_len = sizeof(struct sockaddr_in);

  memset((void*)&server_addr, 0, addr_len);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htons(INADDR_ANY);
  server_addr.sin_port = htons(port);
  printf("bind\n");
  ret = bind(soad_ctx.fd, (struct sockaddr*)&server_addr, addr_len);
  printf("bind\n");
  if (ret < 0) {
    perror("bind error\n");
  }
    return(soad_ctx);
}

int soad_closeSocket(soad_ctx_t *soad_ctx)
{
	close(soad_ctx->fd);
}

int soad_sendmsg(soad_ctx_t* soad_ctx, uint8_t* msg , size_t size, int port)
{
	soad_ctx->addr.sin_port = htons(port);
    int nbytes = sendto(
        soad_ctx->fd,
        msg,
        size,
        0,
        (struct sockaddr*) &soad_ctx->addr,
        sizeof(soad_ctx->addr)
    );
    if (nbytes < 0) {
        perror("sendto");
        return 1;
    }
}

int soad_recieve(soad_ctx_t* soad_ctx, uint8_t* msg , size_t* size, int* port)
{
	struct sockaddr_in client_addr;
	int count = 0x00;
	int addr_len = sizeof(client_addr);
	printf("recieve a msg \n");
	 
    count = recvfrom(soad_ctx->fd, msg , 1024, 0, (struct sockaddr*)&client_addr, &addr_len);
    printf("count = %d\n", count);
    printf("port = %d\n", ntohs(client_addr.sin_port));
    *port= ntohs(client_addr.sin_port);
    printf("addr = %d\n", client_addr.sin_addr.s_addr);
    for (int i = 0x00; i < count ; i++){
	    printf("0x%x",msg[i]);
	    printf("\n");
    }
    *size=1024;
}
int soad_finilize()
{
	
}
