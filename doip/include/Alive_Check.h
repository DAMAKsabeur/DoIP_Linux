#ifndef ALIVE_CHECK_H
#define ALIVE_CHECK_H
#include "doip_types.h"

doip_error_t Alive_status_Check (soad_handler_t soad_handler, doip_msg_t* doip_msg, ip_protocol_t src_protocole);
doip_error_t Alive_status_resp (soad_handler_t soad_handler, doip_msg_t* doip_msg, ip_protocol_t src_protocole);
#endif /* ALIVE_CHECK_H */

