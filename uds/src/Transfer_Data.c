#include "Transfer_Data.h"

uds_error_code_t Transfer_Data_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Transfer_Data_cbk\n");
	return (e_NoError);
}
