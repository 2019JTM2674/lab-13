// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>  
#define PORT 8080 

int main(int argc, char const *argv[]) 
{ 
	int sock = 0, valread,clientReceive; 
	struct sockaddr_in serv_addr; 
	char *hello = "Hello from client"; 
	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
	// send(sock , hello , strlen(hello) , 0 ); 
	// printf("Hello message sent\n"); 
	// valread = read( sock , buffer, 1024); 
	// printf("%s\n",buffer ); 

    char user[30],pass[30],data[1024]={0},temp[50];
    char message[30],option[20]={0};



    start: printf("Enetr Usernmae\n");
    scanf("%s",user);
    send(sock , user , strlen(user) , 0 );
    printf("Enetr Password\n");
    scanf("%s",pass);
    send(sock , pass , strlen(pass) , 0 );
    bzero(buffer,sizeof(buffer)); 
    clientReceive = read( sock , buffer, 1024); 
    printf("%s",buffer);
    strcpy(message,buffer);
    bzero(buffer,sizeof(buffer)); 
    if(strcmp(message,"Invalid User")==0){
        goto start;
    }
	printf("Type Exit to exit chat\n");
    while(1){
        fgets (buffer, 1023, stdin);
        send(sock , buffer , strlen(buffer) , 0 );
		printf("Press Y else continue\n");
		//fgets (buffer, 1023, stdin);
        int z = strcmp(buffer,"Y");
		if(z==10){
			printf("Enetr Mobile");
			fgets (buffer, 1023, stdin);
        	send(sock , buffer , strlen(buffer) , 0 );
			exit(0);
			break;
		}
		else
		{
			bzero(buffer,sizeof(buffer));
			continue;
		}
		
		
    }
	printf("%s",data);
    
	return 0; 
} 
