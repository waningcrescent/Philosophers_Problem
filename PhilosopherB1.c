#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<stdbool.h>
#include<pthread.h>

sem_t fork_[5];
sem_t bowl;

void attempt_right_fork(int num){

    printf("Philosopher number %d tries to pick right fork up",num);
    printf("\n");
    sem_wait(&fork_[(num+1)%5]);
    printf("Philosopher number %d picks the right fork up",num);
    printf("\n");


}

void attempt_left_fork(int num){

    printf("Philosopher number %d tries to pick left fork up",num);    
    printf("\n");

    sem_wait(&fork_[num]);
    printf("Philosopher number %d picks the left fork up",num);
    printf("\n");

}

void eating(int num){
    printf("Philosopher number %d is eating right now",num);    
    printf("\n");

}



void * let_go_fork(void * b){

    while (true)
    {
        int PhilosopherNum=*(int *)b;
        int m;

        if(PhilosopherNum==4){

            attempt_right_fork(4);
            attempt_left_fork(4);

        }else{

            attempt_left_fork(PhilosopherNum);
            attempt_right_fork(PhilosopherNum);
        }

        sem_getvalue(&bowl,&m);
        printf("\n");
        printf("Bowl Semaphore is : %d",m);
        printf("\n");

        sem_wait(&bowl);
        printf("Philosopher number %d has taken bowl and will start eating",PhilosopherNum);
        printf("\n");

        eating(PhilosopherNum);
        sleep(2);

        printf("Philosopher number %d is done eating",PhilosopherNum);
        printf("\n");


        sem_post(&bowl);
        printf("Philosopher %d has returned the bowl to table",PhilosopherNum);
        printf("\n");

        sem_getvalue(&bowl,&m);
        printf("\n");
        printf("Bowl Semaphore is : %d",m);
        printf("\n");

        sem_post(&fork_[(PhilosopherNum+1)%5]);
        printf("Philosopher number %d returns left fork to table",PhilosopherNum);
        printf("\n");
        sem_post(&fork_[(PhilosopherNum)]);
        printf("Philosopher number %d returns left fork to table",PhilosopherNum);
        printf("\n");
        

    }
     
}

int main(){

  
    int threadnum[5];
    pthread_t thr[5];

    int x = 0;
    int j = 0;
    while(j<5){
        sem_init(&fork_[j],0,1);
        j++;
    }
    
    sem_init(&bowl,0,2);

    for(int i = 0 ; i<5 ; i++){

        threadnum[i]=i;
        pthread_create(&thr[i],NULL,let_go_fork,(void *)&threadnum[i]);

    }

   while(x<5){
        pthread_join(thr[x],NULL);
        x++;
    }

    return 0;
}
