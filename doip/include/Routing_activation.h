#ifndef ROUTING_ACTIVATION_H
#define ROUTING_ACTIVATION_H
#include "doip_types.h"
doip_error_t Routing_activation_request_check (doip_msg_t* doip_msg, int src_protocole, void* sender);
doip_error_t Routing_activation_response_msg (doip_msg_t* doip_msg, int src_protocole, void* sender);

#endif /* ROUTING_ACTIVATION_H*/
