#include "Read_Data_By_Identifier_Periodic.h"

uds_error_code_t Read_Data_By_Identifier_Periodic_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Read_Data_By_Identifier_Periodic_cbk\n");
	return (e_NoError);
}
