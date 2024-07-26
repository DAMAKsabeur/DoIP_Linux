#ifndef ROUTING_ACTIVATION_H
#define ROUTING_ACTIVATION_H
#include "doip_types.h"
doip_error_t Routing_activation_request_check (soad_handler_t soad_handler, doip_msg_t* doip_msg, ip_protocol_t src_protocole);
doip_error_t Routing_activation_response_msg (soad_handler_t soad_handler, doip_msg_t* doip_msg, ip_protocol_t src_protocole);

#endif /* ROUTING_ACTIVATION_H*/
