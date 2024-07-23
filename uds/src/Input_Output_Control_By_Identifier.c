#include "Input_Output_Control_By_Identifier.h"

uds_error_code_t Input_Output_Control_By_Identifier_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Input_Output_Control_By_Identifier_cbk\n");
	return (e_NoError);
}
