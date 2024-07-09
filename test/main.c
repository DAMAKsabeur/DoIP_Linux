#include "soad.h"
int main(int argc, char *argv[])
{
	int listenfd = 0, connfd = 0;
	doip_msg_t doip_msg = {0x00};
	doip_msg_t doip1_msg = {0x00};
	soad_ctx_t soad_0ctx= {0x00};
	soad_ctx_t soad_1ctx= {0x00};
	soad_ctx_t soad_2ctx= {0x00};
	uint32_t port = 13400;
    /*char* ip = "10.219.135.255";*/
    char* ip = "10.0.2.255";
	ip_protocol_t protocol = IP_MULTICAST_PROTOCOL;
	doip_msg.doip_header.proto_version = 0x02;
    doip_msg.doip_header.inverse_proto_version = 0xFD;
    doip_msg.doip_header.type = ntohs(0x0004);
    //~ memcpy(doip_msg.payload , message , strlen(message));
    memset(doip_msg.payload, 0xAA , 17); /* VNI */
    doip_msg.payload[17] = 0x0E;
    doip_msg.payload[18] = 0x1E;
    doip_msg.doip_header.length =  ntohl(33);
    int size = 0x00;
    
	soad_initalize();
	soad_0ctx = soad_openSocket(protocol, ip ,port);
	soad_sendmsg(&soad_0ctx, &doip_msg , sizeof(doip_header_t) + 33, port);
	//~ protocol = IP_TCP_PROTOCOL;
	//~ soad_0ctx = soad_openSocket(protocol, ip ,port);
	//~ soad_closeSocket(&soad_0ctx);
	//~ soad_1ctx = soad_openSocket(protocol, "255.255.255.255" ,port);
	//~ printf("call soad_recieve \n");
	//~ soad_recieve(&soad_1ctx, &doip1_msg , &size, &port);
	//~ protocol = IP_MULTICAST_PROTOCOL;
	//~ soad_sendmsg(&soad_1ctx, &doip_msg , sizeof(doip_header_t) + 33 , port);
	protocol = IP_TCP_PROTOCOL;
	ip = "10.0.2.15";
	soad_1ctx = soad_openSocket(protocol, ip ,port);
	char sendBuff[1025];
    connfd = -1;
    while(connfd <0)
    {
        connfd = accept(soad_1ctx.fd, (struct sockaddr*)NULL, NULL); 
    }
    while (1){
        //~ snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", 1000);
        printf("I will write\n");
        //~ write(connfd, sendBuff, strlen(sendBuff)); 
        char buf[64];
        ssize_t sz = read(soad_1ctx.fd, buf, sizeof(buf));
    for (int i = 0x00; i < sizeof(buf) ; i++){
	    printf("0x%x",buf[i]);
	    printf("\n");
    }
		printf("I will write\n");
        //~ close(connfd);
        sleep(1);
     }
	return(0);
}
