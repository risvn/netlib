#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>


char ipstr[INET6_ADDRSTRLEN];



#define PORT "3940"
#define BACKLOG 10 
#define BUFF_SIZE 1020 

#define TYPE_DIR 1
#define TYPE_FILE 0
#define BUF_SIZE 10

void* get_in_addr(struct sockaddr* sa){
  if(sa->sa_family==AF_INET){
    return &(((struct sockaddr_in *)sa)->sin_addr);
  }
  return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}



int send_file(int client_fd,char* file_name){
  //TODO:handle edge cases for files
  char buffer[BUFF_SIZE];
  int file=open(file_name,O_RDONLY);
  int bytes;
  int bytes_sent=0;
  while((bytes=read(file,buffer,BUFF_SIZE))>0){
  bytes_sent+=send(client_fd,buffer,BUFF_SIZE,0);
  }
  return bytes_sent;
}

//[TYPE][LENGTH][DATA]
int send_dir(int client_fd,const char* dir_name){
  DIR* dp=opendir(dir_name);
  struct dirent* entry;
  
  char* file_ls[100];
  int count=0;
    send(client_fd,"SOF",3, 0);
    file_ls[count++]= "START"; 

    while((entry=readdir(dp))!=NULL){
    file_ls[count++]=strdup(entry->d_name);
    }
    file_ls[count++]= "END"; 

    closedir(dp);
    char buffer[BUF_SIZE];
    int bytes;
    bytes=recv(client_fd,buffer,BUF_SIZE,0);
    char check[3];
    strncpy(check,buffer,2);
    check[2]='\0';

  int snd_count=0;
    if(!strcmp(check,"OK")){ 
      printf("[client] %s\n",check);
  while(snd_count!=count){
    send(client_fd, file_ls[snd_count], strlen(file_ls[snd_count]), 0);
    send(client_fd, "\n", 1, 0);
    snd_count++;
  }
  }
    return 0;
  }




int main(int argc,char* argv[]){
struct addrinfo hints,*res;
memset(&hints, 0, sizeof(hints));
hints.ai_family=AF_UNSPEC;
hints.ai_socktype=SOCK_STREAM;
hints.ai_flags = AI_PASSIVE;

int status = getaddrinfo(NULL,PORT , &hints, &res);
if (status != 0) {
        printf("Error: %s\n", gai_strerror(status));
        return 1;
    }
  
int sockfd=socket(res->ai_family,res->ai_socktype,0);
bind(sockfd,res->ai_addr,res->ai_addrlen);

listen(sockfd,BACKLOG);
struct sockaddr_storage client_addr;

int new_fd;
while(1){

printf("server: waiting for connections...\n");
socklen_t addr_size=sizeof client_addr;
new_fd=accept(sockfd,(struct sockaddr *)&client_addr,&addr_size);


char in_str[INET6_ADDRSTRLEN];
inet_ntop(client_addr.ss_family,get_in_addr((struct sockaddr *)&client_addr),in_str,sizeof in_str);
printf("server: got connection from %s\n", in_str);


//send the data you want
//int bytes_sent=send_file(new_fd,argv[1]);
//printf("server: bytes sent [%d]\n", bytes_sent);
 send_dir(new_fd,argv[1]);


//sending file over network


  close(new_fd);
  }
return 0;
}


