#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <string.h>
#include "sharedMemoryStruct.h"
using namespace std; 
  
int main() 
{ 
    // ftok to generate unique key 
    key_t key = ftok("shmfile",65); 
  
    // shmget returns an identifier in shmid 
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
  
    // shmat to attach to shared memory 

    sharedMemSegment *sharedMemPtr = static_cast<sharedMemSegment*> (shmat(shmid,(void*)0,0)); 

    sharedMemPtr->currentFileSize = 16.22; // 16 is size of Hamza is  

      
    //detach from shared memory  
    shmdt(sharedMemPtr); 
  
    return 0; 
} 