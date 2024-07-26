#ifndef VEHICLE_IDENTIFICATION_H
#define VEHICLE_IDENTIFICATION_H
#include "doip_types.h"
doip_error_t Vehicle_Identificationrequest_message_check (soad_handler_t soad_handler, doip_msg_t* doip_msg, ip_protocol_t src_protocole);
doip_error_t Vehicle_identification_requestmessage_with_EID_check (soad_handler_t soad_handler, doip_msg_t* doip_msg, ip_protocol_t src_protocole);
doip_error_t Vehicle_identification_requestmessage_with_VIN_check (soad_handler_t soad_handler, doip_msg_t* doip_msg, ip_protocol_t src_protocole);
doip_error_t Vehicle_announcement_message_resp (soad_handler_t soad_handler, doip_msg_t* doip_msg, ip_protocol_t src_protocole);

#endif /* VEHICLE_IDENTIFICATION_H */
