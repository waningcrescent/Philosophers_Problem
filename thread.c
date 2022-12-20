#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdbool.h>


sem_t fork_[5];


void attempt_right_fork(int num){

    printf("Philosopher number %d tries to pick right fork up\n",num);
    sem_wait(&fork_[(num+1)%5]);
    printf("Philosopher number %d picks the right fork up\n",num);

}

void attempt_left_fork(int num){

    printf("Philosopher number %d tries to pick left fork up\n",num);
    sem_wait(&fork_[num]);
    printf("Philosopher number %d picks the left fork up\n",num);
}


void eating(int num){
    printf("Philosopher number %d is eating right now\n",num);
}

void * let_go_fork(void * b){

    while (true)
    {
        int PhilosopherNum=*(int *)b;

        if(PhilosopherNum==4){

            attempt_right_fork(4);
            attempt_left_fork(4);

        }else{

            attempt_left_fork(PhilosopherNum);
            attempt_right_fork(PhilosopherNum);
        }

        eating(PhilosopherNum);
        sleep(2);
        printf("Philosopher number %d is done eating\n",PhilosopherNum);
        
        sem_post(&fork_[(PhilosopherNum+1)%5]);
        printf("Philosopher number %d returns right fork to table\n",PhilosopherNum);
        sem_post(&fork_[(PhilosopherNum)]);
        printf("Philosopher number %d returns left fork to table\n",PhilosopherNum);

    }
    
    
}




int main(){
    
    int threadnum[5];
    pthread_t thr[5];


    for(int i = 0 ; i<5 ; i++){
        sem_init(&fork_[i],0,1);
    }

    for(int i = 0 ; i<5 ; i++){

        threadnum[i]=i;
        pthread_create(&thr[i],NULL,let_go_fork,(void *)&threadnum[i]);

    }

    for(int i=0;i<5;i++)
        pthread_join(thr[i],NULL);

    return 0;
}
