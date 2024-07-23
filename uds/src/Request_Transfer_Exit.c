#include "Request_Transfer_Exit.h"

uds_error_code_t Request_Transfer_Exit_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Request_Transfer_Exit_cbk\n");
	return (e_NoError);
}
