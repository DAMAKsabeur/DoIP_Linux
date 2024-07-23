#include "Diagnostic_Session_Control.h"

uds_error_code_t Diagnostic_Session_Control_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Diagnostic_Session_Control_cbk\n");
    return (e_NoError);
}

