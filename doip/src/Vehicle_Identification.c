#include "Vehicle_Identification.h"

doip_error_t Vehicle_Identificationrequest_message_check (doip_msg_t* doip_msg, int src_protocole, void* sender)
{
	printf("Vehicle_Identificationrequest_message_check \n");
    return(0);	
}
doip_error_t Vehicle_identification_requestmessage_with_EID_check (doip_msg_t* doip_msg, int src_protocole, void* sender)
{
	printf("Vehicle_identification_requestmessage_with_EID \n");
    return(0);	
}
doip_error_t Vehicle_identification_requestmessage_with_VIN_check (doip_msg_t* doip_msg, int src_protocole, void* sender)
{
	printf("Vehicle_identification_requestmessage_with_VIN \n");
    return(0);	
}
doip_error_t Vehicle_announcement_message_resp (doip_msg_t* doip_msg, int src_protocole, void* sender)
{
	printf("Vehicle_announcement_message_resp \n");
    doip_msg->doip_header.proto_version = 0x02;
    doip_msg->doip_header.inverse_proto_version = 0xFD;
    doip_msg->doip_header.type = ntohs(0x0004);
    //~ memcpy(doip_msg.payload , message , strlen(message));
    memset(doip_msg->payload, 0xAB , 17); /* VNI */
    doip_msg->payload[17] = 0xEE;
    doip_msg->payload[18] = 0xDD;
    doip_msg->doip_header.length =  ntohl(33);
    return(0);	
}
