#include "Diagnostic_srv.h"

const uds_services_t cs_UDSServices[UDS_SERVICE_LAST] =
{
	    {Diagnostic_Session_Control         , Diagnostic_Session_Control_cbk          , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {ECU_Reset                          , ECU_Reset_cbk                           , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Security_Access                    , Security_Access_cbk                     , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Communication_Control              , Communication_Control_cbk               , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Authentication                     , Authentication_cbk                      , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Tester_Present                     , Tester_Present_cbk                      , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Access_Timing_Parameters           , Access_Timing_Parameters_cbk            , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Secured_Data_Transmission          , Secured_Data_Transmission_cbk           , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Control_DTC_Settings               , Control_DTC_Settings_cbk                , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Response_On_Event                  , Response_On_Event_cbk                   , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Link_Control                       , Link_Control_cbk                        , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Read_Data_By_Identifier            , Read_Data_By_Identifier_cbk             , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Read_Memory_By_Address             , Read_Memory_By_Address_cbk              , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Read_Scaling_Data_By_Identifier    , Read_Scaling_Data_By_Identifier_cbk     , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Read_Data_By_Identifier_Periodic   , Read_Data_By_Identifier_Periodic_cbk    , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Dynamically_Define_Data_Identifier , Dynamically_Define_Data_Identifier_cbk  , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Write_Data_By_Identifier           , Write_Data_By_Identifier_cbk            , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Write_Memory_By_Address            , Write_Memory_By_Address_cbk             , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Clear_Diagnostic_Information       , Clear_Diagnostic_Information_cbk        , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Read_DTC_Information               , Read_DTC_Information_cbk                , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Input_Output_Control_By_Identifier , Input_Output_Control_By_Identifier_cbk  , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Routine_Control                    , Routine_Control_cbk                     , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Request_Download                   , Request_Download_cbk                    , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Request_Upload                     , Request_Upload_cbk                      , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Transfer_Data                      , Transfer_Data_cbk                       , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Request_Transfer_Exit              , Request_Transfer_Exit_cbk               , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
	    {Request_File_Transfer              , Request_File_Transfer_cbk               , SUPP_POS_RRESPONS_ALLOWED , {true , true , true }, SEED_NOT_REQUIRED , FINGERPRINT_NOT_REQUIRED },
};

uds_error_code_t Diagnostic_srv_exec (uint8_t* msg , size_t msg_size)
{
	printf("Diagnostic_srv_exec\n");
	uds_error_code_t result = e_NoError;
	printf(">>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<\n");
	printf("%x\n", msg[0]);
    for (int i = 0x00; i < sizeof(cs_UDSServices)/sizeof(uds_services_t); i++)
    {
		if(msg[0] == cs_UDSServices[i].ServiceID)
		{
			printf("%x\n", cs_UDSServices[i].ServiceID);
			result = cs_UDSServices[i].ServicePtr(msg, msg_size);
//			if (0x00 == result)
//			{
//				result = doip_states[i].response_fct(&doip_msg, src_protocole, sender);
//	            soad_send_msg(soad_handler, &doip_msg , 33 + sizeof(doip_header_t) , 13400);
//			}
			break;
		}
	}
    return (result);
}
