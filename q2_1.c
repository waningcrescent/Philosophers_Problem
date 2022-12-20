#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define buff_max 100
#define mod %

struct item{
    char item[5];
} nextProduced;

char* randomstring()
{
    srand(time(NULL));

    char string[50];
    char *ptr;

    ptr=&string[0];
    for( int i = 0; i < 50; i++){

    int s=rand()%72; // starting on '0', ending on '}'
    string[i]=("%c",s);
    }

    return(ptr);
}

int main(){
    int smem_id;
    key_t key;
    char* smem, scopy, str;
    char* s=randomstring();
    int a=rand()%45;

    key=1234;//ftok(".",'a');
    smem_id=shmget(key,100*sizeof(char),IPC_CREAT | 0666);

    if (smem_id<0){
        exit(1);
    }
    smem= shmat(smem_id,NULL,0);
    if(smem==(char*)-1){
        exit(1);
    }
    scopy=smem;

    /*for (int i=0;i<5;i++){
        *scopy=s[a+i];
        scopy++;
    }
    *scopy=0;
    a=a+4;//}while((a) < 49);*/

    while(smem !="*" && a+4<49){
        str=s+a;
        for (int i=0;i<5;i++){
            *scopy=*str;
            str++;
            scopy++;
            *scopy=(a+i);
            scopy++;
        }
        a=a+4;
        *scopy=0;
    }
    
    shmdt(smem);
    shmctl(smem_id,IPC_RMID,NULL);


    return 0;

}
