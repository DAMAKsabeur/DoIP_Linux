#ifndef DIAGNOSTOC_MESSAGE_H
#define DIAGNOSTOC_MESSAGE_H
#include "doip_types.h"

doip_error_t Diagnostic_message_check (doip_msg_t* doip_msg, int src_protocole, void* sender);
doip_error_t Diagnostic_message_resp (doip_msg_t* doip_msg, int src_protocole, void* sender);
#endif /* DIAGNOSTOC_MESSAGE_H */
