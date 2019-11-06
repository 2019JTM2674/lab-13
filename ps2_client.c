// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<ctype.h>
#include<stdlib.h>

#define PORT 6001

int main(int argc, char const *argv[]) 
{ 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char *hello = "Hello from client"; 
	char buffer[1024] = {0}; 
    char file_name[50];
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
	
    printf("Enetr file name\n");
    scanf("%s",file_name);
    FILE *fp = fopen(file_name,"r+");
    char ch;
    float norm;
    char first_name[50],last_name[50];
    char f[50],l[50],j[20];
    int p;
    if(fp == NULL){
        perror("Error opening file");
    }

    while(ch != EOF){
        fscanf(fp,"%s",buffer);
        write(sock,buffer,1024);
        ch = fgetc(fp);
    }
    printf("The file was sent successfully\n");
    bzero(buffer,sizeof(buffer));
    fseek(fp,0,SEEK_SET);

    while(fscanf ( fp, "%s %s",f,l) != EOF){
        if(strcmp(f,"FirstName:")==0){
            strcpy(first_name,l);
        }
        if(strcmp(f,"LastName:")==0){
            strcpy(last_name,l);
        }
    }
    fclose(fp);
    //read(sock,&norm,sizeof(float));
    //p = read(sock , buffer, 1024);
    printf("%s",buffer);
    bzero(buffer,sizeof(buffer));
    //p = read(sock , buffer, 1024);
    printf("Hey %s %s, your normalised score is %s\n",first_name,last_name,buffer);
	return 0; 
} 
