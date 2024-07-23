#include "Authentication.h"

uds_error_code_t Authentication_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Authentication_cbk\n");
	return (e_NoError);
}
