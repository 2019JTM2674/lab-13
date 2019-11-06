// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 6001 
void delay() 		//Delay function to avoid overlapping of data
{
   int c, d;
   
   for (c = 1; c <= 32767; c++)
       for (d = 1; d <= 32767; d++)
       {}
       
}
int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	char *hello = "Hello from server"; 
	char k[10]="user";
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

    
    FILE *fp;
    char ch;
    char m[30];
    char first_name[50],last_name[50],ten[20],inter[20],grad[20],work_exp[20];
    char s_first[50],s_last[50];
    char f[20],l[20],t[20],i[20],g[20],w[20];
    int ten_p,inter_p,grad_p;
    float work;
    int bi;
    
    float a,b,c,d,norm_score=0,s_norm;
    fp = fopen("new_file.txt","w+");
    if ( fp == NULL )
		{
			puts ( "Cannot open file" ) ;
			exit(0) ;
		}
    while((bi=recv(new_socket,buffer,1024,0))>0){
        //read(new_socket,buffer,1024);
        fprintf(fp,"%s\t",buffer);
        
        // ch=fgetc(fp);
    }
    
    fseek(fp,0,SEEK_SET);
    //send(new_socket , k , strlen(k) , 0 ); 
    while(fscanf ( fp, "%s %s %s %s %s %s %s %s %s %s %s %s",  f,first_name,l,last_name,t,ten,i,inter,g,grad,w,work_exp) != EOF){
        ten_p = atoi(ten);
        inter_p=atoi(inter);
        grad_p=atoi(grad);
        if(ten_p>90)
            a=10;
        else if(ten_p>80 && ten_p<=90)
            a=8;
        else if(ten_p>70 && ten_p<=80)
            a=5;
        else if(ten_p>60 && ten_p<=70)
            a=3;
        else if(ten_p>55 && ten_p<=50)
            a=2;
        else if(ten_p<=55)
            a=1;

        
        if(inter_p>90)
            b=10;
        else if(inter_p>80 && inter_p<=90)
            b=8;
        else if(inter_p>70 && inter_p<=80)
            b=5;
        else if(inter_p>60 && inter_p<=70)
            b=3;
        else if(inter_p>55 && inter_p<=50)
            b=2;
        else if(inter_p<=55)
            b=1;


        if(grad_p>85)
            c=10;
        else if(grad_p>75 && grad_p<=85)
            c=8;
        else if(grad_p>70 && grad_p<=75)
            c=5;
        else if(grad_p>65 && grad_p<=70)
            c=3;
        else if(grad_p>60 && grad_p<=65)
            c=2;
        else if(grad_p<=60)
            c=1;


        if(strcmp(work_exp,"NIL")==0){
            d=0;
            // printf("Here");
        }
        if(strcmp(work_exp,"NIL")!=0){
            work = atof(work_exp);
            // printf("work %f",work);
            if(work>36)
                d=1;
            else if(work>12 && work<=36){
                d= 1 + (work-12)/24;
                }
            else if(work<=12){
                d=1;
                }
        }
        // printf("%f\t%f\t%f\t%f",a,b,c,d);
        norm_score = (a+b+c+d)/33;
        
        s_norm=norm_score;
        sprintf(buffer,"%f",s_norm);
        //printf("str %s",buffer);
        //send(new_socket , buffer , strlen(buffer) , 0 ); 
        printf("Hey %s %s, your normalised score is %f\n",first_name,last_name,norm_score);
     
        
    }
    fclose(fp);
    // sprintf(buffer,"%f",s_norm);
    // printf("str %s",buffer);
    // send(new_socket , buffer , strlen(buffer) , 0 ); 
	return 0; 
} 
