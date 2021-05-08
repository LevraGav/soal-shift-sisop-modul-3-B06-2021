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