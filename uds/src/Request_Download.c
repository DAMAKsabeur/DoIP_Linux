#include "Request_Download.h"

uds_error_code_t Request_Download_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Request_Download_cbk\n");
	return (e_NoError);
}
