#include "Communication_Control.h"

uds_error_code_t Communication_Control_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Communication_Control_cbk\n");
	return (e_NoError);
}
