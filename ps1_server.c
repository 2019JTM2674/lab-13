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
	int server_fd, new_socket, valread; 
    int serverReceive;
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	char *hello = "Hello from server"; 
	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 



    char user[30], pass[30],data[1024],option[30]={0};
    char f_user[30], f_pass[30],f_mob[30],mobile_no[20];
    char message[30]="Valid User",invalid[30]="Invalid User";
    FILE *fp;
    int valid=0;
    //Receive Username
	serverReceive = read( new_socket , buffer, 1024); 
	strcpy(user,buffer);
	bzero(buffer,sizeof(buffer)); 
	

	//Recieve Password
	serverReceive = read( new_socket , buffer, 1024); 
	strcpy(pass,buffer);
    bzero(buffer,sizeof(buffer)); 

    printf("%s %s",user,pass);
    fp =fopen("user.txt","r");
    if ( fp == NULL )
		{
			puts ( "Cannot open file" ) ;
			exit(0) ;
		}
	while (fscanf ( fp, "%s %s %s", f_user,f_mob,f_pass ) != EOF )
			{
        
        	if(strcmp(f_pass,pass)==0&&strcmp(f_user,user)==0 )

        		valid=1;
			}
	fclose ( fp ) ;

    if(valid==1){
        send(new_socket , message , strlen(message) , 0 ); 
    }
    else
    {
        send(new_socket , invalid , strlen(invalid) , 0 ); 
    }


    while(1){
        serverReceive = read( new_socket , buffer, 1024);
        //printf("%s",buffer);
        int z = strcmp(buffer,"Y");
		if(z==10){
        	serverReceive = read( new_socket , buffer, 1024);
            strcpy(mobile_no,buffer);
            printf("%s",mobile_no);
			break;
		} 
    }
    // serverReceive = read( new_socket , buffer, 1024); 
    // printf("%s",buffer);
    // bzero(buffer,sizeof(buffer)); 
	return 0; 
} 
