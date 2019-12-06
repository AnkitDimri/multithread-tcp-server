/*****************************************************************************************************************************************
 *                                                                                                                                       *
 *  @author: Ankit Dimri                                                                                                                 *
 *  Multithreaded TCP server. Server name 'MISTCP'                                                                                       *
 *                                                                                                                                       *
 *****************************************************************************************************************************************/
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <fstream>
#include <string>
#include <cstring>
#include <signal.h>

/* Server port number, at which it listens */
#define PORT 1721

 pthread_t thread_tcp [100], thread_file [10];
 int threadno_tcp = 0;
 int mistfd; // server file descriptor

 /* message type that will be sent by the client through TCP connection */
 struct msg {
     char filename [100];
     char file [2048];
 };

 /* Structure to hold the necessary parameters to pass into the threaded function */
 struct req {
     int des;
     socklen_t addlen;
     sockaddr_in clientaddr;
 };

 void* tcp_connection (void*);

 /* Signal handlre for ctrl+c to terminate the infinite server properly by closing the socket */
 void sig_handler(int signo) {

     /* signal handler */
     if (signo == SIGINT) {
         std::cout << "\t Exiting..." << '\n';
         close (mistfd);
         exit (0);
     }
 }

 int main(int argc, char const *argv[]) {

   /* server name : Mistcp */
   sockaddr_in mistaddr; // server address
   sockaddr_in clientaddr; // client address

   socklen_t addrlen = sizeof(clientaddr);

   /* Create socket */
   if ((mistfd = socket (AF_INET, SOCK_STREAM, 0)) == -1) {
       std::cout << "\n\t Socket creation failed...\n\t Exiting..." << '\n';
       return 0;
   }

   std::cout << "\n\t Socket created..." << '\n';

   memset ((sockaddr*)&mistaddr, 0, sizeof (mistaddr));
   mistaddr.sin_family = AF_INET;   // IPv4 address family
   mistaddr.sin_addr.s_addr = htonl (INADDR_ANY);  // Give the local machine address
   mistaddr.sin_port = htons (PORT); // Port at which server listens to the requests

   /* Bind the IP address and the port number to craete the socket */
   if (bind (mistfd, (sockaddr*)&mistaddr, sizeof (mistaddr)) != 0) {
       std::cout << "\n\t Binding failed...\n\t Exiting..." << '\n';
       return 0;
   }

   std::cout << "\n\t Binding succesful..." << '\n';

   if ((listen (mistfd, 5)) != 0) {
      std::cout << "\n\t Server not listning..." << '\n';
      return 0;
   }

   std::cout << "\n\t Server listning..." << '\n';

   while (1) {

      int connfd;
      if ((connfd = accept(mistfd,(sockaddr*)&clientaddr, &addrlen)) < 0)
         std::cout << "\n\t Client connection declined..." << '\n';
      else
         std::cout << "\n\t Client connection accepted..." << '\n';

      /* Filling the parameter values of the threaded function */
      req *r = new req;  // allocate memory
      bzero (r, sizeof (req));  // Clear memory
      r->addlen = addrlen;
      r->clientaddr = clientaddr;
      r->des = connfd;

      pthread_create (&thread_tcp [threadno_tcp++], NULL, tcp_connection, (void*)r);
      if (threadno_tcp == 100)
          threadno_tcp = 0;

   }

 }

 void* tcp_connection (void*  arg) {
     req sock = *((req*)arg);
     msg buffer;

     while (1) {
       /* Read the packet sent by the established client */
       read (sock.des, &buffer, sizeof(buffer));

       std::cout << "\n\t File name: " << buffer.filename;
       std::cout << "\n\n" << buffer.file << '\n';
     }

 }
