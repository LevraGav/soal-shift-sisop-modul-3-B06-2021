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
bool connected = false;
int master_socket , new_socket , client_socket[30]= {0},max_clients = 30 , activity, i , valread , sd; // GFG
fd_set readfds;
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

void resR() {
    memset(recieve,0,sizeof(recieve));
}

void bRead() { // check Disconnects + Read vals
    int check;
    if (check = read(new_socket,recieve,1024) == 0){
        connected=false;
        loggedIn=false;
        close(sd);
        int temp=client_socket[0];
        for(i=0;i<30;i++)
        {
            client_socket[i]=client_socket[i+1];
        }
        client_socket[n-1]=temp;
    }
}

void bReadCommand() { // check Disconnects + Read vals
    int check;
    if (check = read(new_socket,command,100) == 0){
        connected=false;
        loggedIn=false;
        close(sd);
        int temp=client_socket[0];
        for(i=0;i<30;i++)
        {
            client_socket[i]=client_socket[i+1];
        }
        client_socket[n-1]=temp;
    }
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

void sends(char data[]) {
    send(socket,data,strlen(data),0);
    memset(sent,0,sizeof(sent));
}


void addFiles(int socket) { 
    char publisher[1024] = {0};
	char tahun[1024] = {0};
	char path[1024] = {0};
    sends(socket,"Publisher:\nTahun Publikasi:\n Filepath:\n");
}
 
int main(int argc, char const *argv[]) {  
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024];
      
    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt),sizeof(opt)<0)) {
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
    while(1) {
        //clear the socket set 
        FD_ZERO(&readfds);  
     
        //add master socket to set 
        FD_SET(master_socket, &readfds);  
        max_sd = master_socket;  
             
        //add child sockets to set 
        for ( i = 0 ; i < max_clients ; i++)  
        {  
            //socket descriptor 
            sd = client_socket[i];  
                 
            //if valid socket descriptor then add to read list 
            if(sd > 0)  
                FD_SET( sd , &readfds);  
                 
            //highest file descriptor number, need it for the select function 
            if(sd > max_sd)  
                max_sd = sd;  
        } 
         //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely 
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
       
        if ((activity < 0) && (errno!=EINTR))  
        {  
            printf("select error");  
        }  
             
        //If something happened on the master socket , 
        //then its an incoming connection 
        if (FD_ISSET(master_socket, &readfds))  
        {  
            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
            {  
                perror("accept");  
                exit(EXIT_FAILURE);  
            }
             for (i = 0; i < max_clients; i++)  
            {  
                //if position is empty 
                if( client_socket[i] == 0 )  
                {  
                    client_socket[i] = new_socket;  
                    printf("Adding to list of sockets as %d\n" , i);  
                         
                    break;  
                }  
            }  
        }
        sd = client_socket[0];
        connected = true;
        printf("CONNECTED\n");
        strcpy(sent,"Register / Login?\n");
        printf("%s\n",sent);
        send(new_socket,sent,strlen(sent),0);
        memset(sent,0,sizeof(sent));
        while(loggedIn) {
            memset(command,0,sizeof(command));
            bReadCommand();
            printf("Recieve: %s\n",command);
            if (loggedIn==false) {
                if (strcmp(command,"register")==0) {
                    printf("register\n");
                    strcpy(sent,"Register\nInput ID dan password dipisah oleh spasi\nEx: Bayu 123");
                    send(new_socket,sent,strlen(sent),0);
                    bRead();
                    addUser(recieve);
                    sends("Registrasi berhasil, silahkan login!\n");
                    continue;
                    }
                if (strcmp(command,"login")==0) {
                    printf("login\n");
                    sends("Login\nInput ID dan password dipisah oleh spasi\nEx: Bayu 123");
                    bRead();
                    if (LogUser(recieve)) {
                        sprintf(sent,"Login sukses,selamat datang %s\n",user);
                        sends(sent);
                    }
                    else {
                        sends("ID atau password salah\n");
                    }
                        memset(recieve,0,sizeof(recieve));
                        sends(socket,"1"); 
                        continue;
                    }
                }
                if(loggedIn==true) {
                    if (strcmp(command,"add")) {
                        addFiles(new_socket);
                    }
                }
            }   
        }
    return 0;
}
