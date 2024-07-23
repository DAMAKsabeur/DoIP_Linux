#include "Read_Memory_By_Address.h"

uds_error_code_t Read_Memory_By_Address_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Read_Memory_By_Address_cbk\n");
	return (e_NoError);
}
