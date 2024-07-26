#include "Diagnostic_Session_Control.h"

uds_error_code_t Diagnostic_Session_Control_cbk (uint8_t** msg_ptr , size_t* msg_size)
{
	printf("Diagnostic_Session_Control_cbk\n");
//	size_t size = *msg_size;
//	uint8_t* msg = *msg_ptr;
//	msg[0] = 0x40;
//	msg[1] = 0x01;
//	*msg_size = 0x02;
    return (e_NoError);
}

