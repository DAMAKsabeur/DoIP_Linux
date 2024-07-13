#ifndef ALIVE_CHECK_H
#define ALIVE_CHECK_H
#include "doip_types.h"

doip_error_t Alive_status_Check (doip_msg_t* doip_msg, int src_protocole, void* sender);
doip_error_t Alive_status_resp (doip_msg_t* doip_msg, int src_protocole, void* sender);
#endif /* ALIVE_CHECK_H */

