# soal-shift-sisop-modul-3-B06-2021
Laporan Penyelesaian Pengerjaan Soal Praktikum SISOP Modul 3 - Kelompok B06

# Anggota Kelompok
Anggota  | NRP
---------|-------
Faisal Reza Maulana | 05111940000009
Arvel Gavrilla R. | 05111940000040
Bayu Adjie Sidharta | 05111940000172

## Link-link
- [Soal](https://docs.google.com/document/d/1ud1JyncoSDAo5hA03wPvjn7QBHPUeUG1eBJ8ETtq2dQ/edit)
- [Jawaban Soal 1](https://github.com/LevraGav/soal-shift-sisop-modul-3-B06-2021/tree/main/soal1)
- [Jawaban Soal 2](https://github.com/LevraGav/soal-shift-sisop-modul-3-B06-2021/tree/main/soal2)
- [Jawaban Soal 3](https://github.com/LevraGav/soal-shift-sisop-modul-3-B06-2021/tree/main/soal3)

# --- No 1 ---
Keverk adalah orang yang cukup ambisius dan terkenal di angkatannya. Sebelum dia menjadi ketua departemen di HMTC, dia pernah mengerjakan suatu proyek dimana keverk tersebut meminta untuk membuat server database buku. Proyek ini diminta agar dapat digunakan oleh pemilik aplikasi dan diharapkan bantuannya dari pengguna aplikasi ini.

Akan tetapi, keverk saat itu masih belum paham dengan sistem server dan client. Bantulah Keverk untuk menyelesaikan proyek ini!

### Note
- Dilarang menggunakan system() dan execv(). Silahkan dikerjakan sepenuhnya dengan thread dan socket programming. 
- Untuk download dan upload silahkan menggunakan file teks dengan ekstensi dan isi bebas (yang ada isinya bukan touch saja dan tidak kosong) dan requirement untuk benar adalah percobaan dengan minimum 5 data.

### Struktur Direktori
```
.
├── Client
│   ├── client.c
│   ├── File2.extensi
│   └── File1.extensi
└── Server
    ├── akun.txt
    ├── files.tsv
    ├── server.c
    ├── running.log
    └── FILES
            ├── File2.extensi
            └── File1.ekstensi
```
Di dalam proyek itu, Keverk diminta: 

## 1A
Pada saat client tersambung dengan server, terdapat dua pilihan pertama, yaitu register dan login. Jika memilih register, client akan diminta input id dan passwordnya untuk dikirimkan ke server. User juga dapat melakukan login. Login berhasil jika id dan password yang dikirim dari aplikasi client sesuai dengan list akun yang ada didalam aplikasi server. Sistem ini juga dapat menerima multi-connections. Koneksi terhitung ketika aplikasi client tersambung dengan server. Jika terdapat 2 koneksi atau lebih maka harus menunggu sampai client pertama keluar untuk bisa melakukan login dan mengakses aplikasinya. Keverk menginginkan lokasi penyimpanan id dan password pada file bernama <b>akun.txt</b> dengan format :

<b>akun.txt</b>
```
id:password
id2:password2
```

### Pengerjaan
MultiConnection
```bash
int main(int argc, char const *argv[]) {  
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    
    DIR* dir = opendir("files");
    if (dir) {
        closedir(dir);
    } else if (ENOENT == errno) {
        mkdir("files", 0777);
    }
      
    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, &opt,sizeof(opt)) <0 ) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(master_socket, 3) < 0) {
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
        while(connected) {
        ...
        }
```
Server Register
```bash
    if (strcmp(command,"register")==0) {
    printf("register\n");
    strcpy(sent,"Register\nInput ID dan password dipisah oleh spasi\nEx: Bayu 123");
    send(new_socket,sent,strlen(sent),0);
    bRead();
    addUser(recieve);
    sends("Registrasi berhasil, silahkan login!\n");
    continue;
 }
    
void bRead() { // check Disconnects + Read vals
    resR();
    int check;
    if ((check = read(sd,recieve,1024)) == 0){
        connected=false;
        loggedIn=false;
        close(sd);
        for(i=0;i<30;i++)
        {
            client_socket[i]=client_socket[i+1];
        }
        client_socket[29]=0;
    }
}

void addUser(char str[]) {
    printf("ADDUSER\n");
    char idpass [100];
    strcpy(idpass,str);
    printf("%s\n",idpass);
    FILE* file = fopen("akun.txt", "a") ;
    fputs(idpass,file);
    fclose(file);
}

void sends(char data[]) {
    send(sd,data,strlen(data),0);
    memset(sent,0,sizeof(sent));
}
```
Client Register
```bash
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
```
Client Login
```bash
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
```
Server Login
```bash
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
        printf("%s%s\n",find,idpass);
        if (strcmp(find,idpass)==0) {
            strcpy(upass,idpass);
            fclose(file);
            id = strtok(idpass,tok);
            strcpy(user,id);
            loggedIn = true;
            return true;
        }
    }
    return false;
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
                        continue;
                    }
                }
```
### Penjelasan
Soal no 1 mempunyai 2 bagian yaitu, multiple connections dan register melalui client dan di record di akun.txt  
Untuk bagian 1 saya memodifikasi code dari geeks for geeks [Socket Programming in C/C++: Handling multiple clients on server without multi threading](https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading) dalam prograrm saya.
Cara kerjanya adalah membuat queue of connections yang setiap kali ada client yang disconnect akan menconnect ke client selanjutnya. Setiap kali sebuah client connect ke server, ia akan dimasukan ke array tersebut.

Untuk bagian 2 register, pertama client membaca input dari user yang berisi username dan password.
```bash
    char uname[100];
    char pass[100];
    scanf("%s %s",uname,pass);
    sprintf(sent,"%s:%s\n",uname,pass);
    send(soc,sent,strlen(sent),0);
    memset(sent,0,sizeof(sent));
```
lalu input akan diparse sesuai format yaitu "username:password" lalu akan dikirim ke server.
```bash
    bRead();
    char idpass [100];
    strcpy(idpass,str);
    printf("%s\n",idpass);
    FILE* file = fopen("akun.txt", "a") ;
    fputs(idpass,file);
    fclose(file);
```
setelah itu akan di read melalui fungsi "bRead". fungsi ini adalah fungsi helper dimana jika server menemukan "0" atau connection terminated ia akan drop connection dan menggeser array dan connect ke client baru.  
Lalu server membaca username dan password yang telah di parse lalu meng-append file tesebut ke line terakhir lalu close file.

![image](https://user-images.githubusercontent.com/31591861/119263168-261b0f80-bc08-11eb-95be-56bf16702098.png)

Untuk login pertama seperti dijelaskan di register, client akan mengirimkan username dan password yang sudah di parse ke server
Lalu untuk setiap entry akan dicheck username dan password yang telah di parse dengan akun.txt menggunakan
```bash
 while (fgets(find,100,file)) {
        printf("%s%s\n",find,idpass);
        if (strcmp(find,idpass)==0) {
            strcpy(upass,idpass);
            fclose(file);
            id = strtok(idpass,tok);
            strcpy(user,id);
            loggedIn = true;
            return true;
        }
    }
    return false;
}
```
Jika ada yang cocok, id dan password akan di save untuk running.log dan return true, jika tidak return false.  
Karena client juga perlu tau jika login sukses atau failed maka pengecekan dilakukan dengan
```bash
if(recieve[0]=='L'){
        loggedIn=true;
    }
memset(recieve,0,sizeof(recieve));
```
karena kita tau message yang akan dikirim jika sukses atau failed kita dapat menggunakan workaround ini untuk membuat user kita logged in di client
![image](https://user-images.githubusercontent.com/31591861/119264386-28cc3380-bc0d-11eb-9e02-53c019f0059e.png)
### Output
Setelah dijalankan file akun.txt akan menjadi seperti ini
![image](https://user-images.githubusercontent.com/31591861/119263180-3206d180-bc08-11eb-84e4-1ea3bc69f4f9.png)

## 1B
Sistem memiliki sebuah database yang bernama <b>files.tsv</b>. Isi dari <b>files.tsv</b> ini adalah <b>path file saat berada di server</b>, <b>publisher</b>, dan <b>tahun publikasi</b>. Setiap penambahan dan penghapusan file pada folder file yang bernama <b>FILES</b> pada server akan memengaruhi isi dari <b>files.tsv</b>. Folder <b>FILES</b> otomatis dibuat saat server dijalankan.

### Pengerjaan
```bash
int main(int argc, char const *argv[]) {  
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    
    FILE* dir = fopen("files.tsv","a");
    fclose("files.tsv","a");
}
```
### Penjelasan
```bash
int main(int argc, char const *argv[]) {  
    FILE* dir = fopen("files.tsv","a");
    fclose("files.tsv");
}
```
Jika file tidak ada maka buat.  
Jika ada karena append tidak ada yang dilakukan
### Output
![image](https://user-images.githubusercontent.com/31591861/119263348-dee14e80-bc08-11eb-8c25-3a2dc9396feb.png)

## 1C
Tidak hanya itu, Keverk juga diminta membuat fitur agar client dapat menambah file baru ke dalam server. Direktori <b>FILES</b> memiliki struktur direktori di bawah ini : 

Direktori <b>FILES</b>
```
File1.ekstensi
File2.ekstensi
```
Pertama client mengirimkan input ke server dengan struktur sebagai berikut :
Contoh Command Client :
```
add
```

Output Client Console :
```
Publisher:
Tahun Publikasi:
Filepath:
```

Kemudian, dari aplikasi client akan dimasukan data buku tersebut (perlu diingat bahwa Filepath ini merupakan <b>path file yang akan dikirim ke server</b>). Lalu client nanti akan melakukan pengiriman file ke aplikasi server dengan menggunakan socket. Ketika file diterima di server, maka row dari files.tsv akan bertambah sesuai dengan data terbaru yang ditambahkan.

### Pengerjaan
Server
```bash
    void addFiles() { 
    char publisher[1024] = {0};
	char tahun[1024] = {0};
	char path[1024] = {0};
    sends("Publisher:\n");
    bRead();
    strcpy(publisher,recieve);
    sends("Tahun Publish:\n");
    bRead();
    strcpy(tahun,recieve);
    sends("Filepath:\n");
    bRead();
    strcpy(path,recieve);
    char *ptr1;
    char slash ='/';
    ptr1 = strrchr( path, slash );
    ptr1++;
    char fname[100];
    strcpy(fname,ptr1);
    char ext[10];
    char *ptr2;
    char dot ='.';
    ptr2 = strrchr( path, dot );
    ptr2++;
    strcpy(ext,ptr2);
    char dir[300] = "/home/bayu/Documents/Prak3/files/";
    strcat(dir,fname);
    FILE* tsv = fopen("files.tsv","a");
    char info[5000];
    sprintf(info,"%s\t%s\t%s\t%s\t%s\n",fname,publisher,tahun,ext,path);
    fputs(info,tsv);
    fclose(tsv);
    writefile(dir); 
    sends("File berhasil ditambahkan\n");
    FILE* log = fopen("running.log","a");
    fprintf(log,"Tambah: %s %s",fname,upass);
    fclose(log);
}
```
Client
```bash
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
    
    while(1){
        memset(data,0,1024);
        size_t size = fread(data,sizeof(char),1024,sfd);
        send(soc,data,1024,0);
        break;
    }
    printf("break"); 
    fclose(sfd);
    resR();
}
```
### Penjelasan
Pertama User akan menginputkan Publisher, Tahun Publikasi dan Filepath dari file yang ingin dikirim. Hal ini dapat dilihat dari porsi dibawah untuk client dan server
SERVER
```bash
void addFiles() { 
    char publisher[1024] = {0};
	char tahun[1024] = {0};
	char path[1024] = {0};
    sends("Publisher:\n");
    bRead();
    strcpy(publisher,recieve);
    sends("Tahun Publish:\n");
    bRead();
    strcpy(tahun,recieve);
    sends("Filepath:\n");
    bRead();
    strcpy(path,recieve);
```
CLIENT
```bash
void addFiles() { 
    char temp[1024];
    for (int i=0;i<3;i++) {
        resR();
        scanf("%s",temp);
        temp[strcspn(temp,"\n")] =0;
        sends(temp);
    }
```
Lalu kita dapat mendapatkan filename dan extensionya dengan memanipulasi filepath yang dikirimkan dengan menggunakan strrchr.  
strrchr adalah sebuah function yang mereturn pointer ke sebuah kata atau huruf terakhir di array.
```bash
    char *ptr1;
    char slash ='/';
    ptr1 = strrchr( path, slash );
    ptr1++;
    char fname[100];
    strcpy(fname,ptr1);
    char ext[10];
    char *ptr2;
    char dot ='.';
    ptr2 = strrchr( path, dot );
    ptr2++;
    strcpy(ext,ptr2);
```
Hal ini dapat dimanfaatkan untuk mendapatkan filename dan extension dari file. Kita perlu ingat untuk menambah 1 dari pointernya karena kita tidak ingin mengambil "/"
atau pun "." karena jika kita menggunakan strrchr untuk kata "/home/bayu.txt" dengan karakter "/" function tersebut akan mereturn "/bayu"

lalu kita read dari data yang ingin dikirim dan disend ke server menggunakan fread dan while loop. Setelah itu kita send file sukses.
### Output
![image](https://user-images.githubusercontent.com/31591861/119264478-98422300-bc0d-11eb-9c03-d487f355b6f4.png)
![image](https://user-images.githubusercontent.com/31591861/119264494-a6903f00-bc0d-11eb-9cd4-f02b0dad58b0.png)
![image](https://user-images.githubusercontent.com/31591861/119264507-b3149780-bc0d-11eb-86b5-68c703aef50e.png)
![image](https://user-images.githubusercontent.com/31591861/119264509-b871e200-bc0d-11eb-9ed5-1f2e54079148.png)

## 1D
Dan client dapat mendownload file yang telah ada dalam folder FILES di server, sehingga sistem harus dapat mengirim file ke client. Server harus melihat dari files.tsv untuk melakukan pengecekan apakah file tersebut valid. Jika tidak valid, maka mengirimkan pesan error balik ke client. Jika berhasil, file akan dikirim dan akan diterima ke client di <b>folder client</b> tersebut. 

Contoh Command client :
```
download TEMPfile.pdf
```

### Pengerjaan
SERVER
```bash
void download () {
    sends("namafile.extension\n");
    bRead();
    bool flag;
    char find[200];
    recieve[strcspn(recieve,"\n")] =0;
    strcpy(find,recieve);
    FILE* file = fopen("files.tsv", "r");
    char lines[1024];
    while (fgets(lines,1024,file)) {
        char *token;
        char found[100];
        char *linesz = lines;
        char *rest;
        token = strtok_r(linesz,"\t",&rest);
        strcpy(found,token);
        if (strcmp(find,found)==0){
            flag = true;
            break;
        }
    }
    if (flag==true) {
        sends("File found\n");
        char temp[104]="/home/bayu/Documents/Prak3/files/";
        strcat(temp,find);
        FILE *sfd = fopen(temp,"rb");  
        char data[4096] = {0};
        while(1){
            memset(data,0,4096);
            size_t size = fread(data,sizeof(char),4096,sfd);
            send(sd,data,strlen(data),0);
            break;
        }
        printf("break"); 
        fclose(sfd); 
    }
    else {
        sends("Sorry file not found,did you misstype?\n");
    }
}
```
CLIENT
```bash
 resR();
    char temp[1024];
    scanf("%s",temp);
    temp[strcspn(temp,"\n")] =0;
    sends(temp);
    read(soc,recieve,1024);
    printf("%s\n",recieve);
    if (recieve[0]=='F') {
        char dir[300] = "/home/bayu/Documents/Prak3/";
        strcat(dir,temp);
        FILE *file = fopen(dir,"w");
        char buffer[4096]={0};
        while (1) {
            memset(buffer,0,sizeof(buffer));
            int len = read(soc,buffer,4096); 
            fprintf(file,"%s",buffer);
            break;
        }
        printf("break\n");
        fclose(file);
    }
```
### Penjelasan
Pengerjaan soal ini seperti soal 3 tapi dibalik saja dari server ke client. 
```bash
 sends("namafile.extension\n");
    bRead();
    bool flag;
    char find[200];
    recieve[strcspn(recieve,"\n")] =0;
    strcpy(find,recieve);
    FILE* file = fopen("files.tsv", "r");
    char lines[1024];
    while (fgets(lines,1024,file)) {
        char *token;
        char found[100];
        char *linesz = lines;
        char *rest;
        token = strtok_r(linesz,"\t",&rest);
        strcpy(found,token);
        if (strcmp(find,found)==0){
            flag = true;
            break;
        }
    }
```
Seperti pencarian nama, kita mencari dalam file yang sudah diparse menggunakan Strtok untuk mencari string sebelum tab pertama yaitu nama file dengan apa yang ingin didownloaa.
jika ditemukan akan dikirim "File Found". Dengan menggunakan workaround soal 1a kita dapat mendetermine apakah file ada atau tidak. Jika ada, dengan menggunakan cara 1c kita mengirim dari server ke client.
```bash
 if (flag==true) {
        sends("File found\n");
        char temp[104]="/home/bayu/Documents/Prak3/files/";
        strcat(temp,find);
        FILE *sfd = fopen(temp,"rb");  
        char data[4096] = {0};
        while(1){
            memset(data,0,4096);
            size_t size = fread(data,sizeof(char),4096,sfd);
            send(sd,data,strlen(data),0);
            break;
        }
        printf("break"); 
        fclose(sfd); 
    }
```

### Output
![image](https://user-images.githubusercontent.com/31591861/119264880-01766600-bc0f-11eb-812f-2840b82e989d.png)

Sebelum download
![image](https://user-images.githubusercontent.com/31591861/119264856-f6233a80-bc0e-11eb-9f94-5675c6eeb125.png)

Sesudah download  
![image](https://user-images.githubusercontent.com/31591861/119265076-9bd6a980-bc0f-11eb-95f5-a4540543c6a7.png)

![image](https://user-images.githubusercontent.com/31591861/119264906-15ba6300-bc0f-11eb-87b9-15ad94043c83.png)

## 1E
Setelah itu, client juga dapat menghapus file yang tersimpan di server. Akan tetapi, Keverk takut file yang dibuang adalah file yang penting, maka file hanya akan diganti namanya menjadi ‘old-NamaFile.ekstensi’. Ketika file telah diubah namanya, maka row dari file tersebut di file.tsv akan terhapus.

Contoh Command client :
```
delete TEMPfile.pdf
```

### Pengerjaan
Server
```bash
void deletess() {
    sends("namafile.extension\n");
    bRead();
    bool flag = false;
    char finds[1024]={0};
    strcpy(finds,recieve);
    printf("%s\n",finds);
    FILE* fileR = fopen("files.tsv","r");
    FILE* fileW = fopen("temp.tsv","w");
    char data[1024] = {0};
    char publisher[200], tahun[200],filepath[200],ext[20],filename[200];
    while(fgets(data,1024,fileR)!=NULL){
        sscanf(data,"%[^\t]\t%s\t%s\t%s\t%s",filename,publisher,tahun,ext,filepath);
        if (strcmp(filename,finds)!=0) {
        fprintf(fileW,"%s",data);
        } 
        if (strcmp(filename,finds)==0){
            flag = true;
        }
        bzero(data,1024);
    }
    fclose(fileW);
    fclose(fileR);
    if (flag == true) {
    remove("files.tsv");
    rename("temp.tsv","files.tsv");
    FILE* log = fopen("running.log","a");
    fprintf(log,"Hapus: %s %s",finds,upass);
    fclose(log);
    char oldFile[200]= {0};
    char renamed[200]={0};
    char temp[104]="/home/bayu/Documents/Prak3/files/";
    strcat(oldFile,temp);
    strcat(renamed,temp);
    strcat(oldFile,finds);
    strcat(renamed,"old-");
    strcat(renamed,finds);
//    printf("d");
    rename(oldFile,renamed);
    sends("Delete sukses\n");
    }
    else {
        sends("File tidak ditemukan");
    }
}
```
Client
```bash
void delete() {
    resR();
    char temp[1024];
    scanf("%s",temp);
    temp[strcspn(temp,"\n")]=0;
    sends(temp);
    resR();
}
```

### Penjelasan
Client mengirim nama file dan extensi lalu dengan cara diatas lalu server akan mengiterasi ke semua data yang ada di tsv. sscanf disini berfungsi untuk memparse tsv menjadi 5 varible berbeda. jika ada name yang **TIDAK** sama dengan yang ingin didelete akan dicopy ke tsv baru yang dinamakan temp. jika ditemukan file tersebut, tidak copy dan membuat flag menjadi true. 
Metode ini dilakukan karena tidak ada cara mudah untuk mendelete suatu line di tsv dengan mudah. Setelah selesai akan di close kedua file tersebut.
```bash
FILE* fileR = fopen("files.tsv","r");
    FILE* fileW = fopen("temp.tsv","w");
    char data[1024] = {0};
    char publisher[200], tahun[200],filepath[200],ext[20],filename[200];
    while(fgets(data,1024,fileR)!=NULL){
        sscanf(data,"%[^\t]\t%s\t%s\t%s\t%s",filename,publisher,tahun,ext,filepath);
        if (strcmp(filename,finds)!=0) {
        fprintf(fileW,"%s",data);
        } 
        if (strcmp(filename,finds)==0){
            flag = true;
        }
        bzero(data,1024);
    }
    fclose(fileW);
    fclose(fileR);
```
Lalu jika file ditemukan kita mendelete files.tsv yang lama dengan function remove dan rename temp menjadi files dengan function rename. Dengan cara sama seperti sebelumnya kita juga akan merename file yang didelete menjadi old-filename

```bash
if (flag == true) {
    remove("files.tsv");
    rename("temp.tsv","files.tsv");
    FILE* log = fopen("running.log","a");
    fprintf(log,"Hapus: %s %s",finds,upass);
    fclose(log);
    char oldFile[200]= {0};
    char renamed[200]={0};
    char temp[104]="/home/bayu/Documents/Prak3/files/";
    strcat(oldFile,temp);
    strcat(renamed,temp);
    strcat(oldFile,finds);
    strcat(renamed,"old-");
    strcat(renamed,finds);
//    printf("d");
    rename(oldFile,renamed);
    sends("Delete sukses\n");
    }
    else {
        sends("File tidak ditemukan");
    }
}
```
### Output
![image](https://user-images.githubusercontent.com/31591861/119265395-bcebca00-bc10-11eb-9c4c-a4e05de347e5.png)
![image](https://user-images.githubusercontent.com/31591861/119265399-c5440500-bc10-11eb-833b-8d891a78d5db.png)
![image](https://user-images.githubusercontent.com/31591861/119265408-cffe9a00-bc10-11eb-8ff8-bd3319a48aa9.png)

## 1F
Client dapat melihat semua isi <b>files.tsv</b> dengan memanggil suatu perintah yang bernama see. Output dari perintah tersebut keluar dengan format. 

Contoh Command Client :
```
see
```

Contoh Format Output pada Client :
```
Nama:
Publisher:
Tahun publishing:
Ekstensi File : 
Filepath : 

Nama:
Publisher:
Tahun publishing:
Ekstensi File : 
Filepath : 
```

### Pengerjaan
Client
```bash
void see(){
    char bigbuff[10000];
    read (soc,bigbuff,10000);
    printf("%s\n",bigbuff);
    memset(bigbuff,0,sizeof(bigbuff));
    
}
```
Server
```bash
 FILE* fileR = fopen("files.tsv","r");
    char data[1024] = {0};
    char tosend[10000]={0};
    char publisher[200], tahun[200],filepath[200],ext[20],filename[200];
    while(fgets(data,1024,fileR)!=NULL){
        sscanf(data,"%[^\t]\t%s\t%s\t%s\t%s",filename,publisher,tahun,ext,filepath);
        char tosendbuff [1024];
        sprintf(tosendbuff,"Nama: %s\nPublisher: %s\nTahun Publishing: %s\nExtensi File: %s\nFilepath: %s\n\n",filename,publisher,tahun,ext,filepath);
        strcat(tosend,tosendbuff);
        bzero(data,1024);
    }
    fclose(fileR);
    sends(tosend);
}
```
### Penjelasan
Client hanya menyiapkan sebuah buffer besar untuk print, setelah dikirim command see, server akan membaca setiap line dari files.tsv dengan cara 1e dan mengappend tersebut ke sebuah buffer besar untuk dikirim.
### Output
![image](https://user-images.githubusercontent.com/31591861/119265489-2e2b7d00-bc11-11eb-8db6-1035174f5bff.png)

## 1G
Aplikasi client juga dapat melakukan pencarian dengan memberikan suatu string. Hasilnya adalah semua nama file yang mengandung string tersebut. Format output seperti format output f.

Contoh Client Command :
```
find TEMP
```

### Pengerjaan
Server
```bash
void find(){
    bRead();
    FILE* fileR = fopen("files.tsv","r");
    char find[200];
    bool flag = false;
    char data[1024] = {0};
    char tosend[10000]={0};
    char publisher[200], tahun[200],filepath[200],ext[20],filename[200];
    strcpy(find,recieve);
    while(fgets(data,1024,fileR)!=NULL){
           sscanf(data,"%[^\t]\t%s\t%s\t%s\t%s",filename,publisher,tahun,ext,filepath);
           char tosendbuff [1024];
           sprintf(tosendbuff,"Nama: %s\nPublisher: %s\nTahun Publishing: %s\nExtensi File: %s\nFilepath: %s\n\n",filename,publisher,     tahun,ext,filepath);
           char * beep;
           beep = strstr(filename,find);
           if(beep!=NULL){
               flag=true;
            strcat(tosend,tosendbuff);   
           }
           bzero(data,1024);
       }
       fclose(fileR);
       if (!flag){
           sends("Tidak ditemukan");
       }
       else {
           sends(tosend);
       }

}
```
Client
```bash
void find(){
   printf("Tulis nama file anda\n");
    char find[200] = {0};
    scanf("%s",find);
    find[strcspn(find,"\n")]=0;
    sends(find);
    resR();
}
```
### Penjelasan
Client mengirim sebuah string yang ingin dicari. seperti metode see diatas server akan mengloop untuk semua line di tsv dan dengan menggunakan function strstr dapat mencari sebuah substring di dalam string. Jika pointer tersebut tidak null akan di tambahkan ke buffer seperti command see lalu akan dikirimkan ke client
```bash
char * beep;
           beep = strstr(filename,find);
           if(beep!=NULL){
               flag=true;
            strcat(tosend,tosendbuff);   
           }
```
### Output
![image](https://user-images.githubusercontent.com/31591861/119265681-c0cc1c00-bc11-11eb-93ef-0163eabfb1da.png)

## 1H
Dikarenakan Keverk waspada dengan pertambahan dan penghapusan file di server, maka Keverk membuat suatu log untuk server yang bernama <b>running.log</b>. Contoh isi dari log ini adalah

<b>running.log</b>
```
Tambah : File1.ektensi (id:pass)
Hapus : File2.ektensi (id:pass)
```

### Pengerjaan
delete
```bash
void deletess() {
    sends("namafile.extension\n");
    bRead();
    bool flag = false;
    char finds[1024]={0};
    strcpy(finds,recieve);
    printf("%s\n",finds);
    FILE* fileR = fopen("files.tsv","r");
    FILE* fileW = fopen("temp.tsv","w");
    char data[1024] = {0};
    char publisher[200], tahun[200],filepath[200],ext[20],filename[200];
    while(fgets(data,1024,fileR)!=NULL){
        sscanf(data,"%[^\t]\t%s\t%s\t%s\t%s",filename,publisher,tahun,ext,filepath);
        if (strcmp(filename,finds)!=0) {
        fprintf(fileW,"%s",data);
        } 
        if (strcmp(filename,finds)==0){
            flag = true;
        }
        bzero(data,1024);
    }
    fclose(fileW);
    fclose(fileR);
    if (flag == true) {
    remove("files.tsv");
    rename("temp.tsv","files.tsv");
    FILE* log = fopen("running.log","a");
    fprintf(log,"Hapus: %s %s",finds,upass);
    fclose(log);
```
add
```bash
void addFiles() { 
    char publisher[1024] = {0};
	char tahun[1024] = {0};
	char path[1024] = {0};
    sends("Publisher:\n");
    bRead();
    strcpy(publisher,recieve);
    sends("Tahun Publish:\n");
    bRead();
    strcpy(tahun,recieve);
    sends("Filepath:\n");
    bRead();
    strcpy(path,recieve);
    char *ptr1;
    char slash ='/';
    ptr1 = strrchr( path, slash );
    ptr1++;
    char fname[100];
    strcpy(fname,ptr1);
    char ext[10];
    char *ptr2;
    char dot ='.';
    ptr2 = strrchr( path, dot );
    ptr2++;
    strcpy(ext,ptr2);
    char dir[300] = "/home/bayu/Documents/Prak3/files/";
    strcat(dir,fname);
    FILE* tsv = fopen("files.tsv","a");
    char info[5000];
    sprintf(info,"%s\t%s\t%s\t%s\t%s\n",fname,publisher,tahun,ext,path);
    fputs(info,tsv);
    fclose(tsv);
    writefile(dir); 
    sends("File berhasil ditambahkan\n");
    FILE* log = fopen("running.log","a");
    fprintf(log,"Tambah: %s %s",fname,upass);
    fclose(log);
}
```
### Penjelasan
Setiap ada function delete dan add di append ke running.log
### Output
![image](https://user-images.githubusercontent.com/31591861/119265755-fd981300-bc11-11eb-932b-2cc5b46d4e90.png)

## Kendala
- Susah download dan upload
- Banyak sub bab
- Tidak tahu kapan pake theading
- ETS

# --- No 2 ---
Crypto (kamu) adalah teman Loba. Suatu pagi, Crypto melihat Loba yang sedang kewalahan mengerjakan tugas dari bosnya. Karena Crypto adalah orang yang sangat menyukai tantangan, dia ingin membantu Loba mengerjakan tugasnya. Detil dari tugas tersebut adalah :

### Note
- Semua matriks berasal dari input ke program. 
- Dilarang menggunakan system()

Detil dari tugas tersebut adalah :

## 2A
Membuat program perkalian matrix (4x3 dengan 3x6) dan menampilkan hasilnya. Matriks nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka).

### Pengerjaan
```bash
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    int matriks1[21][21], matriks2[21][21], hasil[21][21];
    int i, j, k, m, n, p, q, jumlah = 0;

    key_t key = 1234;
    int *Temp;
    int shmid = shmget(key, sizeof(int)*24, IPC_CREAT | 0666);
    Temp = shmat(shmid, NULL, 0);

    if(shmid  == -1){
        printf("error\n");
        return 0;
    }

    printf("Masukkan jumlah baris matriks pertama: ");
    scanf("%d",&m);

    printf("Masukkan jumlah kolom matriks pertama: ");
    scanf("%d",&n);

    printf("Masukkan jumlah baris matriks kedua: ");
    scanf("%d",&p);

    printf("Masukkan jumlah kolom matriks kedua: ");
    scanf("%d",&q);

    if(n != p)
    {
        printf("Matriks tidak dapat dikalikan satu sama lain.\n");
    } 
    
    else {
        printf("Masukkan elemen matriks pertama: \n");
        for(i = 0; i < m; i++)
        {
            for(j = 0; j < n; j++)
            {
                scanf("%d", &matriks1[i][j]);
            }
        }

        printf("Masukkan elemen matriks kedua: \n");
        for(i = 0; i < p; i++)
        {
            for(j = 0; j < q; j++)
            {
                scanf("%d", &matriks2[i][j]);
            }
        }

        for(i = 0; i < m; i++)
        {
            for(j = 0; j < q; j++)
            {
                for(k = 0; k < p; k++)
                {
                    jumlah = jumlah + matriks1[i][k] * matriks2[k][j];
                }
                hasil[i][j] = jumlah;
                jumlah = 0;
            }
        }

        printf("Hasil perkalian matriks: \n");
        for(i = 0; i < m; i++)
        {
            for(j = 0; j < q; j++)
            {
                printf("%d\t", hasil[i][j]);
                Temp[i*6+j] = hasil[i][j];
            }
            printf("\n");
        }
        shmdt(Temp);
        //shmctl(shmid, IPC_RMID, NULL);
    }    
    return 0;
}
```

### Penjelasan
```bash
 int matriks1[21][21], matriks2[21][21], hasil[21][21];
 int i, j, k, m, n, p, q, jumlah = 0;
 
 printf("Masukkan jumlah baris matriks pertama: ");
 scanf("%d",&m);

 printf("Masukkan jumlah kolom matriks pertama: ");
 scanf("%d",&n);

 printf("Masukkan jumlah baris matriks kedua: ");
 scanf("%d",&p);

 printf("Masukkan jumlah kolom matriks kedua: ");
 scanf("%d",&q);
```
Pada bagian ini, dilakukan pendeklarasian berbagai macam variabel yang akan digunakan nantinya, Disini terdapat pendeklarasian untuk matriks - matriks yang akan digunakan yaitu matriks1 dimana sesuai soal memiliki atribut berupa baris sebanyak 4 dan kolom sebanyak 3. Kemudian terdapat matriks2 dimana sesuai soal memiliki atribut berupa baris sebanyak 3 dan kolom sebanyak 6. Masing - masing baris dan kolom untuk setiap matriks akan diinputkan sendiri oleh user.

```bash
 if(n != p)
    {
        printf("Matriks tidak dapat dikalikan satu sama lain.\n");
    } 
```
Bagian ini hanya berfungsi sebagai exception, dimana sesuai aturan perkalian matriks jika jumlah kolom dari matriks1 tidak sama dengan jumlah baris dari matriks2 maka perkalian matriks tidak dapat dilakukan.

```bash
printf("Masukkan elemen matriks pertama: \n");
for(i = 0; i < m; i++)
{
  for(j = 0; j < n; j++)
  {
    scanf("%d", &matriks1[i][j]);
  }
}
```
Pada bagian ini user akan melakukan penginputan elemen - elemen angka yang akan menyusun matriks1

```bash
 printf("Masukkan elemen matriks kedua: \n");
for(i = 0; i < p; i++)
{
    for(j = 0; j < q; j++)
    {
      scanf("%d", &matriks2[i][j]);
    }
}
```
Pada bagian ini user akan melakukan penginputan elemen - elemen angka yang akan menyusun matriks2

```bash
for(i = 0; i < m; i++)
{
  for(j = 0; j < q; j++)
  {
      for(k = 0; k < p; k++)
      {
         jumlah = jumlah + matriks1[i][k] * matriks2[k][j];
      }
      hasil[i][j] = jumlah;
      jumlah = 0;
   }
}
```
Pada bagian ini dilakukan operasi perkalian antara matriks1 dan matriks2, dimana hasil dari perkalian akan disimpan ke dalam variable jumlah. Setelah disimpan di dalam variable jumlah, hasil perkalian akan dipassing lagi ke variable ```hasil``` dan variable ```jumlah``` nilainya di set kembali menjadi 0 untuk menyimpan hasil perkalian berikutnya.

```bash
printf("Hasil perkalian matriks: \n");
for(i = 0; i < m; i++)
{
   for(j = 0; j < q; j++)
   {
     printf("%d\t", hasil[i][j]);
     Temp[i*6+j] = hasil[i][j];
   }
   printf("\n");
}
shmdt(Temp);
//shmctl(shmid, IPC_RMID, NULL);
```
Pada bagian ini, hasil perkalian matriks yang tadi disimpan ke dalam variable hasil akan dipindahkan lagi ke dalam variable ```Temp```, dimana bentuk ```i*6+j``` adalah untuk mengubah bentuk array matriks dari 2 dimensi menjadi 1 dimensi. Variable ```Temp``` ini lah yang akan digunakan untuk melakukan ```shared memory``` dengan soal 2b karena hasil perkalian matriks dari soal 2a akan digunakan kembali di soal 2b.

### Output
![Output no 2A](https://user-images.githubusercontent.com/72689610/119260599-bd2e9a00-bbfd-11eb-8735-6c6e62a51182.png)

## 2B
Membuat program dengan menggunakan matriks output dari program sebelumnya (program soal2a.c) (<b>Catatan!</b> : gunakan shared memory). Kemudian matriks tersebut akan dilakukan perhitungan dengan matrix baru (input user) sebagai berikut contoh perhitungan untuk matriks yang ada. Perhitungannya adalah setiap cel yang berasal dari matriks A menjadi angka untuk faktorial, lalu cel dari matriks B menjadi batas maksimal faktorialnya matri(dari paling besar ke paling kecil) (<b>Catatan!</b> : gunakan thread untuk perhitungan di setiap cel).

<b>Ketentuan</b>
```
If a >= b  -> a!/(a-b)!
If b > a -> a!
If 0 -> 0
```
Contoh :
A  | B | Angka - Angka Faktorial
---------|-------|---------------
4 | 4 | 4 3 2 1
4 | 5 | 4 3 2 1
4 | 3 | 4 3 2
4 | 0 | 0
0 | 4 | 0
4 | 6 | 4 3 2 1

Contoh :
![Untitled](https://user-images.githubusercontent.com/72689610/119249774-8046b100-bbc5-11eb-9832-5348131ba618.png)

### Pengerjaan
```bash
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int banyak_data=24;
int input_data_2b[24];
int *Temp;

long long jumlah(long long n, int sn) 
{
    long long hasil = 1;
    for(long long a=0; a < sn; a++){
        if(n - a <= 0)
        {
            hasil *= 1;
        }

        else
        {
            hasil *= (n-a);
        }
    }
    return hasil;
}

typedef struct factorial
{
    int angka_matriks_2a;
    int angka_matriks_2b;
}factorial;

void *faktorial(void *data)
{
    factorial *tmp = (factorial *)data;
    // printf("\nangka: %d %d\n", tmp -> angka_matriks_2a, tmp -> angka_matriks_2b;); 
    if(tmp -> angka_matriks_2a == 0 || tmp -> angka_matriks_2b == 0)
    {    
        printf("0\t");
    }

    else
    {
        printf("%lld\t", jumlah(tmp -> angka_matriks_2a, tmp -> angka_matriks_2b));
    }
}

void main()
{
    pthread_t thread;
    key_t key = 1234;
    int shmid = shmget(key, sizeof(int)*24, IPC_CREAT | 0666);
    Temp = shmat(shmid, NULL, 0);
    
    // for(int i=0;i<24;i++)
    // {
    //     printf("%d", Temp[i]);
    // }

    for(int i=0;i<24;i++)
    {
        printf("Masukkan data input[%d]:", i+1);
        scanf("%d", &input_data_2b[i]);
    }

    for(int a = 0; a < banyak_data; a++){
        if(a % 6 == 0){
            printf("\n");
        }
        factorial *tes = (factorial*)malloc(sizeof(*tes)); 
        tes->angka_matriks_2a = Temp[a];
        tes->angka_matriks_2b = input_data_2b[a];
        // tes->index = i;
        pthread_create(&thread, NULL, faktorial, (void *)tes ); 
        pthread_join(thread,NULL); 
    }
    printf("\n");

    // for(int a=0;a<banyak_data;a++)
    // {
    //     for(i = 0; i < baris; i++)
    //     {
    //         for(j = 0; j < kolom; j++)
    //         {
    //             Tempat = arr[i][j];
    //             loop = input_data_2b[a];
    //             a++;
    //             factorial *tes = (factorial*)malloc(sizeof(*tes));
    //             tes->angka_matriks_2a = Tempat;
    //             tes->angka_matriks_2b; = loop;
    //             // tes->index = i;
    //             pthread_create(&thread, NULL, faktorial, (void *)tes ); 
    //             pthread_join(thread,NULL); 
    //         }
    //         printf("\n");
    //     }    
    // }
    shmdt(Temp);
    shmctl(shmid, IPC_RMID, NULL);
}
```

### Penjelasan
```bash
int banyak_data=24;
int input_data_2b[24];
int *Temp;
```
Pada bagian ini dilakukan pendeklarasian beberapa variable, yang pertama adalah ``` banyak_data``` yang di set sebanyak 24 karena hasil perkalian matriks di soal 2a bentuk matriksnya adalah 4*6 yang berarti terdapat 24 elemen. Variable yang kedua adalah ```input_data_2b``` dengan array sebanyak 24 untuk menyamakan jumlah elemennya dengan jumlah elemen dari hasil perkalian matriks pada soal 2a. Variable yang ketiga adalah ```Temp``` yang berbentuk pointer yang akan digunakan untuk melakukan shared memory (pemanggilan hasil perkalian matriks) dengan soal 2a.

```bash
typedef struct factorial
{
    int angka_matriks_2a;
    int angka_matriks_2b;
}factorial;
```
Untuk soal ini, saya menggunakan struct dimana pada bagian ini saya melakukan pendeklarasian variable ```angka_matriks_2a``` untuk menyimpan nilai hasil perkalian matriks dari soal 2a dan variable ```angka_matriks_2b``` untuk menyimpan hasil inputan angka dari user pada soal 2b.

```bash
void *faktorial(void *data)
{
    factorial *tmp = (factorial *)data;
    // printf("\nangka: %d %d\n", tmp -> angka_matriks_2a, tmp -> angka_matriks_2b;); 
    if(tmp -> angka_matriks_2a == 0 || tmp -> angka_matriks_2b == 0)
    {    
        printf("0\t");
    }

    else
    {
        printf("%lld\t", jumlah(tmp -> angka_matriks_2a, tmp -> angka_matriks_2b));
    }
}
```
Pada bagian ini digunakan percabangan untuk melakukan pendeklarasian syarat perhitungan agar sesuai dengan hasil yang diminta oleh soal. Pertama diketahui bahwa jika salah satu angka baik pada hasil perkalian matriks pada soal2a maupun pada inputan user di soal2b nilainya adalah 0, maka program akan langsung mencetak hasilnya adalah 0. Jika kondisi sebelumnya tidak terpenuhi, maka program akan menjalankan fungsi ```jumlah``` dengan parameternya adalah ```angka_matriks_2a``` (hasil perkalian matriks pada soal2a) dan ```angka_matriks_2b``` (inputan user pada soal 2b).

```bash
long long jumlah(long long n, int sn) 
{
    long long hasil = 1;
    for(long long a=0; a < sn; a++){
        if(n - a <= 0)
        {
            hasil *= 1;
        }

        else
        {
            hasil *= (n-a);
        }
    }
    return hasil;
}
```
Fungsi jumlah berfungsi untuk melakukan operasi faktorial sesuai dengan limit tertentu, dimana hasil dari operasi faktorial akan disimpan di dalam variable ```hasil```. Percabangan yang pertama berfungsi untuk kondisi ketika nilai elemen indeks tertentu pada hasil perkalian matriks dari soal2a lebih kecil daripada nilai inputan user pada soal2b. Jika kondisi di atas tidak terpenuhi, maka program akan menjalankan operasi matriks seperti biasa.

Berikut adalah fungsi source code di dalam fungsi main.
```bash
for(int i=0;i<24;i++)
{
  printf("Masukkan data input[%d]:", i+1);
  scanf("%d", &input_data_2b[i]);
}
```
Pada bagian ini, user akan menginputkan angka-angka sebanyak 24 elemen yang akan dioperasikan dengan masing - masing elemen dari hasil perkalian matriks pada soal 2a.

```bash
for(int a = 0; a < banyak_data; a++)
{
  if(a % 6 == 0){
    printf("\n");
  }
  factorial *tes = (factorial*)malloc(sizeof(*tes)); 
  tes->angka_matriks_2a = Temp[a];
  tes->angka_matriks_2b = input_data_2b[a];
  // tes->index = i;
  pthread_create(&thread, NULL, faktorial, (void *)tes ); 
        pthread_join(thread,NULL); 
}
```
Pada bagian ini, setiap program mencetak hasil pada kolom 6 maka program akan melakukan enter terlebih dahulu sebelum melanjutkan pencetakan hasil berikutnya. Kemudian juga dilakukan pemanggilan hasil perkalian matriks pada soal2a melalui variable ```Temp``` yang kemudian akan dimasukkan ke dalam variable ```angka_matriks_2a```. Selain itu semua inputan user pada soal2b akan dimasukkan ke dalam variable ```angka_matriks_2b```. Pada bagian ini juga dilakukan pendeklarasian untuk melakukan thread pada setiap perhitungannya.

### Output
![Output no 2B](https://user-images.githubusercontent.com/72689610/119260698-1d254080-bbfe-11eb-813b-dfecd393b438.png)

## 2C
Karena takut lag dalam pengerjaannya membantu Loba, Crypto juga membuat program (soal2c.c) untuk mengecek 5 proses teratas apa saja yang memakan resource komputernya dengan command “ps aux | sort -nrk 3,3 | head -5” (<b>Catatan!</b> : Harus menggunakan IPC Pipes)

### Pengerjaan
```bash
// This program is an example of how to run a command such as
// ps aux | grep root | grep sbin
// using C and Unix.

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int pid;
int pipe1[2];
int pipe2[2];

int main(int argc, char const *argv[]) 
{
    // create pipe1
    if (pipe(pipe1) == -1) 
    {
        perror("bad pipe1");
        exit(1);
    }

  // fork (ps aux)
    if ((pid = fork()) == -1) 
    {
        perror("bad fork1");
        exit(1);
    } 
    
    else if (pid == 0) 
    {
        // stdin --> ps --> pipe1
        // input from stdin (already done)
        // output to pipe1
        dup2(pipe1[1], 1);
        // close fds
        close(pipe1[0]);
        close(pipe1[1]);
        // exec
        char *argv[] = {"ps", "aux", NULL};
        execv("/bin/ps", argv);
        // exec didn't work, exit
        perror("bad exec ps");
        _exit(1);
    }
    // parent

    // create pipe2
    if (pipe(pipe2) == -1) 
    {
        perror("bad pipe2");
        exit(1);
    }

    // fork (grep root)
    if ((pid = fork()) == -1) 
    {
        perror("bad fork2");
        exit(1);
    } 

    else if (pid == 0) 
    {
        // pipe1 --> grep --> pipe2
        // input from pipe1
        dup2(pipe1[0], 0);
        // output to pipe2
        dup2(pipe2[1], 1);
        // close fds
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        // exec
        char *argv[] = {"sort", "-nrk", "3.3", NULL};
        execv("/bin/sort", argv);
        // exec didn't work, exit
        perror("bad exec grep root");
        _exit(1);
    }
    // parent

    // close unused fds
    close(pipe1[0]);
    close(pipe1[1]);

    // fork (grep sbin)
    if ((pid = fork()) == -1) 
    {
        perror("bad fork3");
        exit(1);
    } 
    
    else if (pid == 0) 
    {
        // pipe2 --> grep --> stdout
        // input from pipe2
        dup2(pipe2[0], 0);
        // output to stdout (already done)
        // close fds
        close(pipe2[0]);
        close(pipe2[1]);
        // exec
        char *argv[] = {"head", "-5", NULL};
        execv("/bin/head", argv);
        // exec didn't work, exit
        perror("bad exec grep sbin");
        _exit(1);
    }
    // parent
}

```

### Penjelasan
```bash
else if (pid == 0) 
{
   // stdin --> ps --> pipe1
   // input from stdin (already done)
   // output to pipe1
   dup2(pipe1[1], 1);
   // close fds
   close(pipe1[0]);
   close(pipe1[1]);
   // exec
   char *argv[] = {"ps", "aux", NULL};
   execv("/bin/ps", argv);
   // exec didn't work, exit
   perror("bad exec ps");
   _exit(1);
}
```
Pada bagian ini, program akan menunjukkan list semua proses yang sedang berjalan sekaligus dengan status dan penggunaan sumber dayanya.

```bash
else if (pid == 0) 
{
  // pipe1 --> grep --> pipe2
  // input from pipe1
  dup2(pipe1[0], 0);
  // output to pipe2
  dup2(pipe2[1], 1);
  // close fds
  close(pipe1[0]);
  close(pipe1[1]);
  close(pipe2[0]);
  close(pipe2[1]);
  // exec
  char *argv[] = {"sort", "-nrk", "3.3", NULL};
  execv("/bin/sort", argv);
  // exec didn't work, exit
  perror("bad exec grep root");
  _exit(1);
}
```
Pada bagian ini, program akan melakukan sort atau pengurutan penampilan data pada list.

```bash
else if (pid == 0) 
{
    // pipe2 --> grep --> stdout
    // input from pipe2
    dup2(pipe2[0], 0);
    // output to stdout (already done)
    // close fds
    close(pipe2[0]);
    close(pipe2[1]);
    // exec
    char *argv[] = {"head", "-5", NULL};
    execv("/bin/head", argv);
    // exec didn't work, exit
    perror("bad exec grep sbin");
    _exit(1);
}
```
Pada bagian ini, program akan menampilkan 5 data teratas yang memakan resource dengan urutan dari yang terbesar hingga yang terkecil.

### Output
![Output no 2C](https://user-images.githubusercontent.com/72689610/119260731-4940c180-bbfe-11eb-8cf7-4aac78f26bb7.png)

## Kendala
Tidak ada kendala dalam pengerjaan soal ini

# --- No 3 ---
Seorang mahasiswa bernama Alex sedang mengalami masa gabut. Di saat masa gabutnya, ia memikirkan untuk merapikan sejumlah file yang ada di laptopnya. Karena jumlah filenya terlalu banyak, Alex meminta saran ke Ayub. Ayub menyarankan untuk membuat sebuah program C agar file-file dapat dikategorikan. Program ini akan memindahkan file sesuai ekstensinya ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working directory ketika program kategori tersebut dijalankan.

Contoh apabila program dijalankan :
```
# Program soal3 terletak di /home/izone/soal3
$ ./soal3 -f path/to/file1.jpg path/to/file2.c path/to/file3.zip
#Hasilnya adalah sebagai berikut
/home/izone
|-jpg
|--file1.jpg
|-c
|--file2.c
|-zip
|--file3.zip
```
Namun karena Ayub adalah orang yang hanya bisa memberi ide saja, tidak mau bantuin buat bikin programnya, Ayub meminta bantuanmu untuk membuatkan programnya. Bantulah agar program dapat berjalan!

### Note
- Kategori folder tidak dibuat secara manual, harus melalui program C 
- Program ini tidak case sensitive. Contoh: JPG dan jpg adalah sama
- Jika ekstensi lebih dari satu (contoh “.tar.gz”) maka akan masuk ke folder dengan titik terdepan (contoh “tar.gz”)
- Dilarang juga menggunakan fork-exec dan system()
- Bagian b dan c berlaku <b>rekursif</b>

## Fungsi-fungsi yang dibutuhkan

###  pindah
```c
void *pindah(void *arg) {
  char *fullPath = (char *)arg;

  char fileAsli[1000], fileCopy[1000];
  strcpy(fileAsli, fullPath);
  strcpy(fileCopy, fullPath);

  //mengambil ekstensi dan nama bersih (nama tanpa path) dari argumen yang diberikan (full path)
  char *ekst = ambilEkst(fullPath);
  char *cleanName = ambilNama(fileCopy);

  char folderName[120];

  // mengecek indeks ke-0 dari array untuk karakter titik
  if (cleanName[0] == '.') {
    sprintf(folderName, "Hidden");
    //jika iya, maka file akan dimasukkan ke folder Hidden
  } else if (ekst == NULL) {
    sprintf(folderName, "Unknown");
    //jika ekstensinya null, akan dimasukkan folder unknown
  } else {
    // mengubah setiap karakter menjadi lowercase
    for (int i = 0; ekst[i]; i++) {
      ekst[i] = tolower(ekst[i]);
      //mengubah ekstensi menjadi lowercase (untuk dimasukkan folder)
    }
    sprintf(folderName, "%s", ekst);
  }
  mkdir(folderName, 0777);
  //membuat folder, dengan permission 777 agar full permission
  //ditambahkan 0 agar c menginterpretasikannya sebagai oktal dan bukan desimal

  char destDir[200];
  sprintf(destDir, "%s/%s/%s", curDir, folderName, ambilNama(fileAsli));
  //racik string destdir untuk diberikan ke helper

  pindahHelper(fileAsli, destDir);
  //panggil fungsi helper untuk memindahkan file
  return NULL;
}
```

### kategRekur (kategorikan secara rekursif)
```c
void kategRekur(char *basePath) {
  char path[1000], srcPathForThread[1000];
  struct dirent **namelist;
  int n;
  int i = 0;
  int error = 0;
  n = scandir(basePath, &namelist, NULL, alphasort);
  //menghitung dan me-list berapa banyak file di dalam direktori
  if (n < 0)
    return;
  else {
    while (i < n) {
      //loop while selama jumlah file yang diproses (i) kurang dari n
      if (strcmp(namelist[i]->d_name, ".") != 0 && strcmp(namelist[i]->d_name, "..") != 0) {
        //mengecek apakah 'file' yang akan diproses itu . atau .., jika ya, tidak diproses
        strcpy(path, basePath);
        strcat(path, "/");
        strcat(path, namelist[i]->d_name);
        //sambungkan (concatenate) basePath dengan / dan file name agar menjadi variabel path

        if (namelist[i]->d_type != DT_DIR) {
          int err;
          err = pthread_create(&(tid[threadCount - 2]), NULL, &pindah, (void *)path);
          //buat thread baru yang akan memanggil fungsi pindah dengan argumen path

          if (err != 0)
            error++;
            //jika ada error, increment error
          else
            threadCount++;
            //jika tidak, increment threadCount

          for (int p = 0; p < (threadCount - 1); p++)
            pthread_join(tid[p], NULL);
            //menunggu thread selesai
        }

        kategRekur(path);
      }
      free(namelist[i]);
      //free namelist agar tidak ada memory leak
      ++i;
      //increment i untuk menghentikan while
    }
    free(namelist);
  }
  if (error != 0)
    printf("Yah, gagal disimpan :(\n");
  else
    printf("Direktori sukses disimpan!\n");
  //jika error bukan 0, maka output gagal, jika tidak, output sukses
}
```

### pindahHelper
```c
void pindahHelper(char source[], char dest[]) {
  int ch;
  FILE *fp1, *fp2;

  fp1 = fopen(source, "r");
  fp2 = fopen(dest, "w");
  //membuka file source dan destination

  if (!fp1) {
    printf("Unable to open source file to read!!\n");
    fclose(fp2);
    return;
  }
  //print error jika tidak bisa dibuka

  if (!fp2) {
    printf("Unable to open target file to write\n");
    return;
  }

  while ((ch = fgetc(fp1)) != EOF) {
    fputc(ch, fp2);
  }
  //pindahkan file dengan fputc

  fclose(fp1);
  fclose(fp2);
  //tutup file agar process tidak kehabisa file descriptor/ handle

  remove(source);
  //hapus file source
  return;
}
```

### ambilNama
```c
char *ambilNama(char str[]) {
  char *nama;
  char *result;
  nama = strchr(str, '/');
  // cari kemunculan pertama /
  if (nama == NULL) return str;
  while (nama != NULL) {
    // lakukan while loop sampai didapatkan nama file
    result = nama + 1;
    // tambahkan 1 untuk menghapus slash
    nama = strchr(nama + 1, '/');
    // cari lagi slash
  }
  // while loop ini akan berulang sampai tidak ada lagi slash
  return result;
}
```

### ambilEkst
```c
char *ambilEkst(char str[]) {
  char *nama = ambilNama(str);
  char *result = strchr(nama, '.');
  // cari kemunculan pertama .
  if (result == NULL) {
    return NULL;
  } else {
    return (result + 1);
    // tambahkan 1 untuk menghilangkan titik
  }
}
```

## 3A
Program menerima opsi -f seperti contoh di atas, jadi pengguna bisa menambahkan argumen file yang bisa dikategorikan sebanyak yang diinginkan oleh pengguna.

Output yang dikeluarkan adalah seperti ini :
```
File 1 : Berhasil Dikategorikan (jika berhasil)
File 2 : Sad, gagal :( (jika gagal)
File 3 : Berhasil Dikategorikan
```

### Penjelasan
```c
int main(int argc, char **argv) {
  char buf[1000];
  curDir = getcwd(buf, 1000);
  //ambil current directory menggunakan cwd

  int i = 2, p;
  int err;

  if (strcmp(argv[1], "-f") == 0) {
    //cek tiap argumen setelah parameter, jika -f, maka if ini akan dijalankan
    while (argv[i] != NULL) {
      //jalankan while selama argumen setelah -f belum habis
      err = pthread_create(&(tid[i - 2]), NULL, &pindah, (void *)argv[i]);
      //buat thread baru yang memanggil fungsi pindah dengan argumen argv
      if (err != 0)
        printf("File %d: Sad, gagal :(\n", i - 1);
      else
        printf("File %d : Berhasil Dikategorikan\n", i - 1);
      //jika error != 0, maka print gagal, jika tidak, print berhasil
      i++;
      //increment i untuk argumen selanjutnya
    }
    for (p = 0; p < (i - 1); p++) pthread_join(tid[p], NULL);
    //tunggu tiap thread selesai
```

### Output (before dan after)
![image](https://user-images.githubusercontent.com/11045113/119229558-cd357380-bb42-11eb-8f99-acafff1d209d.png)
![image](https://user-images.githubusercontent.com/11045113/119229587-eccc9c00-bb42-11eb-8065-43bfdcbc3207.png)

## 3B
Program juga dapat menerima opsi -d untuk melakukan pengkategorian pada suatu directory. Namun pada opsi -d ini, user hanya bisa memasukkan input 1 directory saja, tidak seperti file yang bebas menginput file sebanyak mungkin.

Contohnya adalah seperti ini :
```
$ ./soal3 -d /path/to/directory/
```

Perintah di atas akan mengkategorikan file di /path/to/directory, lalu hasilnya akan disimpan di working directory dimana program C tersebut berjalan (hasil kategori filenya bukan di /path/to/directory).

Output yang dikeluarkan adalah seperti ini :
```
Jika berhasil, print “Direktori sukses disimpan!”
Jika gagal, print “Yah, gagal disimpan :(“
```

### Penjelasan
```c
  }else if (strcmp(argv[1], "-d") == 0) {
    kategRekur(argv[2]);
    //jika argumen pertama -d, panggil fungsi kategRekur dengan argumen argv[1]
```

### Output (before dan after)
![image](https://user-images.githubusercontent.com/11045113/119229606-066de380-bb43-11eb-9a1c-c022c7582f2c.png)
![image](https://user-images.githubusercontent.com/11045113/119229638-27cecf80-bb43-11eb-8130-8ea450893c34.png)

## 3C
Selain menerima opsi-opsi di atas, program ini menerima opsi *, contohnya ada di bawah ini :
```
$ ./soal3 \*
```
Opsi ini akan mengkategorikan seluruh file yang ada di working directory ketika menjalankan program C tersebut.

### Penjelasan
```c
  } else if (strcmp(argv[1], "*") == 0) {
    kategRekur(".");
    //jika argumen pertama *, maka panggil fungsi kategRekur dengan argumen . (current directory)
  }
```

### Output
![image](https://user-images.githubusercontent.com/11045113/119229694-5fd61280-bb43-11eb-9076-3a14dd841435.png)
![image](https://user-images.githubusercontent.com/11045113/119229730-85fbb280-bb43-11eb-87a8-c8aa5f48cc43.png)

## 3D
Semua file harus berada di dalam folder, jika terdapat file yang tidak memiliki ekstensi, file disimpan dalam folder “Unknown”. Jika file hidden, masuk folder “Hidden”.

### Sudah dijelaskan di fungsi pindah

## 3E
Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat.

### Sudah dijelaskan di fungsi kategRekur dan nomor 3a

## Kendala
- Kurangnya waktu karena sedang minggu ETS
- Masih bingung dengan implementasi threading
