#include "Diagnostic_srv.h"
#include "doip_types.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

typedef struct
{
	soad_handler_t soad_handler;
    uint32_t src_addr;
    uint32_t dest_addr;
    size_t msgsize;
	uint8_t msg [256];

} msg_struct_t;


mqd_t mq;
mqd_t mq_1;

#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_SIZE 256
#define QUEUE_NAME "/uds"

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

static void *Diagnostic_srv(void *arg)
{
	printf("Diagnostic_srv\n");

	uds_error_code_t result = e_NoError;
	uint32_t src_addr = 0x00;
    uint32_t dest_addr = 0x00;
    uint8_t msg [256] = {0x00};
    uint32_t msgsize = 0x10;
    msg_struct_t msg_struct = {0x00};
    uint32_t tmp = 0x00;;
    while(true)
    {
        if (mq_receive (mq, &msg_struct,MAX_SIZE , NULL) == -1) {
            perror ("Server: mq_receive");
        }
        /* check if we have to execute a cmd */
            for (int i = 0x00; i < sizeof(cs_UDSServices)/sizeof(uds_services_t); i++)
            {
        		if(msg_struct.msg[0] == cs_UDSServices[i].ServiceID)
        		{
        			result = cs_UDSServices[i].ServicePtr(&msg_struct.msg[0], &msg_struct.msgsize);
        			msg_struct.msg[0]+=0x40;
        			tmp = msg_struct.src_addr;
        			msg_struct.src_addr = msg_struct.dest_addr;
        			msg_struct.dest_addr = tmp;
        			tmp = 0x00;
        			Diagnostic_message_send (msg_struct.soad_handler,	msg_struct.src_addr, msg_struct.dest_addr, msg_struct.msg, msg_struct.msgsize);
        		}
            }
    	usleep(500);
    }
}

uds_error_code_t Diagnostic_srv_init(void)
{
	uds_error_code_t result = e_NoError;
    pthread_t th;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    struct mq_attr attr_mq;

   /* initialize the queue attributes */
    attr_mq.mq_flags = 0;
    attr_mq.mq_maxmsg = 10;
    attr_mq.mq_msgsize = MAX_SIZE;
    attr_mq.mq_curmsgs = 0;

    /* create the message queue */
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr_mq);

    /* open the mail queue */
    mq_1 = mq_open(QUEUE_NAME, O_WRONLY);

	pthread_create(&th, &attr, Diagnostic_srv, NULL);
}


uds_error_code_t Diagnostic_srv_exec (soad_handler_t soad_handler, uint8_t* msg ,size_t msgsize)
{
	printf("Diagnostic_srv_exec\n");
	uds_error_code_t result = e_NoError;
	msg_struct_t msg_struct = {0x00};
    msg_struct.soad_handler =soad_handler;
    msg_struct.src_addr = msg[0] << 8 | msg[1] ;
    msg_struct.dest_addr= msg[2] << 8 | msg[3] ;
    msg_struct.msgsize=(msgsize-4);
    memcpy(msg_struct.msg,&msg[4], msg_struct.msgsize);
    if (mq_send (mq_1, &msg_struct, MAX_SIZE , NULL) == -1) {
        perror ("Server: mq_send");
    }

    return (result);
}
