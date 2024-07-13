#ifndef DOIP_ENTITY_STATUS_H
#define DOIP_ENTITY_STATUS_H
#include "doip_types.h"
doip_error_t DoIP_entity_status_check (doip_msg_t* doip_msg, int src_protocole, void* sender);
doip_error_t DoIP_entity_status_resp (doip_msg_t* doip_msg, int src_protocole, void* sender);
#endif /* DOIP_ENTITY_STATUS_H */
