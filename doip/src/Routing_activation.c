#include "Routing_activation.h"

doip_error_t Routing_activation_request_check (doip_msg_t* doip_msg, int src_protocole, void* sender)
{
	printf("Routing_activation_request_check \n");
	printf("proto_version = 0x%x\n", doip_msg->doip_header.proto_version);
	printf("type = 0x%x\n", doip_msg->doip_header.type);
	printf("length = 0x%x\n", doip_msg->doip_header.length);
	printf("Source address = 0x%0.2x%0.2x\n", doip_msg->payload[0] , doip_msg->payload[1]);
	printf("target address = 0x%0.2x%0.2x\n", doip_msg->payload[2] , doip_msg->payload[3]);
	
    return(0);	
}
doip_error_t Routing_activation_response_msg (doip_msg_t* doip_msg, int src_protocole, void* sender)
{
	printf("Routing_activation_response_msg \n");
    doip_msg->doip_header.proto_version = 0x02;
    doip_msg->doip_header.inverse_proto_version = 0xFD;
    doip_msg->doip_header.type = ntohs(Routing_activation_response);
    memset(doip_msg->payload, 0x00 , 13); /* VNI */
    doip_msg->payload[0] = 0xEE;
    doip_msg->payload[1] = 0xDD;
    doip_msg->payload[2] = 0x01;
    doip_msg->payload[3] = 0x1E;
    doip_msg->payload[4] = 0x10;
    doip_msg->doip_header.length =  ntohl(13);

    printf("proto_version = 0x%x\n", doip_msg->doip_header.proto_version);
	printf("type = 0x%x\n", doip_msg->doip_header.type);
	printf("length = 0x%x\n", doip_msg->doip_header.length);
	printf("Source address = 0x%x,0x%x\n", doip_msg->payload[0] , doip_msg->payload[1]);
    return(0);	
}

