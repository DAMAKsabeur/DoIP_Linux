#include "Read_DTC_Information.h"

uds_error_code_t Read_DTC_Information_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Read_DTC_Information_cbk\n");
	return (e_NoError);
}
