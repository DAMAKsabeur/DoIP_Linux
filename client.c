

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
 
#define TRUE 1
 
/*
 * This program uses select to check that someone is
 * trying to connect before calling accept.
 */
 
main()
{
   int sock, length;
   struct sockaddr_in server;
   int msgsock;
   char buf[1024];
   int rval;
   fd_set ready;
   struct timeval to;
 
   /* Open a socket and bind it as in previous examples. */
 
   /* Start accepting connections. */
   listen(sock, 5);
   do {
      FD_ZERO(&ready);
      FD_SET(sock, &ready);
      to.tv_sec = 5;
      to.tv_usec = 0;
      if (select(1, &ready, (fd_set *)0, (fd_set *)0, &to) == -1) {
         perror("select");
         continue;
      }
      if (FD_ISSET(sock, &ready)) {
         msgsock = accept(sock, (struct sockaddr *)0,
            (int *)0);
         if (msgsock == -1)
            perror("accept");
         else do {
            memset(buf, 0, sizeof buf);
            if ((rval = read(msgsock, buf, 1024)) == -1)
               perror("reading stream message");
            else if (rval == 0)
               printf("Ending connection\n");
            else
               printf("-->%s\n", buf);
         } while (rval > 0);
         close(msgsock);
      } else
         printf("Do something else\n");
   } while (TRUE);
	   exit(0);
}
