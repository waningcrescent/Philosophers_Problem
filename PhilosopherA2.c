#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

void left_pick(int a);
void right_pick(int a);
void eats(int a);
void* collect_cutlery(void* a);
sem_t Cutlery[5];

int main()
{
    for(int i = 0 ; i<5 ; i++)
    {
        sem_init(&Cutlery[i],0,1);
    }

    int Pnumber[5];
    pthread_t P[5];

    for(int i = 0 ; i<5 ; i++)
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


void left_pick(int a){

    printf("%d) Philospher is waiting on left cutlery\n",a);
    sem_wait(&Cutlery[a]);
    printf("%d) Philospher gets his hands on the left cutlery\n",a);
}


void eats(int a){
    printf("%d) Philospher is eating...\n",a);
}

void right_pick(int a){

    printf("%d) Philospher is waiting on right cutlery\n",a);
    sem_wait(&Cutlery[(a+1)%5]);
    printf("%d) Philospher gets his hands on the right cutlery\n",a);

}


void* collect_cutlery(void* a){

    while (1)
    {
        int P=(int)a;

        if(P==4)
        {

            right_pick(P);
            left_pick(P);

        }
        else
        {

            left_pick(P);
            right_pick(P);
        }

        eats(P);
        sleep(2);

        printf("%d) Philospher is done eating...\n",P);
        sem_post(&Cutlery[(P+1)%5]);
        printf("%d) Philospher gives up the right cutlery\n",P);
        sem_post(&Cutlery[(P)]);
        printf("%d) Philospher gives up the left cutlery\n",P);

    }
      
}
