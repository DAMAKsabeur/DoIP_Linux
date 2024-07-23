#include "Tester_Present.h"

uds_error_code_t Tester_Present_cbk (uint8_t* msg , size_t msg_size)
{
	printf("Tester_Present_cbk\n");
	return (e_NoError);
}
