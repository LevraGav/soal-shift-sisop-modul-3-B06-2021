#include <ctype.h>
#include <dirent.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

pthread_t tid[100000];
char *curDir;
int threadCount = 2;

void pindahHelper(char source[], char dest[]);
char *ambilNama(char str[]);
void kategRekur(char *basePath);
char *ambilEkst(char str[]);

void *pindah(void *arg) {
  char *fullPath = (char *)arg;

  char fileAsli[1000], fileCopy[1000];
  strcpy(fileAsli, fullPath);
  strcpy(fileCopy, fullPath);

  char *ekst = ambilEkst(fullPath);
  char *cleanName = ambilNama(fileCopy);

  char folderName[120];

  // mengecek indeks ke-0 dari array untuk karakter titik
  if (cleanName[0] == '.') {
    sprintf(folderName, "Hidden");
  } else if (ekst == NULL) {
    sprintf(folderName, "Unknown");
  } else {
    // mengubah setiap karakter menjadi lowercase
    for (int i = 0; ekst[i]; i++) {
      ekst[i] = tolower(ekst[i]);
    }
    sprintf(folderName, "%s", ekst);
  }
  mkdir(folderName, 0777);

  char destDir[200];
  sprintf(destDir, "%s/%s/%s", curDir, folderName,
          ambilNama(fileAsli));

  pindahHelper(fileAsli, destDir);
  return NULL;
}

int main(int argc, char **argv) {
  char buf[1000];
  curDir = getcwd(buf, 1000);

  int i = 2, p;
  int err;

  if (strcmp(argv[1], "-f") == 0) {
    // cek tiap argumen setelah parameter
    while (argv[i] != NULL) {
      err = pthread_create(&(tid[i - 2]), NULL, &pindah, (void *)argv[i]);
      if (err != 0)
        printf("File %d: Sad, gagal :(\n", i - 1);
      else
        printf("File %d : Berhasil Dikategorikan\n", i - 1);
      i++;
    }
    for (p = 0; p < (i - 1); p++) pthread_join(tid[p], NULL);
    
  }else if (strcmp(argv[1], "-d") == 0) {
    kategRekur(argv[2]);

  } else if (strcmp(argv[1], "*") == 0) {
    kategRekur(".");
  }

  return 0;
}

void kategRekur(char *basePath) {
  char path[1000], srcPathForThread[1000];
  struct dirent **namelist;
  int n;
  int i = 0;
  int error = 0;
  n = scandir(basePath, &namelist, NULL, alphasort);
  if (n < 0)
    return;
  else {
    while (i < n) {
      if (strcmp(namelist[i]->d_name, ".") != 0 &&
          strcmp(namelist[i]->d_name, "..") != 0) {
        strcpy(path, basePath);
        strcat(path, "/");
        strcat(path, namelist[i]->d_name);

        if (namelist[i]->d_type != DT_DIR) {
          int err;
          err = pthread_create(&(tid[threadCount - 2]), NULL, &pindah, (void *)path);

          if (err != 0)
            error++;
          else
            threadCount++;

          for (int p = 0; p < (threadCount - 1); p++)
            pthread_join(tid[p], NULL);
        }

        kategRekur(path);
      }
      free(namelist[i]);
      ++i;
    }
    free(namelist);
  }
  if (error != 0)
    printf("Yah, gagal disimpan :(\n");
  else
    printf("Direktori sukses disimpan!\n");
}

void pindahHelper(char source[], char dest[]) {
  int ch;
  FILE *fp1, *fp2;

  fp1 = fopen(source, "r");
  fp2 = fopen(dest, "w");

  if (!fp1) {
    printf("Unable to open source file to read!!\n");
    fclose(fp2);
    return;
  }

  if (!fp2) {
    printf("Unable to open target file to write\n");
    return;
  }

  while ((ch = fgetc(fp1)) != EOF) {
    fputc(ch, fp2);
  }

  fclose(fp1);
  fclose(fp2);

  remove(source);
  return;
}

char *ambilNama(char str[]) {
  char *nama;
  char *result;
  // cari kemunculan pertama /
  nama = strchr(str, '/');
  if (nama == NULL) return str;
  // lakukan while loop sampai didapatkan nama file
  while (nama != NULL) {
    result = nama + 1;
    nama = strchr(nama + 1, '/');
  }
  return result;
}

char *ambilEkst(char str[]) {
  char *nama = ambilNama(str);
  // cari kemunculan pertama .
  char *result = strchr(nama, '.');
  if (result == NULL) {
    return NULL;
  } else {
    // tambahkan 1 untuk menghilangkan titik
    return (result + 1);
  }
}
