#include "Response_On_Event.h"

uds_error_code_t Response_On_Event_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Response_On_Event_cbk\n");
	return (e_NoError);
}
