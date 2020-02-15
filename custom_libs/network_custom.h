#include <stdio.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT     8888 
#define MAXLINE 24 
#define SERVERADDRESS "192.168.1.201"


int send_command(char* cmd){
    char buffer[100]; 
    char *message = (char*)malloc(MAXLINE * sizeof(char)); 
    strcpy(message,cmd);
    int sockfd, n; 
    struct sockaddr_in servaddr; 
    // clear servaddr 
    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_addr.s_addr = inet_addr(SERVERADDRESS); 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_family = AF_INET; 
      
    // create datagram socket 
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
    // connect to server 
    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
    { 
        return -1; 
    } 
    // request to send datagram 
    // no need to specify server address in sendto 
    // connect stores the peers IP and port 
    sendto(sockfd, message, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr));  
    // waiting for response 
    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL); 
    // close the descriptor 
    close(sockfd); 
    return 0;
}