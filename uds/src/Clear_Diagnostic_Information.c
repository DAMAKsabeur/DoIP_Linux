#include "Clear_Diagnostic_Information.h"

uds_error_code_t Clear_Diagnostic_Information_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Clear_Diagnostic_Information_cbk\n");
	return (e_NoError);
}
