#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<stdbool.h>
#include<stdlib.h>


sem_t BOWL;
sem_t fork_[5];


int main(){
  
    int threadnum[5];
    pthread_t thr[5];
    
    int j = 0;
    while(j<5){
        sem_init(&fork_[j],0,1);
        j++;
    }
    
    sem_init(&BOWL,0,2);
    
    int y = 0;
    while(y<=4){
        threadnum[y]=y;
        pthread_create(&thr[y],NULL,let_go_fork,(void *)&threadnum[y]);
        y++;
    }
    
   int x = 0;
   while(x<5){
        pthread_join(thr[x],NULL);
        x++;
    }

    return 0;
}


void attempt_right_fork(int num){

    printf("Philosopher number %d tries to pick right fork up",num);
    printf("\n");
    sem_wait(&fork_[num]);
    printf("Philosopher number %d picks the right fork up",num);
    printf("\n");


}

void attempt_left_fork(int num){

    printf("Philosopher number %d tries to pick left fork up",num);    
    printf("\n");
    sem_wait(&fork_[(num+1)%5]);
    printf("Philosopher number %d picks the left fork up",num);
    printf("\n");

}

void eating(int num){
    printf("Philosopher number %d is eating right now",num);    
    printf("\n");
    sleep(2);
    printf("Philosopher number %d is done eating",num);
    printf("\n");
}



void * let_go_fork(void * b){

    while (true)
    {
        long m;
        long PhilosopherNum=*(int *)b;

        if(PhilosopherNum==4){

            attempt_left_fork(4);
            attempt_right_fork(4);

        }else{

            attempt_right_fork(PhilosopherNum);
            attempt_left_fork(PhilosopherNum);
        }

        sem_getvalue(&BOWL,&m);
        printf("\n");
        printf("Bowl Semaphore is : %d",m);
        printf("\n");

        sem_wait(&BOWL);
        printf("Philosopher number %d has taken bowl and will start eating",PhilosopherNum);
        printf("\n");

        eating(PhilosopherNum);

        sem_post(&BOWL);
        printf("Philosopher %d has returned the bowl to table",PhilosopherNum);
        printf("\n");

        sem_post(&fork_[(PhilosopherNum+1)%5]);
        printf("Philosopher number %d returns left fork to table",PhilosopherNum);
        printf("\n");
        
        sem_post(&fork_[(PhilosopherNum)]);
        printf("Philosopher number %d returns right fork to table",PhilosopherNum);
        printf("\n");
        
          sem_getvalue(&BOWL,&m);
        printf("\n");
        printf("Bowl Semaphore is : %d",m);
        printf("\n");

        

    }
     
}
