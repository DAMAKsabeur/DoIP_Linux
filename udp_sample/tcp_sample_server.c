
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close()
#define MAX 80 
#define PORT 13400 
#define SA struct sockaddr 
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
// Function designed for chat between client and server. 
void func(int connfd) 
{ 
    doip_msg_t buff; 
    int n , count; 
    // infinite loop for chat 
    for (;;) { 
        memset(&buff, 0x00 , sizeof(doip_msg_t)); /* VNI */
        // read the message from client and copy it in buffer 
        count = read(connfd, &buff, sizeof(buff)); 
        // print buffer which contains the client contents 
        printf("count = %d\n", count);
        printf("0x%x\n",buff.doip_header.proto_version);
        printf("0x%x\n",buff.doip_header.inverse_proto_version);
        printf("0x%x\n",buff.doip_header.type);
        printf("0x%x\n",buff.doip_header.length);
        for (int i = 0x00; i < (count) ; i++){
			printf("0x%x",buff.payload[i]);
			printf("\n");
		}
        if( n == count)
        {
			break;
		}
	    buff.doip_header.proto_version = 0x02;
        buff.doip_header.inverse_proto_version = 0xFD;
        buff.doip_header.type = ntohs(0x0006);
        //~ memcpy(doip_msg.payload , message , strlen(message));
        memset(buff.payload, 0x00 , sizeof(buff.payload)); /* VNI */
        buff.payload[0] = 0x0E;
        buff.payload[1] = 0x00;
        buff.payload[2] = 0x0E;
        buff.payload[3] = 0x1E;
        buff.payload[4] = 0x10;
        buff.doip_header.length =  ntohl(13);
        //~ // and send that buffer to client 
        count = write(connfd, &buff, sizeof(buff)); 
   
        //~ // if msg contains "Exit" then server exit and chat ended. 
        //~ if (strncmp("exit", buff, 4) == 0) { 
            //~ printf("Server Exit...\n"); 
            //~ break; 
        //~ } 
    }
} 
   
// Driver function 
int main() 
{ 
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
   
    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
   
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
   
    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 
   
    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
    len = sizeof(cli); 
   
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server accept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server accept the client...\n"); 
   
    // Function for chatting between client and server 
    func(connfd); 
   
    // After chatting close the socket 
    close(sockfd); 
}
