#include "Diagnostic_message.h"

doip_error_t Diagnostic_message_check (doip_msg_t* doip_msg, int src_protocole, void* sender)
{
	printf("Diagnostic_message_check \n");
	printf("proto_version = 0x%x\n", doip_msg->doip_header.proto_version);
	printf("type = 0x%x\n", doip_msg->doip_header.type);
	printf("length = 0x%x\n", doip_msg->doip_header.length);
	printf("Source address = 0x%x,0x%x\n", doip_msg->payload[0] , doip_msg->payload[1]);

    return(0);	
}
doip_error_t Diagnostic_message_resp (doip_msg_t* doip_msg, int src_protocole, void* sender)
{
	printf("Diagnostic_message_resp \n");
    doip_msg->doip_header.proto_version = 0x02;
    doip_msg->doip_header.inverse_proto_version = 0xFD;
    doip_msg->doip_header.type = ntohs(Diagnostic_message_positive_acknowledgement);
    memset(doip_msg->payload, 0x00 , 7); /* VNI */
    doip_msg->payload[0] = 0x0E; /* source address */
    doip_msg->payload[1] = 0x00; /* source address */
    doip_msg->payload[2] = 0xEE; /* target address */
    doip_msg->payload[3] = 0xDD; /* target address */
    
    doip_msg->payload[4] = 0x00; /* ACK*/
    doip_msg->payload[5] = 0xAA;
    doip_msg->payload[6] = 0xBB;
    doip_msg->doip_header.length =  ntohl(7);

    printf("proto_version = 0x%x\n", doip_msg->doip_header.proto_version);
	printf("type = 0x%x\n", doip_msg->doip_header.type);
	printf("length = 0x%x\n", doip_msg->doip_header.length);
	printf("Source address = 0x%x,0x%x\n", doip_msg->payload[0] , doip_msg->payload[1]);
    return(0);	
}
