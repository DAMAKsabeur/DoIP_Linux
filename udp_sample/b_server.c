#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <linux/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include "doip_types.h"

#define PORT 13400

//~ typedef struct 
//~ {
    //~ uint8_t proto_version;
    //~ uint8_t inverse_proto_version;
	//~ uint16_t type;
    //~ uint32_t length;
//~ } doip_header_t;

//~ typedef struct 
//~ {
	//~ doip_header_t doip_header;
    //~ uint8_t payload[256];
//~ } doip_msg_t;

int main() {
  int sock;
  int yes = 1;
  struct sockaddr_in client_addr;
  struct sockaddr_in server_addr;
  int addr_len;
  int count;
  int ret;
  fd_set readfd;
  doip_msg_t buffer = {0x00};

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    perror("sock error\n");
    return -1;
  }
  printf(sizeof(doip_msg_t));
  addr_len = sizeof(struct sockaddr_in);

  memset((void*)&server_addr, 0, addr_len);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htons(INADDR_ANY);
  server_addr.sin_port = htons(PORT);
  printf("bind\n");
  ret = bind(sock, (struct sockaddr*)&server_addr, addr_len);
  printf("bind\n");
  if (ret < 0) {
    perror("bind error\n");
    return -1;
  }
  while (1) {
    //~ FD_ZERO(&readfd);
    //~ FD_SET(sock, &readfd);
    //~ ret = select(sock+1, &readfd, NULL, NULL, 0);
    //~ ret = 1;
    //~ if (ret > 0) {
      //~ if (FD_ISSET(sock, &readfd)) {
        count = recvfrom(sock, &buffer, sizeof(doip_msg_t), 0, (struct sockaddr*)&client_addr, &addr_len);
        printf("count = %d\n", count);
        printf("0x%x\n",buffer.doip_header.proto_version);
        printf("0x%x\n",buffer.doip_header.inverse_proto_version);
        printf("0x%x\n",buffer.doip_header.type);
        printf("0x%x\n",buffer.doip_header.length);
        for (int i = 0x00; i < count ; i++){
			printf("0x%x",buffer.payload[i]);
			printf("\n");
		}
		char str[100];
        inet_ntop(AF_INET, &(client_addr.sin_addr), str, 100);
        printf("%s\n", str);
	    buffer.doip_header.proto_version = 0x02;
        buffer.doip_header.inverse_proto_version = 0xFD;
        buffer.doip_header.type = ntohs(0x0004);
        //~ memcpy(doip_msg.payload , message , strlen(message));
        memset(buffer.payload, 0xAA , 17); /* VNI */
        buffer.payload[17] = 0x0E;
        buffer.payload[18] = 0x1E;
        buffer.doip_header.length =  ntohl(33);
                printf("count = %d\n", count);
        printf("0x%x\n",buffer.doip_header.proto_version);
        printf("0x%x\n",buffer.doip_header.inverse_proto_version);
        printf("0x%x\n",buffer.doip_header.type);
        printf("0x%x\n",buffer.doip_header.length);
        for (int i = 0x00; i < sizeof(buffer.payload) ; i++){
			printf("0x%x",buffer.payload[i]);
			printf("\n");
		}
        printf("\nClient connection information:\n\t IP: %s, Port: %d\n" ,str, ntohs(client_addr.sin_port));
        count = sendto(sock, &buffer, 33 +sizeof(doip_header_t), 0, (struct sockaddr*)&client_addr, addr_len);
        
      }
}
