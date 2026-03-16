#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>


char ipstr[INET6_ADDRSTRLEN];

#define PORT "3940"
#define BACKLOG 10 
#define BUFF_SIZE 1020 

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
  
  
//void* addr;
//struct sockaddr_in* ipv4;
//struct sockaddr_in6* ipv6;
//char *ipver;
//
//
//  //get
//if(res->ai_family==AF_INET){
//    ipv4 = (struct sockaddr_in *)res->ai_addr;
//    addr = &(ipv4->sin_addr);
//    ipver="ipv4";
//  }
//else{
//        ipv6 = (struct sockaddr_in6 *)res->ai_addr;
//        addr=&(ipv6->sin6_addr);
//        ipver="ipv6";
//  }
//     // convert the IP to a string and print it:
//        inet_ntop(res->ai_family, addr, ipstr, sizeof ipstr);
//       printf("  %s: %s\n", ipver, ipstr);


int sockfd=socket(res->ai_family,res->ai_socktype,0);
bind(sockfd,res->ai_addr,res->ai_addrlen);

listen(sockfd,BACKLOG);
printf("server: waiting for connections...\n");
struct sockaddr_storage client_addr;

int new_fd;
while(1){

socklen_t addr_size=sizeof client_addr;
new_fd=accept(sockfd,(struct sockaddr *)&client_addr,&addr_size);


char in_str[INET6_ADDRSTRLEN];
inet_ntop(client_addr.ss_family,get_in_addr((struct sockaddr *)&client_addr),in_str,sizeof in_str);
printf("server: got connection from %s\n", in_str);


//send the data you want
int bytes_sent=send_file(new_fd,argv[1]);
printf("server: bytes sent [%d]\n", bytes_sent);


//sending file over network


  close(new_fd);
  }
return 0;
}


