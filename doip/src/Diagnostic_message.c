#include "Diagnostic_message.h"
#include "Diagnostic_srv.h"
#include <mqueue.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

doip_error_t Diagnostic_message_check (soad_handler_t soad_handler, doip_msg_t* doip_msg, ip_protocol_t src_protocole)
{
	//printf("Diagnostic_message_check \n");
	return(0);
}

doip_error_t Diagnostic_message_resp (soad_handler_t soad_handler, doip_msg_t* doip_msg, ip_protocol_t src_protocole)
{
    uint8_t temp = 0x00;
    uds_error_code_t rc = 0x00;
    printf("Diagnostic_message_resp \n");
    doip_msg->doip_header.proto_version = 0x02;
    doip_msg->doip_header.inverse_proto_version = 0xFD;
    doip_msg->doip_header.type = ntohs(Diagnostic_message_positive_acknowledgement);

	rc = Diagnostic_srv_exec (soad_handler, doip_msg->payload , ntohl(doip_msg->doip_header.length));
    temp = doip_msg->payload[0];
    doip_msg->payload[0] = doip_msg->payload[2];
     doip_msg->payload[2] = temp;
    temp = doip_msg->payload[1];
    doip_msg->payload[1] = doip_msg->payload[3];
    doip_msg->payload[3] = temp;

    doip_msg->payload[4] = 0x00; /* ACK*/
    doip_msg->payload[5] = 0x10;
    doip_msg->payload[6] = 0x01;

    doip_msg->doip_header.length =  ntohl(7);

    return(0);
}

doip_error_t Diagnostic_message_send (soad_handler_t soad_handler,	uint32_t src_addr, uint32_t dest_addr , uint8_t* msg,size_t msg_size)
{
    uds_error_code_t rc = 0x00;
    doip_msg_t doip_msg ={0x00};
    uint32_t payload_size = msg_size + 4;
    printf("Diagnostic_message_send \n");
    doip_msg.doip_header.proto_version = 0x02;
    doip_msg.doip_header.inverse_proto_version = 0xFD;
    doip_msg.doip_header.type = ntohs(Diagnostic_message);
    doip_msg.doip_header.length = ntohl(payload_size);
    doip_msg.payload[0] = src_addr & 0xFF;
    doip_msg.payload[1] = (src_addr >> 8)& 0xFF;
    doip_msg.payload[2] = dest_addr & 0xFF;
    doip_msg.payload[3] = (dest_addr >> 8)& 0xFF;
    memcpy(&doip_msg.payload[4],msg,msg_size);
    soad_send_msg(soad_handler, &doip_msg , payload_size + sizeof(doip_header_t) , 13400);
    return(0);
}
