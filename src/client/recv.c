#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>



#define BUF_SIZE 1020
#define PORT "3940" 



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

  // 4. Receive file
    FILE *fp = fopen("shared/received_file", "wb");

  char buffer[BUF_SIZE];
  int bytes;
    while((bytes = recv(sockfd, buffer, BUF_SIZE, 0)) > 0)
    {
        fwrite(buffer, 1, bytes, fp);
    }

    fclose(fp);

    printf("File received\n");

    // 5. Close socket
    close(sockfd);

return 0;
}
