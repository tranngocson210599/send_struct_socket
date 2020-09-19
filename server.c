// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 
int main(int argc, char const *argv[]) 
{ 
	int server_fd;//descriptor socket
    int new_socket;
    int valread; // uisng in read()
    /*
    struct sockaddr_in 
    {
    short            sin_family;   // e.g. AF_INET
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
    };
    */
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	char *test = "Hello from server"; 
	
	// Creating socket file descriptor 
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	//printf("server_fd : %d\n ",server_fd);
	// Forcefully attaching socket to the port 8080 
	//setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    //printf("setsockopt : %d\n ",setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt
                                                                              //  , sizeof(opt)));

    address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
	bind(server_fd, (struct sockaddr *)&address, sizeof(address));
	
    //printf("bind: %d\n",bind(server_fd, (struct sockaddr *)&address, sizeof(address)));
    //int listen(int sockfd, int backlog)
    // backlog20192019:defines the maximum length to which the queue of pending connections for sockfd may grow
	listen(server_fd, 3);
	
    //printf("listen : %d\n",listen(server_fd,3));
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen) ;
    printf("Hello message sent\n"); 
	valread = read( new_socket , buffer, 1024); 
    printf("%s\n",buffer ); 
	send(new_socket , test , strlen(test) , 0 ); 
	return 0; 
} 
