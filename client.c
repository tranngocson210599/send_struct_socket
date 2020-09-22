
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#define MAX 80 
#define PORT 8081 
#define SA struct sockaddr 

struct Task
{
    int mType;
    int tType;
    int cCnt;
    int* cId;
    char data[128];
};
unsigned char * serialize_int(unsigned char *buffer, int value)
{
    buffer[0] = value >> 24;
    buffer[1] = value >> 16;
    buffer[2] = value >> 8;
    buffer[3] = value;
    return buffer + 4;
}

unsigned char * serialize_char(unsigned char *buffer, char value)
{
    buffer[0] = value;
    return buffer + 1;
}

int deserialize_int(unsigned char *buffer)
{
    int value = 0;

    value |= buffer[0] << 24;
    value |= buffer[1] << 16;
    value |= buffer[2] << 8;
    value |= buffer[3];
    return value;

}

char deserialize_char(unsigned char *buffer)
{
    return buffer[0];
}

unsigned char* serializeTask(unsigned char* msg, const  struct Task* t)
{
    msg = serialize_int(msg,t->mType);
    msg = serialize_int(msg,t->tType);
    msg = serialize_int(msg,t->cCnt);
    for(int i=0; i<t->cCnt; i++)
            msg = serialize_int(msg,t->cId[i*4]);

for(int i=0; i<strlen(t->data); i++)
    msg = serialize_char(msg,t->data[i]);

    return msg;
}

void func(int sockfd) 
{ 
	//char buff[MAX]; 
	char * buff;
	int n; 
	struct Task* t;
	t->cCnt=1;
	//t->cId=2;
	t->mType=3;
	t->data[0]='s';
	t->cId[0]=5;
//	for (;;) { 
		bzero(buff, sizeof(buff)); 
		printf("Message to server : "); 
		n = 0; 

	//	while ((buff[n++] = getchar()) != '\n') ; 
	    
		write(sockfd, buff, sizeof(buff)); 
		bzero(buff, sizeof(buff)); 
		read(sockfd, buff, sizeof(buff)); 
		printf("From Server : %s", buff); 
		if ((strncmp(buff, "exit", 4)) == 0) { 
			printf("Client Exit...\n"); 
//			break; 
//		} 
	} 
} 

int main() 
{ 
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 

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
    servaddr.sin_addr.s_addr = inet_addr("10.230.5.186"); 
     
    servaddr.sin_port = htons(PORT); 

	// connect the client socket to server socket 
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("connection with the server failed...\n"); 
		exit(0); 
	} 
	else
		printf("connected to the server..\n"); 

struct Task* t;
	t->cCnt=1;
	//t->cId=2;
	t->mType=3;
	t->data[0]='s';
	t->cId[0]=5;
	char * buff;
	buff=serializeTask(buff,t);
		for(int i=0;i<sizeof(buff)/sizeof(char);i++)
		printf("%d",buff[i]);
	// function for chat 
	//func(sockfd); 

	// close the socket 
	close(sockfd); 
} 
