#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#define PORT 8080

char sent[1024];
char recieve[1024];
char buff[1024];
char user[30];
char command[100];
bool loggedIn = false;

void addUser(char str[]) {
    printf("ADDUSER\n");
    char idpass [100];
    strcpy(idpass,str);
    printf("%s\n",idpass);
    FILE* file = fopen("akun.txt", "a") ;
    fputs(idpass,file);
    fclose(file);
}

bool LogUser(char str[]) {
    printf("LogUser\n");
    char idpass [100];
    strcpy(idpass,str);
    printf("%s\n",idpass);
    char *id;
    char tok[2]=":";
    char find[100];
    FILE* file = fopen("akun.txt","r");
    while (fgets(find,100,file)) {
        printf("%s %s\n",find,idpass);
        if (strcmp(find,idpass)==0) {
            fclose(file);
            id = strtok(idpass,tok);
            strcpy(user,id);
            loggedIn = true;
            return true;
        }
    }
    return false;
}

int connectionCheck(){
    return 1;
}
 
int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024];
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    bool connected = false;
    while(1) {
        if(!connected) {
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            printf("CONNECTED\n");
            connected = true;
            strcpy(sent,"Register / Login?\n");
            printf("%s\n",sent);
            send(new_socket,sent,strlen(sent),0);
            memset(sent,0,sizeof(sent));
        }
        else {
            memset(command,0,sizeof(command));
            read(new_socket,command,100);
            printf("Recieve: %s\n",command);
            if(connectionCheck()) {
                if (strcmp(command,"register")==0) {
                    printf("register\n");
                    strcpy(sent,"Register\nInput ID dan password dipisah oleh spasi\nEx: Bayu 123");
                    send(new_socket,sent,strlen(sent),0);
                    memset(sent,0,sizeof(sent));
                    read(new_socket,recieve,1024);
                    addUser(recieve);
                    memset(recieve,0,sizeof(recieve));
                    strcpy(sent,"Registrasi berhasil, silahkan login!\n");
                    send(new_socket,sent,strlen(sent),0);
                    memset(sent,0,sizeof(sent));
                    continue;
                }
                if (strcmp(command,"login")==0) {
                    printf("login\n");
                    strcpy(sent,"Login\nInput ID dan password dipisah oleh spasi\nEx: Bayu 123");
                    send(new_socket,sent,strlen(sent),0);
                    memset(sent,0,sizeof(sent));
                    read(new_socket,recieve,1024);
                    if (LogUser(recieve)) {
                        sprintf(sent,"Login sukses,selamat datang %s\n",user);
                        send(new_socket,sent,strlen(sent),0);
                    }
                    else {
                        strcpy(sent,"ID atau password salah\n");
                        send(new_socket,sent,strlen(sent),0);
                    }
                    memset(sent,0,sizeof(sent));
                    memset(recieve,0,sizeof(recieve));
                    continue;
                }
            }
            else {
                connected = 0;
            }
        }   
    }
    return 0;
}
