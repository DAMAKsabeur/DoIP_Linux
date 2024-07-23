#include "Write_Memory_By_Address.h"

uds_error_code_t Write_Memory_By_Address_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Write_Memory_By_Address_cbk\n");
	return (e_NoError);
}

