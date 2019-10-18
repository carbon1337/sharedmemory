#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <string.h>
#include "sharedMemoryStruct.h"
using namespace std; 
  
int main() 
{ 
    union {
        int d;
        char bytes[sizeof(double)];
    } packet;

    // ftok to generate unique key 
    key_t key = ftok("shmfile",65); 
  
    // shmget returns an identifier in shmid 
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
  
    // shmat to attach to shared memory 
    // char *str = (char*) shmat(shmid,(void*)0,0); 
    //int k_rev;
   
   // memcpy(&str , &k_rev , sizeof(int));
    
    // packet.bytes[0] = str[0];
    // packet.bytes[1] = str[1];
    // packet.bytes[2] = str[2];
    // packet.bytes[3] = str[3];

    // cout <<  "Data read from memory: "  << packet.d  << endl; 
     sharedMemSegment *sharedMemPtr = static_cast<sharedMemSegment*> (shmat(shmid,(void*)0,0)); 
      cout << " LOL DONE " << sharedMemPtr->currentFileSize;
    //detach from shared memory  
    shmdt(sharedMemPtr); 
    
    // destroy the shared memory 
    shmctl(shmid,IPC_RMID,NULL); 
     
    return 0; 
} 