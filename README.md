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
- [Jawaban Soal 2]()
- [Jawaban Soal 3]()

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

### Penjelasan

### Output

## 1B
Sistem memiliki sebuah database yang bernama <b>files.tsv</b>. Isi dari <b>files.tsv</b> ini adalah <b>path file saat berada di server</b>, <b>publisher</b>, dan <b>tahun publikasi</b>. Setiap penambahan dan penghapusan file pada folder file yang bernama <b>FILES</b> pada server akan memengaruhi isi dari <b>files.tsv</b>. Folder <b>FILES</b> otomatis dibuat saat server dijalankan.

### Pengerjaan

### Penjelasan

### Output

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

### Penjelasan

### Output

## 1D
Dan client dapat mendownload file yang telah ada dalam folder FILES di server, sehingga sistem harus dapat mengirim file ke client. Server harus melihat dari files.tsv untuk melakukan pengecekan apakah file tersebut valid. Jika tidak valid, maka mengirimkan pesan error balik ke client. Jika berhasil, file akan dikirim dan akan diterima ke client di <b>folder client</b> tersebut. 

Contoh Command client :
```
download TEMPfile.pdf
```

### Pengerjaan

### Penjelasan

### Output

## 1E
Setelah itu, client juga dapat menghapus file yang tersimpan di server. Akan tetapi, Keverk takut file yang dibuang adalah file yang penting, maka file hanya akan diganti namanya menjadi ‘old-NamaFile.ekstensi’. Ketika file telah diubah namanya, maka row dari file tersebut di file.tsv akan terhapus.

Contoh Command client :
```
delete TEMPfile.pdf
```

### Pengerjaan

### Penjelasan

### Output

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

### Penjelasan

### Output

## 1G
Aplikasi client juga dapat melakukan pencarian dengan memberikan suatu string. Hasilnya adalah semua nama file yang mengandung string tersebut. Format output seperti format output f.

Contoh Client Command :
```
find TEMP
```

### Pengerjaan

### Penjelasan

### Output

## 1H
Dikarenakan Keverk waspada dengan pertambahan dan penghapusan file di server, maka Keverk membuat suatu log untuk server yang bernama <b>running.log</b>. Contoh isi dari log ini adalah

<b>running.log</b>
```
Tambah : File1.ektensi (id:pass)
Hapus : File2.ektensi (id:pass)
```

### Pengerjaan

### Penjelasan

### Output

## Kendala
- Susah download dan upload
- Banyak sub bab
- Tidak tahu kapan pake theading
- ETS

# --- No 3 ---
Seorang mahasiswa bernama Alex sedang mengalami masa gabut. Di saat masa gabutnya, ia memikirkan untuk merapikan sejumlah file yang ada di laptopnya. Karena jumlah filenya terlalu banyak, Alex meminta saran ke Ayub. Ayub menyarankan untuk membuat sebuah program C agar file-file dapat dikategorikan. Program ini akan memindahkan file sesuai ekstensinya ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working directory ketika program kategori tersebut dijalankan.

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

## 3a
Program menerima opsi -f seperti contoh di atas, jadi pengguna bisa menambahkan argumen file yang bisa dikategorikan sebanyak yang diinginkan oleh pengguna.

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

## 3b
Program juga dapat menerima opsi -d untuk melakukan pengkategorian pada suatu directory. Namun pada opsi -d ini, user hanya bisa memasukkan input 1 directory saja, tidak seperti file yang bebas menginput file sebanyak mungkin.

### Penjelasan
```c
  }else if (strcmp(argv[1], "-d") == 0) {
    kategRekur(argv[2]);
    //jika argumen pertama -d, panggil fungsi kategRekur dengan argumen argv[1]
```

### Output (before dan after)
![image](https://user-images.githubusercontent.com/11045113/119229606-066de380-bb43-11eb-9a1c-c022c7582f2c.png)
![image](https://user-images.githubusercontent.com/11045113/119229638-27cecf80-bb43-11eb-8130-8ea450893c34.png)

## 3c
Selain menerima opsi-opsi di atas, program ini menerima opsi *

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

## 3d
Semua file harus berada di dalam folder, jika terdapat file yang tidak memiliki ekstensi, file disimpan dalam folder “Unknown”. Jika file hidden, masuk folder “Hidden”.

### Sudah dijelaskan di fungsi pindah

## 3e
Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat.

### Sudah dijelaskan di fungsi kategRekur dan nomor 3a

## Kendala
- Kurangnya waktu karena sedang minggu ETS
- Masih bingung dengan implementasi threading
