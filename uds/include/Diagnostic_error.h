/*
 * uds_srv_common.h
 *
 *  Created on: Jul 22, 2024
 *      Author: uic56995
 */

#ifndef DIAGNOSTIC_ERROR_CODE_H_
#define DIAGNOSTIC_ERROR_CODE_H_
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

typedef enum
{
    e_NoError                                          = 0x00u,
    e_ServiceNotSupported                              = 0x11u,
    e_SubFunctionNotSupported                          = 0x12u,
    e_InCorrectMessageLenght                           = 0x13u,
    e_ResponseTooLong                                  = 0x14u,
    e_BusyRepeatRequest                                = 0x21u,
    e_ConditionNotCorrect                              = 0x22u,
    e_RequestSequenceError                             = 0x24u,
    e_RequestOutOfRange                                = 0x31u,
    e_SecurityAccessDenied                             = 0x33u,
    e_InvalidKey                                       = 0x35u,
    e_InvalidKey_3rd_attempt                           = 0x36u,
    e_RequiredTimeDelayNotExpired                      = 0x37u,
    e_UploadDownloadNotAccepted                        = 0x70u,
    e_TransferDataSuspended                            = 0x71u,
    e_GeneralProgrammingFailure                        = 0x72u,
    e_WrongBlockSequenceCounter                        = 0x73u,
    e_SubFunctionNotSupportedInActiveDiagnosticSession = 0x7Eu,
    e_ServiceNotSupportedInActiveDiagnosticSession     = 0x7Fu,
    e_VoltageTooHigh                                   = 0x92u,
    e_VoltageTooLow                                    = 0x93u
} uds_error_code_t;

#endif /* DIAGNOSTIC_ERROR_CODE_H_ */
