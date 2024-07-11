#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <linux/in.h>
#include <sys/socket.h>
#include <sys/select.h>

#define IP_FOUND "IP_FOUND"
#define IP_FOUND_ACK "IP_FOUND_ACK"
#define PORT 13400

int main() {
  int sock;
  int yes = 1;
  struct sockaddr_in broadcast_addr;
  struct sockaddr_in server_addr;
  int addr_len;
  int count;
  int ret;
  fd_set readfd;
  uint8_t buffer[1024];
  int i;
  
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    perror("sock error");
    return -1;
  }
  ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&yes, sizeof(yes));
  if (ret == -1) {
    perror("setsockopt error");
    return 0;
  }

  addr_len = sizeof(struct sockaddr_in);

  memset((void*)&broadcast_addr, 0, addr_len);
  broadcast_addr.sin_family = AF_INET;
  broadcast_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
  broadcast_addr.sin_port = htons(PORT);
  printf("loop  \n");
  for (i=0;i<3;i++) {
	buffer[0] = 0x2;
    buffer[1] = 0xfd;
    buffer[2] = 0x0;
    buffer[3] = 0x1;
    buffer[4] = 0x0;
    buffer[5] = 0x0;
    buffer[6] = 0x0;
    buffer[7] = 0x0;
    buffer[8] = 0x0;
    buffer[9] = 0x0;
    
    ret = sendto(sock, buffer, 10, 0, (struct sockaddr*) &broadcast_addr, addr_len);

    FD_ZERO(&readfd);
    FD_SET(sock, &readfd);
	printf("select \n");
    ret = select(sock + 1, &readfd, NULL, NULL, NULL);
    printf("FD_ISSET \n");
    if (ret > 0) {
      if (FD_ISSET(sock, &readfd)) {
        count = recvfrom(sock, buffer, 30, 0, (struct sockaddr*)&server_addr, &addr_len);
        for ( int i = 0x00 ; i< 30 ; i++)
        {
			printf("0x%x\n",buffer[i]);
		}
      }
    }

  }
}

