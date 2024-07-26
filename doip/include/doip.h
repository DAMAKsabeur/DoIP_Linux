#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdint.h>

#include "doip_types.h"
#include "Alive_Check.h"
#include "Diagnostic_message.h"
#include "DoIP_entity_status.h"
#include "Generic_DoIP_header.h"
#include "Power_mode_information.h"
#include "Routing_activation.h"
#include "Vehicle_Identification.h"

doip_error_t doip_init(void);
doip_error_t doip_uninit(void);
int doip_process_msg_callback(soad_handler_t soad_handler, uint8_t* buffer, ip_protocol_t src_protocole);
