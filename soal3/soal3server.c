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
bool loggedIn = false;

void addUser(char str[]) {
    printf("ADDUSER\n");
    char idpass [100];
    char *token = strtok(str, " ");
    char id[30];
    strcpy(id,token);
    char password[30];
    while (token!=NULL) {
        token = strtok(NULL, " ");
    }
    strcpy(password,token);
    sprintf(idpass,"%s:%s",id,password);
    FILE* file = fopen("akun.txt", "a") ;
    fputs(idpass,file);
    fclose(file);
}

bool LogUser(char str[]) {
    char idpass [100];
    char *token = strtok(str, " ");
    char id[30];
    strcpy(id,token);
    char password[30];
    while (token!=NULL) {
        token = strtok(NULL, " ");
    }
    strcpy(password,token);
    sprintf(idpass,"%s:%s",id,password);
    char find[100];
    FILE* file = fopen("akun.txt","a");
    while (fgets(find,100,file)) {
        if (strcmp(find,idpass)==0) {
            fclose(file);
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
        }
        else {
            read(new_socket,recieve,1024);
            printf("Recieve: %s\n",recieve);
            if(connectionCheck()) {
                if (strcmp(recieve,"register")==0) {
                    printf("register\n");
                    strcpy(sent,"Register\nInput ID dan password dipisah oleh spasi\n Ex: Bayu 123");
                    send(new_socket,sent,strlen(sent),0);
                    read(new_socket,recieve,1024);
                    addUser(recieve);
                    strcpy(sent,"Registrasi berhasil, silahkan login!\n");
                    send(new_socket,sent,strlen(sent),0);
                    continue;
                }
                if (strcmp(recieve,"login")==0) {
                    printf("login\n");
                    strcpy(sent,"Login\nInput ID dan password dipisah oleh spasi\n Ex: Bayu 123");
                    send(new_socket,sent,strlen(sent),0);
                    read(new_socket,recieve,1024);
                    if (LogUser(recieve)) {
                        strcpy(sent,"Login sukses\n");
                        send(new_socket,sent,strlen(sent),0);
                    }
                    else {
                        strcpy(sent,"ID atau password salah\n");
                        send(new_socket,sent,strlen(sent),0);
                    }
                }
            }
            else {
                connected = 0;
            }
        }   
    }
    return 0;
}
