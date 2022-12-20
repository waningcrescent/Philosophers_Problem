#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

void *countA();
void *countB();
void *countC();


#define BILLION 10000000000L

int main()
{
//Inputs
    pthread_t ThreadA;
    double timetakenA;
    struct sched_param param_A;
    struct timespec start_timeA, end_timeA;
    
    pthread_t ThreadB;
    double timetakenB;
    struct sched_param param_B;
    struct timespec start_timeB, end_timeB;



    pthread_t ThreadC;
    double timetakenC;
    struct sched_param param_C;
    struct timespec start_timeC, end_timeC;


   
//Clocks
    param_A.sched_priority=0;
    pthread_setschedparam(ThreadA, SCHED_OTHER, &param_A);
    clock_gettime(CLOCK_MONOTONIC, &start_timeA);
    pthread_create(&ThreadA, NULL, countA, NULL);
    pthread_join(ThreadA, NULL);
    pthread_cancel(ThreadA);
    clock_gettime(CLOCK_MONOTONIC, &end_timeA);
    timetakenA = (end_timeA.tv_sec - start_timeA.tv_sec) * BILLION + (end_timeA.tv_nsec - start_timeA.tv_nsec);
    

    param_B.sched_priority=1;;
    pthread_setschedparam(ThreadB, SCHED_RR, &param_B);
    clock_gettime(CLOCK_MONOTONIC, &start_timeB);
    pthread_create(&ThreadB, NULL, countB, NULL);
    pthread_join(ThreadB, NULL);
    pthread_cancel(ThreadB);
    clock_gettime(CLOCK_MONOTONIC, &end_timeB);
    timetakenB = (end_timeB.tv_sec - start_timeB.tv_sec) * BILLION + (end_timeB.tv_nsec - start_timeB.tv_nsec);

    param_C.sched_priority=1;
    pthread_setschedparam(ThreadC, SCHED_FIFO, &param_C);
    clock_gettime(CLOCK_MONOTONIC, &start_timeC);
    pthread_create(&ThreadC, NULL, countC, NULL);
    pthread_join(ThreadC, NULL);
    pthread_cancel(ThreadC);
    clock_gettime(CLOCK_MONOTONIC, &end_timeC);
    timetakenC = (end_timeC.tv_sec - start_timeC.tv_sec) * BILLION + (end_timeC.tv_nsec - start_timeC.tv_nsec);


//Outputs
    printf("Time taken by thread A= %lf nanoseconds\n",timetakenA);
    printf("Time Taken by thread B= %lf nanoseconds\n",timetakenB);
    printf("Time Taken by thread C= %lf nanoseconds\n",timetakenC);

    return 0;
}


void *countA()
{
    long long A = pow(2,32);
    for (long long int a=0;a<A;a++){
    }
    return 0;
}

void *countB()
{
    long long B = pow(2,32);
    for (long long int b=0;b<B;b++){
    }
    return 0;
}

void *countC()
{
    long long C = pow(2,32);
    for (long long int c=0;c<C;c++){
    }
    return 0;
}

printf("git pull working")
