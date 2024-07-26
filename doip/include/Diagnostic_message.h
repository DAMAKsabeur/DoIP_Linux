#ifndef DIAGNOSTOC_MESSAGE_H
#define DIAGNOSTOC_MESSAGE_H
#include "doip_types.h"
doip_error_t Diagnostic_message_check (soad_handler_t soad_handler, doip_msg_t* doip_msg, ip_protocol_t src_protocole);
doip_error_t Diagnostic_message_resp (soad_handler_t soad_handler, doip_msg_t* doip_msg, ip_protocol_t src_protocole);
doip_error_t Diagnostic_message_send (soad_handler_t soad_handler,	uint32_t src_addr, uint32_t dest_addr , uint8_t* msg,size_t msg_size);
#endif /* DIAGNOSTOC_MESSAGE_H */
