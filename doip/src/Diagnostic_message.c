#include "Diagnostic_message.h"
#include "Diagnostic_srv.h"
doip_error_t Diagnostic_message_check (doip_msg_t* doip_msg, int src_protocole, void* sender)
{
	printf("Diagnostic_message_check \n");
	printf("proto_version = 0x%x\n", doip_msg->doip_header.proto_version);
	printf("type = 0x%x\n", doip_msg->doip_header.type);
	printf("length = 0x%x\n", doip_msg->doip_header.length);
	printf("Source address = 0x%0.2x%0.2x\n", doip_msg->payload[0] , doip_msg->payload[1]);
	printf("target address = 0x%0.2x%0.2x\n", doip_msg->payload[2] , doip_msg->payload[3]);
	return(0);
}

doip_error_t Diagnostic_message_resp (doip_msg_t* doip_msg, int src_protocole, void* sender)
{
	printf("Diagnostic_message_resp \n");
	printf("proto_version = 0x%x\n", doip_msg->doip_header.proto_version);
	printf("type = 0x%x\n", doip_msg->doip_header.type);
	printf("length = 0x%x\n", doip_msg->doip_header.length);
    uint8_t temp = 0x00;
    uds_error_code_t rc = 0x00;
    doip_msg->doip_header.proto_version = 0x02;
    doip_msg->doip_header.inverse_proto_version = 0xFD;
    doip_msg->doip_header.type = ntohs(Diagnostic_message_positive_acknowledgement);
	printf("Source address = 0x%0.2x%0.2x\n", doip_msg->payload[0] , doip_msg->payload[1]);
	printf("target address = 0x%0.2x%0.2x\n", doip_msg->payload[2] , doip_msg->payload[3]);
	rc = Diagnostic_srv_exec (&doip_msg->payload[4] , doip_msg->doip_header.length-4);

    temp = doip_msg->payload[0];
    doip_msg->payload[0] = doip_msg->payload[2];
     doip_msg->payload[2] = temp;
    temp = doip_msg->payload[1];
    doip_msg->payload[1] = doip_msg->payload[3];
    doip_msg->payload[3] = temp;

	printf("Source address = 0x%0.2x%0.2x\n", doip_msg->payload[0] , doip_msg->payload[1]);
	printf("target address = 0x%0.2x%0.2x\n", doip_msg->payload[2] , doip_msg->payload[3]);
    doip_msg->payload[4] = 0x00; /* ACK*/
    doip_msg->payload[5] = 0x40;
    doip_msg->payload[6] = 0x01;

    doip_msg->doip_header.length =  ntohl(7);

    printf("proto_version = 0x%x\n", doip_msg->doip_header.proto_version);
	printf("type = 0x%x\n", doip_msg->doip_header.type);
	printf("length = 0x%x\n", doip_msg->doip_header.length);
	printf("Source address = 0x%0.2x%0.2x\n", doip_msg->payload[0] , doip_msg->payload[1]);
	printf("target address = 0x%0.2x%0.2x\n", doip_msg->payload[2] , doip_msg->payload[3]);
    return(0);	
}
