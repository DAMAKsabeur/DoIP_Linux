#include "doip.h"
#include "soad.h"
doip_state_t doip_states [11] =
   {
	    { Generic_DoIP_header_negative_acknowledge        , NULL                                                 , Generic_DoIP_header_negative_acknowledge     , NULL                              , "Generic_DoIP_header_negative_acknowledge"},
	    { Vehicle_Identificationrequest_message           , Vehicle_Identificationrequest_message_check          , Vehicle_announcement_message                 , Vehicle_announcement_message_resp , "Vehicle_Identificationrequest_message"},
	    { Vehicle_identification_requestmessage_with_EID  , Vehicle_identification_requestmessage_with_EID_check , Vehicle_announcement_message                 , Vehicle_announcement_message_resp , "Vehicle_identification_requestmessage_with_EID"},
	    { Vehicle_identification_requestmessage_with_VIN  , Vehicle_identification_requestmessage_with_VIN_check , Vehicle_announcement_message                 , Vehicle_announcement_message_resp , "Vehicle_identification_requestmessage_with_VIN"},
	    { Vehicle_announcement_message                    , NULL                                                 , Vehicle_announcement_message                 , Vehicle_announcement_message_resp , "Vehicle_announcement_message"},
	    { Routing_activation_request                      , Routing_activation_request_check                     , Routing_activation_response                  , Routing_activation_response_msg   , "Routing_activation_request"},
	    { Alive_Check_request                             , Alive_status_Check                                   , Alive_Check_response                         , Alive_status_resp                 , "Alive_Check_request"},
	    { DoIP_entity_status_request                      , DoIP_entity_status_check                             , DoIP_entity_status_response                  , DoIP_entity_status_resp           , "DoIP_entity_status_request"},
	    { Diagnostic_power_mode_information_request       , Diagnostic_power_mode_information_check              , Diagnostic_power_mode_information_response   , Diagnostic_power_mode_resp        , "Diagnostic_power_mode_information_request"},
	    { Diagnostic_message                              , Diagnostic_message_check                             , Diagnostic_message_positive_acknowledgement  , Diagnostic_message_resp           , "Diagnostic_message"},
	    { Diagnostic_message                              , NULL                                                 , Diagnostic_message_negative_acknowledgement  , NULL                              , "Diagnostic_message"}
	};
	
int doip_process_msg_callback(uint8_t* const buffer, int src_protocole, void* const sender, soad_handler_t soad_handler)
{
    doip_error_t result = 0x00;
    doip_msg_t doip_msg = {0x00};
    memcpy(&doip_msg, buffer, sizeof(doip_msg_t));
    for (int i = 0x00; i < sizeof(doip_states)/sizeof(doip_state_t); i++)
    {
		if(htons(doip_msg.doip_header.type) == doip_states[i].request)
		{
			printf("%s\n", doip_states[i].log);
			result = doip_states[i].request_check_fct(&doip_msg, src_protocole, sender);
			if (0x00 == result)
			{
				result = doip_states[i].response_fct(&doip_msg, src_protocole, sender);	
	            soad_send_msg(soad_handler, &doip_msg , 33 + sizeof(doip_header_t) , 13400);
			}
			break;
		}
	}
    return (result);
}

doip_error_t doip_int(void)
{
	/* 1- initialize a broadcast socket 
	 * 2- send 3 times a broadcast message with vehicule annoncement
	 * 3- close broadcast udp socket
	 * 4- initialize unicast udp socket
	 * 5- initialize udp read thread
	 * 6- initialize tcp socket 
	 * 7- initialize tcp read thread*/
    doip_error_t result = 0x00;
    printf("doip_int \n");
    soad_handler_t soad_handler = 0;
    //~ void* callback = &doip_process_msg_callback;
    soad_handler = soad_open_udp_Socket(&doip_process_msg_callback, 0, "255.255.255.0" ,13400);
    soad_handler = soad_open_tcp_Socket(&doip_process_msg_callback, 0, "10.0.2.15." ,13400);

    return (result);
}

doip_error_t doip_unint(void)
{
	/* kill udp read thread 
	 * close udp socket
	 * kill tcp read thread
	 * close tcp socket*/
    doip_error_t result = 0x00;
    printf("doip_unint \n");
    return (result);	
}

