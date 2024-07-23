#include "Request_File_Transfer.h"

uds_error_code_t Request_File_Transfer_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Request_File_Transfer_cbk\n");
	return (e_NoError);
}
