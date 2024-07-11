#ifndef DOIP_TYPES_H
#define DOIP_TYPES_H
#include <stdint.h>
#define PORT 13400

#define doip_error_t size_t

typedef enum 
{
	Generic_DoIP_header_negative_acknowledge       = 0x0000,
	Vehicle_Identificationrequest_message          = 0x0001,
	Vehicle_identification_requestmessage_with_EID = 0x0002,
	Vehicle_identification_requestmessage_with_VIN = 0x0003,
	Vehicle_announcement_message                   = 0x0004,
	Routing_activation_request                     = 0x0005,
	Routing_activation_response                    = 0x0006,
	Alive_Check_request                            = 0x0007,
	Alive_Check_response                           = 0x0008,
	DoIP_entity_status_request                     = 0x4001,
	DoIP_entity_status_response                    = 0x4002,
	Diagnostic_power_mode_information_request      = 0x4003,
	Diagnostic_power_mode_information_response     = 0x4004,
	Diagnostic_message                             = 0x8001,
	Diagnostic_message_positive_acknowledgement    = 0x8002,
	Diagnostic_message_negative_acknowledgement    = 0x8003,
	doip_message_type_last
}doip_message_type_t;

typedef struct 
{
    uint8_t proto_version;
    uint8_t inverse_proto_version;
	doip_message_type_t type:2;
    uint32_t length;
} doip_header_t;

typedef struct 
{
	doip_header_t doip_header;
    uint8_t payload[256];
} doip_msg_t;

#endif /* DOIP_TYPES_H */
