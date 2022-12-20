#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>


int main(){
    int smem_id;
    key_t key;
    char* smem, scopy;

    key=1234;//ftok(".",'a');
    smem_id=shmget(key,100*sizeof(char), 0666);

    if (smem_id<0){
        exit(1);
    }
    smem= shmat(smem_id,NULL,0);
    if(smem==(char*)-1){
        exit(1);
    }
    scopy=smem;

    for (;scopy<smem+10;scopy++){
        printf("%c",*scopy);
        if(scopy==smem){
            *scopy=*smem+9;
            continue;
        }
        *scopy="*";
    }
    shmdt(smem);
    return 0;
}
