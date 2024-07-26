//~ /*
 //~ * client.c: Client program
 //~ *           to demonstrate interprocess communication
 //~ *           with POSIX message queues
 //~ */

//~ #include <stdio.h>
//~ #include <stdlib.h>
//~ #include <stdint.h>
//~ #include <string.h>
//~ #include <sys/types.h>
//~ #include <unistd.h>
//~ #include <fcntl.h>
//~ #include <sys/stat.h>
//~ #include <mqueue.h>

//~ #define SERVER_QUEUE_NAME   "/sp-example-server"
//~ #define QUEUE_PERMISSIONS 0660
//~ #define MAX_MESSAGES 10
//~ #define MAX_MSG_SIZE 256
//~ #define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

//~ int main (int argc, char **argv)
//~ {
    //~ char client_queue_name [64];
    //~ mqd_t qd_server, qd_client;   // queue descriptors


    //~ // create the client queue for receiving messages from server
    //~ sprintf (client_queue_name, "/sp-example-client-%d", getpid ());

    //~ struct mq_attr attr;

    //~ attr.mq_flags = 0;
    //~ attr.mq_maxmsg = MAX_MESSAGES;
    //~ attr.mq_msgsize = MAX_MSG_SIZE;
    //~ attr.mq_curmsgs = 0;

    //~ if ((qd_client = mq_open (client_queue_name, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
        //~ perror ("Client: mq_open (client)");
        //~ exit (1);
    //~ }

    //~ if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_WRONLY)) == -1) {
        //~ perror ("Client: mq_open (server)");
        //~ exit (1);
    //~ }

    //~ char in_buffer [MSG_BUFFER_SIZE];

    //~ printf ("Ask for a token (Press <ENTER>): ");

    //~ char temp_buf [10];

    //~ while (fgets (temp_buf, 4, stdin)) {
         //~ uint8_t buff [10] = {0x00};
         //~ uint8_t aa = 0x00;
         //~ uint8_t bb = 0x00;
         //~ printf("temp_buf[0] =%x\n",temp_buf[0]);
         //~ printf("temp_buf[1] =%x\n",temp_buf[1]);
         //~ buff[0] = (((temp_buf[0] -0x30)<<0x04) | (temp_buf[1] -0x30));
         //~ buff[0] = ((temp_buf[1] - 0x30) << 8) | ((temp_buf[0] - 0x30));
         //~ printf("buff=%x\n",buff[0]);
         //~ buff[1] = 0x01;
        //~ // send message to server
        //~ if (mq_send (qd_server, buff, 10, 0) == -1) {
            //~ perror ("Client: Not able to send message to server");
            //~ continue;
        //~ }

        // receive response from server

        //~ if (mq_receive (qd_client, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {
            //~ perror ("Client: mq_receive");
            //~ exit (1);
        //~ }
        // display token received from server
        //~ printf ("Client: Token received from server: %s\n\n", in_buffer);

        //~ printf ("Ask for a token (Press ): ");
    //~ }


    //~ if (mq_close (qd_client) == -1) {
        //~ perror ("Client: mq_close");
        //~ exit (1);
    //~ }

    //~ if (mq_unlink (client_queue_name) == -1) {
        //~ perror ("Client: mq_unlink");
        //~ exit (1);
    //~ }
    //~ printf ("Client: bye\n");

    //~ exit (0);
//~ }
/*
 * client.c: Client program
 *           to demonstrate interprocess communication
 *           with POSIX message queues
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdint.h>
#define SERVER_QUEUE_NAME   "/uds"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

int main (int argc, char **argv)
{
    //~ char client_queue_name [64];
    mqd_t qd_server, qd_client;   // queue descriptors


    // create the client queue for receiving messages from server
    //~ sprintf (client_queue_name, "/doip", getpid ());
	char* client_queue_name = "/doip";
    struct mq_attr attr;
    printf("client_queue_name = %d \n", strlen(client_queue_name));
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    if ((qd_client = mq_open (client_queue_name, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
        perror ("Client: mq_open (client)");
        exit (1);
    }

    if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_WRONLY)) == -1) {
        perror ("Client: mq_open (server)");
        exit (1);
    }

    char in_buffer [MSG_BUFFER_SIZE];

    printf ("Ask for a token (Press <ENTER>): ");

    char temp_buf [10];

    while (fgets (temp_buf, 4, stdin)) {
         uint8_t buff [256] = {0x00};
         uint8_t aa = 0x00;
         uint8_t bb = 0x00;
         printf("temp_buf[0] =%x\n",temp_buf[0]);
         printf("temp_buf[1] =%x\n",temp_buf[1]);

         memcpy(buff,client_queue_name,strlen (client_queue_name));
         buff[10] = (((temp_buf[0] -0x30)<<0x04) | (temp_buf[1] -0x30));
         buff[11] = ((temp_buf[1] - 0x30) << 8) | ((temp_buf[0] - 0x30));
         buff[12] = 0x01;
         printf("buff0=%x\n",buff[0]);
         printf("buff1=%x\n",buff[1]);
         printf("buff2=%x\n",buff[2]);
         printf("buff3=%x\n",buff[3]);
         printf("buff4=%x\n",buff[4]);
         printf("buff5=%x\n",buff[5]);
         printf("buff10=%x\n",buff[10]);
         printf("buff11=%x\n",buff[11]);
         printf("buff12=%x\n",buff[12]);
         printf("buff13=%x\n",buff[13]);
         
        //~ // send message to server
        //~ if (mq_send (qd_server, buff, 10, 0) == -1) {
            //~ perror ("Client: Not able to send message to server");
            //~ continue;
        //~ }
        // send message to server
        if (mq_send (qd_server, buff, 14, 0) == -1) {
            perror ("Client: Not able to send message to server");
            continue;
        }

        // receive response from server

        if (mq_receive (qd_client, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {
            perror ("Client: mq_receive");
            exit (1);
        }
        // display token received from server
        printf ("in_buffer[0]=%x\n", in_buffer[0]);
        printf ("in_buffer[1]=%x\n", in_buffer[1]);
        printf ("in_buffer[2]=%x\n", in_buffer[2]);

        printf ("Ask for a token (Press ): ");
    }


    if (mq_close (qd_client) == -1) {
        perror ("Client: mq_close");
        exit (1);
    }

    if (mq_unlink (client_queue_name) == -1) {
        perror ("Client: mq_unlink");
        exit (1);
    }
    printf ("Client: bye\n");

    exit (0);
}
