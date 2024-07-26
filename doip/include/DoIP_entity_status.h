#ifndef DOIP_ENTITY_STATUS_H
#define DOIP_ENTITY_STATUS_H
#include "doip_types.h"

doip_error_t DoIP_entity_status_check (soad_handler_t soad_handler, doip_msg_t* doip_msg, ip_protocol_t src_protocole);
doip_error_t DoIP_entity_status_resp (soad_handler_t soad_handler, doip_msg_t* doip_msg, ip_protocol_t src_protocole);
#endif /* DOIP_ENTITY_STATUS_H */
