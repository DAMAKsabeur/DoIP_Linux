#ifndef POWER_MODE_INFORMATION_H
#define POWER_MODE_INFORMATION_H
#include "doip_types.h"

doip_error_t Diagnostic_power_mode_resp (doip_msg_t* doip_msg, int src_protocole, void* sender);
doip_error_t Diagnostic_power_mode_information_check (doip_msg_t* doip_msg, int src_protocole, void* sender);
#endif /* POWER_MODE_INFORMATION_H */
