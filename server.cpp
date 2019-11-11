#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>

 pthread_t thread [100];

 /* Structure to hold the necessary parameters to pass into the threaded reverse_string function */
 struct req {
     int des;
     char str [2048];
     socklen_t addlen;
     sockaddr_in clientaddr;
 };

 int main(int argc, char const *argv[]) {

   /* server name : Misty */
   sockaddr_in mistaddr; // server address
   sockaddr_in clientaddr; // client address
   int mistfd; // server file descriptor

   socklen_t addrlen = sizeof(clientaddr);
   int recvlen, msgcnt = 0;
   char buf [2048]; // Hold buffer sent in udp packet

   /* Create socket */
   if ((fd = socket (AF_INET, SOCK_DGRAM, 0)) == -1) {
       std::cout << "\n\t Socket creation failed...\n\t Exiting..." << '\n';
       return 0;
   }

   std::cout << "\n\t Socket created..." << '\n';

   memset ((sockaddr*)&mistaddr, 0, sizeof (mistaddr));
   mistaddr.sin_family = AF_INET;   // IPv4 address family
   mistaddr.sin_addr.s_addr = htonl (INADDR_ANY);  // Give the local machine address
   mistaddr.sin_port = htons (1721); // Port at which server listens to the requests

   /* Bind the IP address and the port number to craete the socket */
   if (bind (fd, (sockaddr*)&mistaddr, sizeof (mistaddr)) == -1) {
       std::cout << "\n\t Binding failed...\n\t Exiting..." << '\n';
       return 0;
   }

   std::cout << "\n\t Binding succesful..." << '\n';

   if (listen (mistfd, 5) != 0) {
      std::cout << "\n\t Server not listning..." << '\n';
      return 0;
   }

   std::cout << "\n\t Server listning..." << '\n';

   while (1) {

      if (accept(sockfd,(sockaddr_in*)&clientaddr, &addrlen) < 0)
         std::cout << "\n\t Client connection declined..." << '\n';
      else
         std::cout << "\n\t Client connection accepted..." << '\n';

      /* Filling the parameter values of the threaded function */
      req *r = new req;  // allocate memory
      bzero (r, sizeof (req));  // Clear memory
      r->addlen = addrlen;
      r->clientaddr = clientaddr;
      r->des = mistfd;

      pthread_create (&thread [threadno++], NULL, find_word, (void*)r);
      if (threadno == 100)
          threadno = 0;

   }

 }
