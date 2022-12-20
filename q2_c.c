#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>


void left_pick(int a);
void right_pick(int a);
void eats(int a);
void* collect_cutlery(void* a);

sem_t Cutlery[5];
sem_t bowl;


int main()
{

    for(int i = 0 ; i<5 ; i++)
    {
        sem_init(&Cutlery[i],0,1);
    }

    sem_init(&bowl,0,2);
    int Pnumber[5];
    pthread_t P[5];

    for(int i=0; i<5 ; i++)
    {
        Pnumber[i]=i;
        pthread_create(&P[i],NULL,collect_cutlery,(void *)&Pnumber[i]);
    }

    int i=0;
    while(i<5)
    {
        pthread_join(P[i],NULL);
        i++;
    }

    return 0;
}

void eats(int n){
    printf("%d) Philosopher is eating...\n ",n);
}

void left_pick(int n){

    printf("%d) Philosopher is waiting on left cutlery\n",n);
    sem_wait(&Cutlery[n]);
    printf("%d) Philosopher gets his hands on the left cutlery\n",n);
}

void right_pick(int n){

    printf("%d) Philosopher is waiting on right cutlery\n",n);
    sem_wait(&Cutlery[(n+1)%5]);
    printf("%d) Philosopher gets his hands on the right cutlery\n",n);

}


void * collect_cutlery(void * n){

    while (1)
    {
        int sep;
        int P=*(int *)n;

        if(P!=4){

            left_pick(P);
            right_pick(P);

        }
        else{

            right_pick(P);
            left_pick(P);        
        }

        sem_getvalue(&bowl,&sep);
        printf("%d is Bowl semaphore value\n",sep);

        sem_wait(&bowl);
        printf("%d)Philosopher has the bowl\n",P);

        eats(P);
        sleep(2);

        sem_post(&bowl);
        printf("%d)Philosopher is done eating... and gives up the bowl\n",P);

        //printf("%d) Philosopher gives up the bowl\n",P);
        sem_post(&Cutlery[(P+1)%5]);
        printf("%d) Philosopher gives up the right cutlery\n",P);
        sem_post(&Cutlery[(P)]);
        printf("%d) Philosopher gives up the left cutlery\n",P);

        sem_getvalue(&bowl,&sep);
        printf("%d is Bowl semaphore value\n",sep);
        

    }
     
}
