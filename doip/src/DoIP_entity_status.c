#include "DoIP_entity_status.h"

doip_error_t DoIP_entity_status_check (soad_handler_t soad_handler, doip_msg_t* doip_msg, ip_protocol_t src_protocole)
{
	printf("DoIP_entity_status_check \n");
    return(0);	
}
doip_error_t DoIP_entity_status_resp (soad_handler_t soad_handler, doip_msg_t* doip_msg, ip_protocol_t src_protocole)
{
	printf("DoIP_entity_status_check_resp \n");
    doip_msg->doip_header.proto_version = 0x02;
    doip_msg->doip_header.inverse_proto_version = 0xFD;
    doip_msg->doip_header.type = ntohs(DoIP_entity_status_response);
    memset(doip_msg->payload, 0x00 , 7); /* VNI */
    doip_msg->payload[0] = 0x01; /* Node Type */
    doip_msg->payload[1] = 0xFF; /* Max open sockets */
    doip_msg->payload[2] = 0x02; /* Currently open socket */
    doip_msg->payload[3] = 0x00;
    doip_msg->payload[4] = 0x00;
    doip_msg->payload[5] = 0x10;
    doip_msg->payload[6] = 0x00;
    doip_msg->doip_header.length =  ntohl(7);
    return(0);	
}
