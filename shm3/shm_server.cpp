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
    char *str = (char*) shmat(shmid,(void*)0,0); 
 
    char *buffer = (char*)shmat(shmid,(void*)0,0); 

    // cout<<"Write Data : "; 
    // cin >> str; 

    int k = 1; 
    // str = k;
    memcpy( &k , &str , sizeof(char));

    memcpy(buffer,(unsigned char*)&k,4);

    cout << "Data written in memory: " << str  << endl; 
      
    //detach from shared memory  
    shmdt(str); 
  
    return 0; 
} 