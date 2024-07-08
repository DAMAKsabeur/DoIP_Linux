//
// Simple sender.c program for UDP
//
// Adapted from:
// http://ntrg.cs.tcd.ie/undergrad/4ba2/multicast/antony/example.html
//
// Changes:
// * Compiles for Windows as well as Linux
// * Takes the port and group on the command line
//
// Note that what this program does should be equivalent to NETCAT:
//
//     echo "Hello World" | nc -u 239.255.255.250 1900

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // for sleep()

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 #include <arpa/inet.h>

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

int main(int argc, char *argv[])
{
    if (argc != 3) {
       printf("Command line args should be multicast group and port\n");
       printf("(e.g. for SSDP, `sender 239.255.255.250 1900`)\n");
       return 1;
    }

    char* group = argv[1]; // e.g. 239.255.255.250 for SSDP
    int port = atoi(argv[2]); // 0 if error, which is an invalid port
    doip_msg_t doip_msg = {0x00};
    // !!! If test requires, make these configurable via args
    //
    const int delay_secs = 1;
    const char *message = "Hello, World!";
    doip_msg.doip_header.proto_version = 0x02;
    doip_msg.doip_header.inverse_proto_version = 0xFD;
    doip_msg.doip_header.type = ntohs(0x0004);
    memcpy(doip_msg.payload , message , strlen(message));
    memset(doip_msg.payload, 0xAA , 17); /* VNI */
    doip_msg.payload[17] = 0x0E;
    doip_msg.payload[18] = 0x1E;
    doip_msg.doip_header.length =  ntohl(33);
    // create what looks like an ordinary UDP socket
    //
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket");
        return 1;
    }
	int on=1;
	setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
    // set up destination address
    //
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(group);
    addr.sin_port = htons(port);

      // now just sendto() our destination!
    //
    for (int i=0 ; i<100000 ; i++) {
        char ch = 0;
        int nbytes = sendto(
            fd,
            &doip_msg,
            33 + sizeof(doip_header_t),
            0,
            (struct sockaddr*) &addr,
            sizeof(addr)
        );
        if (nbytes < 0) {
            perror("sendto");
            return 1;
        }

          sleep(delay_secs); // Unix sleep is seconds
     }

    return 0;
}
