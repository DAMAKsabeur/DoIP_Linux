#include "ECU_Reset.h"

uds_error_code_t ECU_Reset_cbk (uint8_t* msg , size_t msg_size)
{
	printf("ECU_Reset_cbk \n");
	return (e_NoError);
}
