#include "Dynamically_Define_Data_Identifier.h"

uds_error_code_t Dynamically_Define_Data_Identifier_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Dynamically_Define_Data_Identifier_cbk\n");
	return (e_NoError);
}
