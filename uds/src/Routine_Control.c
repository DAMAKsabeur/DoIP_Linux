#include "Routine_Control.h"

uds_error_code_t Routine_Control_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Routine_Control_cbk\n");
	return (e_NoError);
}
