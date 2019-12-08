/*****************************************************************************************************************************************
 *                                                                                                                                       *
 *  @author: Ankit Dimri                                                                                                                 *
 *  TCP client                                                                                                                           *
 *                                                                                                                                       *
 *****************************************************************************************************************************************/

#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fstream>

/* port at which the server operates */
#define PORT 1721
#define SA struct sockaddr

 /* Socket file descriptor */
 int sockfd;

 /* Structure of the message that will be sent to the server */
 struct msg {
     char filename [100];
     char file [2048];
 };

 /* Signal handler for ctrl+c to terminate the infinite client properly by closing the socket */
 void sig_handler(int signo) {

     /* signal handler */
     if (signo == SIGINT) {
         std::cout << "\t Exiting..." << '\n';
         close (sockfd);
         exit (1);
     }
 }

 void func(int sockfd) {

    	msg buffer;
    	while (1) {
    		memset (buffer.filename, 0, sizeof (buffer.filename));
        memset (buffer.file, '\0', sizeof (buffer.file));
    	  std::cout << "\n\t Enter the filename: ";
    		std::cin >> buffer.filename;

        std::ifstream file;
        file.open (buffer.filename);
        file.seekg (0);
        char c;
        int i = 0;

        while (!file.eof ()) {
            file.get (c);
            buffer.file [i] = c;
            i++;
        }

    		write (sockfd, &buffer, sizeof(buffer));

        std::cout << "\n\t File read and sent to the server..." << '\n';

        std::cout << "\n\t file: " << '\n';
        std::cout << buffer.file << '\n';

    	}

}

 int main(int argc, char const *argv[]) {

	   sockaddr_in servaddr, cli ;

	   /* socket create and varification */
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



	   /* connect the client socket to server socket */
	   if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		   printf("connection with the server failed...\n");
		   exit(0);
	   }
	   else
		   printf("connected to the server..\n");
	   func(sockfd);

     return 0;
 }
