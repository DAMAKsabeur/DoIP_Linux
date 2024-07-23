#include "Security_Access.h"

uds_error_code_t Security_Access_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Security_Access_cbk\n");
	return (e_NoError);
}
