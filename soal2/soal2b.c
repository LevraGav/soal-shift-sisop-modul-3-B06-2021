#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int banyak_data=24;
int input_data_2b[24];
int *Temp;

long long jumlah(int n, int sn) 
{
    long long hasil = 1;
    for(int a=0; a < sn; a++){
        hasil *= (n-a);
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