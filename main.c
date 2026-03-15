#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

char ipstr[INET6_ADDRSTRLEN];


int main(int argv,char* argc[]){


struct addrinfo hints,*res,*p;
memset(&hints, 0, sizeof(hints));
hints.ai_family=AF_UNSPEC;
hints.ai_socktype=SOCK_STREAM;

int status = getaddrinfo("goolge.com", NULL, &hints, &res);
if (status != 0) {
        printf("Error: %s\n", gai_strerror(status));
        return 1;
    }
void* addr;
struct sockaddr_in* ipv4;
struct sockaddr_in6* ipv6;
char *ipver;


  //get
if(res->ai_family==AF_INET){
    ipv4 = (struct sockaddr_in *)res->ai_addr;
    addr = &(ipv4->sin_addr);
    ipver="ipv4";
  }
else{
        ipv6 = (struct sockaddr_in6 *)res->ai_addr;
        addr=&(ipv6->sin6_addr);
        ipver="ipv6";
  }
     // convert the IP to a string and print it:
        inet_ntop(res->ai_family, addr, ipstr, sizeof ipstr);
        printf("  %s: %s\n", ipver, ipstr);




















return 0;
}


