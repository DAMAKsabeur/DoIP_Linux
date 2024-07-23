#include "Request_Upload.h"

uds_error_code_t Request_Upload_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Request_Upload_cbk\n");
	return (e_NoError);
}
