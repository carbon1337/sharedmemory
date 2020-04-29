#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <iostream>
#include <sys/mman.h>
#include <semaphore.h>
using namespace std;
#include "sharedMemoryStruct.h"


int main(int argc, char **argv) {


int sharedMemoryFileDesc = shm_open("nameOfsharedMem", O_RDWR, 0);
    if (sharedMemoryFileDesc == -1){
        cout << "shm_open error in client" ;
    }


    sharedMemSegment *sharedMemPtr =  static_cast<sharedMemSegment*> (mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED, sharedMemoryFileDesc, 0)); // put random but big integer value for totalSegmentSize
    if (sharedMemPtr == MAP_FAILED){
        cout << "mmap error in client" ;
    }

    close(sharedMemoryFileDesc);

    char fileContRecv[1000];
    strcpy (fileContRecv,  sharedMemPtr->buffer);

// print receiving msg here
    while(1)
    { 
    printf("%s %f \n",  fileContRecv , sharedMemPtr->currentFileSize);
    usleep(100);
    }
// when done using shared memory, do the following:
shm_unlink("nameOfsharedMem");

return 0;
}