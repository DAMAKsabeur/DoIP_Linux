#include "Write_Data_By_Identifier.h"

uds_error_code_t Write_Data_By_Identifier_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Write_Data_By_Identifier_cbk\n");
	return (e_NoError);
}
