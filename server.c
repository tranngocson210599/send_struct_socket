#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 80 
#define PORT 8081 
#define SA struct sockaddr 
#include <unistd.h>
// Function designed for chat between client and server. 
void func(int sockfd) 
{ 
	char buff[MAX]; 
	int n; 
	// infinite loop for chat 
	for (;;) 
    { 
		bzero(buff, MAX); 

		// read the message from client and copy it in buffer 
		read(sockfd, buff, sizeof(buff)); 
		// print buffer which contains the client contents 
		printf("Message from client: %s\t To client : ", buff); 
		bzero(buff, MAX); 
		n = 0; 
		// copy server message in the buffer 
		while ((buff[n++] = getchar()) != '\n') 
			; 

		// and send that buffer to client 
		write(sockfd, buff, sizeof(buff)); 

		// if msg contains "Exit" then server exit and chat ended. 
		if (strncmp("exit", buff, 4) == 0)  
         { 
			printf("Server Exit...\n"); 
			break; 
		 } 
	} 
} 

// Driver function 
int main() 
{ 
	int i=0;
	int sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 
	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	bzero(&servaddr, sizeof(servaddr)); 
	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 
	// Binding newly created socket to given IP and verification 
	bind(sockfd, (SA*)&servaddr, sizeof(servaddr));
	// Now server is ready to listen and verification 
	listen(sockfd, 5);
	len = sizeof(cli); 
	// Accept the data packet from client and verification 
	connfd = accept(sockfd, (SA*)&cli, &len); 
	// Function for chatting between client and server 
	func(connfd); 
	// After chatting close the socket 
	close(sockfd); 
} 

