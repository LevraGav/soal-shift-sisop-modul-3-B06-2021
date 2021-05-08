#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<ctype.h>
#include<dirent.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char *argv[])
{
    if(strcmp(argv[1], "-f") == 0)
    {
        printf("parameter -f dipilih\n");
    }
}
