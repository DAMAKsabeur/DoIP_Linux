/*
 * Diagnostic_srv.h
 *
 *  Created on: Jul 22, 2024
 *      Author: uic56995
 */

#ifndef DIAGNOSTIC_SRV_H_
#define DIAGNOSTIC_SRV_H_
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "Diagnostic_error.h"
#include "soad.h"
#include "Access_Timing_Parameters.h"
#include "Diagnostic_Session_Control.h"
#include "Link_Control.h"
#include "Read_Memory_By_Address.h"
#include "Request_Upload.h"
#include "Tester_Present.h"
#include "Authentication.h"
#include "Diagnostic_srv.h"
#include "Negative_Response.h"
#include "Read_Scaling_Data_By_Identifier.h"
#include "Response_On_Event.h"
#include "Transfer_Data.h"
#include "Clear_Diagnostic_Information.h"
#include "Dynamically_Define_Data_Identifier.h"
#include "Read_Data_By_Identifier.h"
#include "Request_Download.h"
#include "Routine_Control.h"
#include "Write_Data_By_Identifier.h"
#include "Communication_Control.h"
#include "ECU_Reset.h"
#include "Read_Data_By_Identifier_Periodic.h"
#include "Request_File_Transfer.h"
#include "Secured_Data_Transmission.h"
#include "Write_Memory_By_Address.h"
#include "Control_DTC_Settings.h"
#include "Input_Output_Control_By_Identifier.h"
#include "Read_DTC_Information.h"
#include "Request_Transfer_Exit.h"
#include "Security_Access.h"

#define NBOFDIAGNOSISSESSION                0x03
#define NB_NRC_BEHAVIOR_ORDER               0x08

typedef enum
{
    Diagnostic_Session_Control         = 0x10,
    ECU_Reset                          = 0x11,
    Security_Access                    = 0x27,
    Communication_Control              = 0x28,
    Authentication                     = 0x29,
    Tester_Present                     = 0x3E,
    Access_Timing_Parameters           = 0x83,
    Secured_Data_Transmission          = 0x84,
    Control_DTC_Settings               = 0x85,
    Response_On_Event                  = 0x86,
    Link_Control                       = 0x87,
    Read_Data_By_Identifier            = 0x22,
    Read_Memory_By_Address             = 0x23,
    Read_Scaling_Data_By_Identifier    = 0x24,
    Read_Data_By_Identifier_Periodic   = 0x2A,
    Dynamically_Define_Data_Identifier = 0x2C,
    Write_Data_By_Identifier           = 0x2E,
    Write_Memory_By_Address            = 0x3D,
    Clear_Diagnostic_Information       = 0x14,
    Read_DTC_Information               = 0x19,
    Input_Output_Control_By_Identifier = 0x2F,
    Routine_Control                    = 0x31,
    Request_Download                   = 0x34,
    Request_Upload                     = 0x35,
    Transfer_Data                      = 0x36,
    Request_Transfer_Exit              = 0x37,
    Request_File_Transfer              = 0x38,
    UDS_SERVICE_LAST
} Services_id_t;

typedef enum
{
    SUPP_POS_RRESPONS_NOT_ALLOWED = 0x00U,
    SUPP_POS_RRESPONS_ALLOWED     = 0x01U,
    SUPP_POS_RRESPONS_IGNORED     = 0x02U,
    SUPP_POS_RRESPONS_LAST        = 0x03U
} SuppPosResponsAllowed_t;


typedef enum
{
    SEED_NOT_REQUIRED             = 0x00U,
    SEED_REQUIRED                 = 0x01U,
    SEED_LAST
} SeedRequired_t;

typedef enum
{
    FINGERPRINT_NOT_REQUIRED      = 0x00U,
    FINGERPRINT_REQUIRED          = 0x01U,
    FINGERPRINT_LAST
} FingerPrintRequired_t;

typedef uds_error_code_t (* Service_cbk_t) (uint8_t* msg , size_t msg_size);

typedef struct
{
	Services_id_t           ServiceID;
    Service_cbk_t           ServicePtr;
    SuppPosResponsAllowed_t SuppPosResponsAllowed;
    bool                    DiagSessionAllowed[NBOFDIAGNOSISSESSION];
    SeedRequired_t          SeedKeyNeeded;
    FingerPrintRequired_t   fingerprintNeeded;
} uds_services_t;

uds_error_code_t Diagnostic_srv_exec (soad_handler_t soad_handler, uint8_t* msg ,size_t msgsize);
uds_error_code_t Diagnostic_srv_init(void);

#endif /* DIAGNOSTIC_SRV_H_ */
