#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#define PORT 8080

char sent[1024];
char recieve[1024];
char buff[1024];
bool loggedIn=false;

void RegLog() {
    read(soc,recieve,1024);
    printf("%s\n",recieve);
    memset(recieve,0,sizeof(recieve));
    char uname[100];
    char pass[100];
    scanf("%s %s",uname,pass);
    sprintf(sent,"%s:%s\n",uname,pass);
    send(soc,sent,strlen(sent),0);
    memset(sent,0,sizeof(sent));
    read(soc,recieve,1024);
    printf("%s\n",recieve);
    memset(recieve,0,sizeof(recieve));
}

void resR() {
    memset(recieve,0,sizeof(recieve));
}

void sends(int socket,char data[]) {
    send(socket,data,strlen(data),0);
    memset(sent,0,sizeof(sent));
}

int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int soc=0;
    struct sockaddr_in serv_addr;
    if ((soc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(soc, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    else {
        read(soc,recieve,1024);
        printf("%s\n",recieve);
        memset(recieve,0,sizeof(recieve));
    }

    while(1)
    {
        char command[100];
        scanf("%s",command);
        strcpy(sent,command);
        send(soc,sent,strlen(sent),0);
        memset(sent,0,sizeof(sent));
        if (!loggedIn) {
            if (strcmp(command,"register")==0){
            RegLog();
            }
            if (strcmp(command,"login")==0){
                RegLog();
                read(soc,recieve,1024);
                if (strcmp(recieve,"1"==0) {
                    loggedIn=true;
                }
            }
        }
        if (loggedIn){
            
        }
    }
    return 0;
}
