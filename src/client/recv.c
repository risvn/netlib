#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "menu.h" 



#define BUF_SIZE 1024
#define PORT "3940" 

char* file_ls[100];
int count=0;

void name_array(char* file_names){
char* name=strtok(file_names,"\n");

  while(name!=NULL){
    file_ls[count++]=name;
    //DEBUG: printf("file_names %s\n",name);
    name=strtok(NULL,"\n");
  }

   //DEBUG: printf("file_names %s\n",file_ls[5]);
}

void rcv_ex(int sockfd){
    int bytes=0;
    send(sockfd,"OK",2, 0);
    int total_bytes=0;
    int capacity =BUF_SIZE;
    char* file_names=malloc(capacity);
    char buffer[BUF_SIZE];
      while(1){
     if(capacity<total_bytes+bytes){
        capacity*=2;
        file_names=realloc(file_names,capacity);
        //TODO ERROR HANDLING
      }
      bytes=recv(sockfd,buffer,BUF_SIZE,0);
      //printf("rcv %s\n",buffer);
      memcpy(file_names+total_bytes,buffer,bytes);
      total_bytes+=bytes;

    if (bytes == 0) {
            printf("FILES RCVD\n");
            break;
          }

      }

     name_array(file_names);
}

int main(int argc,char* argv[]){

struct addrinfo hints,*server;
memset(&hints, 0, sizeof hints);
hints.ai_family = AF_INET;
hints.ai_socktype = SOCK_STREAM;

int status=getaddrinfo("localhost",PORT,&hints,&server);

int sockfd=socket(server->ai_family,server->ai_socktype,0);
  
 
   //connect

  if(connect(sockfd, server->ai_addr, server->ai_addrlen) < 0)
    {
        perror("connect");
        return 1;
    }
   mkdir("shared", 0755);
  FILE *fp = fopen("shared/received_file", "wb");

    char buffer[BUF_SIZE];
    int bytes;

    while((bytes=recv(sockfd,buffer,BUF_SIZE,0))>0){
    char check[4];
    strncpy(check,buffer,3);
    check[3]='\0';
    if(!strcmp(check,"SOF")){
      //TODO: make this function to return the char* from heap
      rcv_ex(sockfd);
      show_menu(count,file_ls);
    }
        
     }

    fclose(fp);

    printf("File received\n");

    close(sockfd);

return 0;
}
