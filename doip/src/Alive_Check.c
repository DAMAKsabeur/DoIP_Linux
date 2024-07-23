#include "Alive_Check.h"


doip_error_t Alive_status_Check (doip_msg_t* doip_msg, int src_protocole, void* sender)
{
	printf("Alive_status_Check \n");
	printf("proto_version = 0x%x\n", doip_msg->doip_header.proto_version);
	printf("type = 0x%x\n", doip_msg->doip_header.type);
	printf("length = 0x%x\n", doip_msg->doip_header.length);
	printf("Source address = 0x%0.2x%0.2x\n", doip_msg->payload[0] , doip_msg->payload[1]);
	printf("target address = 0x%0.2x%0.2x\n", doip_msg->payload[2] , doip_msg->payload[3]);

    return(0);	
}
doip_error_t Alive_status_resp (doip_msg_t* doip_msg, int src_protocole, void* sender)
{
    printf("Alive_status_resp \n");
    doip_msg->doip_header.proto_version = 0x02;
    doip_msg->doip_header.inverse_proto_version = 0xFD;
    doip_msg->doip_header.type = ntohs(Alive_Check_response);
    memset(doip_msg->payload, 0x00 , 7); /* VNI */
    doip_msg->payload[0] = 0x01; /* Node Type */
    doip_msg->payload[1] = 0xFF; /* Max open sockets */
    doip_msg->payload[2] = 0x02; /* Currently open socket */
    doip_msg->payload[3] = 0x00;
    doip_msg->payload[4] = 0x00;
    doip_msg->payload[5] = 0x10;
    doip_msg->payload[6] = 0x00;
    doip_msg->doip_header.length =  ntohl(7);

    printf("proto_version = 0x%x\n", doip_msg->doip_header.proto_version);
	printf("type = 0x%x\n", doip_msg->doip_header.type);
	printf("length = 0x%x\n", doip_msg->doip_header.length);
	printf("Source address = 0x%x,0x%x\n", doip_msg->payload[0] , doip_msg->payload[1]);
    return(0);	
}
