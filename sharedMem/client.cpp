#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sched.h>
#include <syscall.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdbool.h>

pthread_cond_t* condition;
pthread_mutex_t* mutex;

#define OKTOWRITE "/oktowrite"
#define MESSAGE "/message"
#define MUTEX "/lock"

struct shared_use_st 
{
bool conditionSatisfied;
};

struct shared_use_st *shared_stuff;

void create_shared_memory()
{
    int shmid;
    void *shared_memory=(void *)0;
    shmid =shmget( (key_t)1234, 4096, 0666 | IPC_CREAT );

    if (shmid == -1)
    {
        fprintf(stderr,"shmget failed\n");
        exit(EXIT_FAILURE);
    }

    shared_memory =shmat(shmid, (void *)0,0);

    if(shared_memory == (void *)-1)
    {
        fprintf(stderr,"shmat failed\n");
        exit(EXIT_FAILURE); 
    }

    shared_stuff = (struct shared_use_st *)shared_memory;
}

int main()
{
    int des_cond, des_msg, des_mutex;
    int mode = S_IRWXU | S_IRWXG;

    des_mutex = shm_open(MUTEX, O_CREAT | O_RDWR | O_TRUNC, mode);

    if (des_mutex < 0) {
        perror("failure on shm_open on des_mutex");
        exit(1);
    }

    if (ftruncate(des_mutex, sizeof(pthread_mutex_t)) == -1) {
        perror("Error on ftruncate to sizeof pthread_cond_t\n");
        exit(-1);
    }

    mutex = (pthread_mutex_t*) mmap(NULL, sizeof(pthread_mutex_t),PROT_READ | PROT_WRITE, MAP_SHARED, des_mutex, 0);

    if (mutex == MAP_FAILED ) {
        perror("Error on mmap on mutex\n");
        exit(1);
    }

    des_cond = shm_open(OKTOWRITE, O_CREAT | O_RDWR | O_TRUNC, mode);

    if (des_cond < 0) {
        perror("failure on shm_open on des_cond");
        exit(1);
    }

    if (ftruncate(des_cond, sizeof(pthread_cond_t)) == -1) {
        perror("Error on ftruncate to sizeof pthread_cond_t\n");
        exit(-1);
    }

    condition = (pthread_cond_t*) mmap(NULL, sizeof(pthread_cond_t),PROT_READ | PROT_WRITE, MAP_SHARED, des_cond, 0);

    if (condition == MAP_FAILED ) {
        perror("Error on mmap on condition\n");
        exit(1);
    }

    /* set mutex shared between processes */
    pthread_mutexattr_t mutexAttr;
    pthread_mutexattr_init(&mutexAttr);
    pthread_mutexattr_setpshared(&mutexAttr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(mutex, &mutexAttr);

    /* set condition shared between processes */
    pthread_condattr_t condAttr;
    pthread_condattr_init(&condAttr);
    pthread_condattr_setpshared(&condAttr, PTHREAD_PROCESS_SHARED);
    pthread_cond_init(condition, &condAttr);

    create_shared_memory();
    shared_stuff->conditionSatisfied=0;

    while(1)
    {
        printf("Receiver waits on for signal from hello1.c \n");

        pthread_mutex_lock(mutex);
        while(!shared_stuff->conditionSatisfied)
            pthread_cond_wait(condition, mutex);
        pthread_mutex_unlock(mutex);

        printf("Signal received, wake up!!!!!!!!\n");

        //reset
        pthread_mutex_lock(mutex);
        shared_stuff->conditionSatisfied=0;
        pthread_mutex_unlock(mutex);
    }

}