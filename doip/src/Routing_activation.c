#include "Routing_activation.h"

doip_error_t Routing_activation_request_check (soad_handler_t soad_handler, doip_msg_t* doip_msg, ip_protocol_t src_protocole)
{
	printf("Routing_activation_request_check \n");
    return(0);	
}
doip_error_t Routing_activation_response_msg (soad_handler_t soad_handler, doip_msg_t* doip_msg, ip_protocol_t src_protocole)
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
    return(0);	
}

