#ifndef POWER_MODE_INFORMATION_H
#define POWER_MODE_INFORMATION_H
#include "doip_types.h"

doip_error_t Diagnostic_power_mode_resp (soad_handler_t soad_handler, doip_msg_t* doip_msg, ip_protocol_t src_protocole);
doip_error_t Diagnostic_power_mode_information_check (soad_handler_t soad_handler, doip_msg_t* doip_msg, ip_protocol_t src_protocole);
#endif /* POWER_MODE_INFORMATION_H */
