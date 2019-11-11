#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <signal.h>

#define MAX 80
#define PORT 50020
#define SA struct sockaddr

 struct msg {
     char filename [100];
     char word [20];
 };

 /* Signal handlre for ctrl+c to terminate the infinite client properly by closing the socket */
 void sig_handler(int signo) {

     /* signal handler */
     if (signo == SIGINT) {
         std::cout << "\t Exiting..." << '\n';
         close (fd);
         exit (1);
     }
 }

 int main(int argc, char const *argv[]) {

     int sockfd, connfd;
	   struct sockaddr_in servaddr, cli ;

	   // socket create and varification
	   sockfd = socket(AF_INET, SOCK_STREAM, 0);
	   if (sockfd == -1) {
		     printf("socket creation failed...\n");
		       exit(0);
	   }
	   else
		   printf("Socket successfully created..\n");

     bzero(&servaddr, sizeof(servaddr));

	   // assign IP, PORT
	   servaddr.sin_family = AF_INET;
	   //servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	   inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	   servaddr.sin_port = htons(PORT);



	   // connect the client socket to server socket
	   if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		   printf("connection with the server failed...\n");
		   exit(0);
	   }
	   else
		   printf("connected to the server..\n");
	   func(sockfd);
	   close(sockfd);

     return 0;
 }
