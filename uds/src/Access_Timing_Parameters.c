#include "Access_Timing_Parameters.h"

uds_error_code_t Access_Timing_Parameters_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Access_Timing_Parameters_cbk\n");
	return (e_NoError);
}
