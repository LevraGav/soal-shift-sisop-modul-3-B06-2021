#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <fcntl.h>
#define PORT 8080

char sent[1024];
char recieve[1024];
char buff[1024];
bool loggedIn=false;
int soc;

void Reg() {
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


void Log() {
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
    if(recieve[0]=='L'){
        loggedIn=true;
    }
    memset(recieve,0,sizeof(recieve));
}

void resR() {
    read(soc,recieve,1024);
    printf("%s\n",recieve);
    memset(recieve,0,sizeof(recieve));
}

void sends(char data[]) {
    send(soc,data,strlen(data),0);
    memset(sent,0,sizeof(sent));
}

void addFiles() {
    char temp[1024];
    for (int i=0;i<3;i++) {
        resR();
        scanf("%s",temp);
        temp[strcspn(temp,"\n")] =0;
        sends(temp);
    }
    FILE *sfd = fopen(temp,"rb");  
    char data[1024] = {0};
    int n;
    while(1){
        memset(data,0,1024);
        n=fread(sfd,data,1024);
        //printf("%d",n);
        send(soc,data,n,0);
        if(n==0) {
            break;
        }
        break;
    }
    printf("break"); 
    fclose(sfd);
    resR();
}

void download() {
    resR();
    char temp[1024];
    scanf("%s",temp);
    temp[strcspn(temp,"\n")] =0;
    sends(temp);
    read(soc,recieve,1024);
    printf("%s\n",recieve);
    if (strlen(recieve)<=15) {
        char dir[300] = "/home/bayu/Documents/Prak3/";
        strcat(dir,temp);
        FILE *file = fopen(dir,"w");
        char buffer[1024]={0};
        while (1) {
            memset(buffer,0,sizeof(buffer));
            int len = read(sd,buffer,1024);
            fprintf(file,"%s",buffer);
            break;
        }
        printf("break\n");
        fclose(file);
        resR();
    }
}

int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
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
        pthread_t thread;
        char command[100];
        scanf("%s",command);
        strcpy(sent,command);
        send(soc,sent,strlen(sent),0);
        memset(sent,0,sizeof(sent));
       if (strcmp(command,"register")==0){
                Reg();
                continue;
            }
            else if (strcmp(command,"login")==0){
                Log();
            }
            else if (strcmp(command,"add")==0 && loggedIn) {
                addFiles();
            }
            else if (strcmp(command,"donwload")==0 && loggedIn) {
                download();
            }
            else {
                printf("Command salah,perhatikan penulisan anda\n");
                continue;
            }
    }
    return 0;
}
