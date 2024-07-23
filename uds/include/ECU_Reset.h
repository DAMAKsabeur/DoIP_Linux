#ifndef ECU_Reset_H_
#define ECU_Reset_H_

#include "Diagnostic_error.h"

uds_error_code_t ECU_Reset_cbk (uint8_t* msg , size_t msg_size);

#endif /* ECU_Reset_H_ */
