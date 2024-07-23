#include "Secured_Data_Transmission.h"

uds_error_code_t Secured_Data_Transmission_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Secured_Data_Transmission_cbk\n");
	return (e_NoError);
}
