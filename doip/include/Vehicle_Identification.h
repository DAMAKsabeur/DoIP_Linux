#ifndef VEHICLE_IDENTIFICATION_H
#define VEHICLE_IDENTIFICATION_H
#include "doip_types.h"
doip_error_t Vehicle_Identificationrequest_message_check (doip_msg_t* doip_msg, int src_protocole, void* sender);
doip_error_t Vehicle_identification_requestmessage_with_EID_check (doip_msg_t* doip_msg, int src_protocole, void* sender);
doip_error_t Vehicle_identification_requestmessage_with_VIN_check (doip_msg_t* doip_msg, int src_protocole, void* sender);
doip_error_t Vehicle_announcement_message_resp (doip_msg_t* doip_msg, int src_protocole, void* sender);

#endif /* VEHICLE_IDENTIFICATION_H */
