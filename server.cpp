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
using namespace std;		
#include "sharedMemoryStruct.h"





int main(int argc, char **argv) {
cout << "hello " << endl;
char nameOfsharedMem [100]; 
memset(nameOfsharedMem, '\0', 100);
strcpy(nameOfsharedMem, SHARED_MEMORY_SEGMENT_NAME);

	// It opens a POSIX shared memory object and makes it available to the calling process via the returned file descriptor.
int sharedMemFileDesc = shm_open(nameOfsharedMem, O_RDWR | O_CREAT, 0660);	
if (sharedMemFileDesc == -1){
	cout << "shm_open error in server" << endl;
}
else{
	cout << "shm_open success in server" << endl;
}

if (ftruncate (sharedMemFileDesc, 500) == -1){
	cout << "ftruncate error in server" << endl;
}
else{
	cout << "ftruncate error in server" << endl;
}

// we can map a POSIX shared memory object to the calling process's virtual address space
sharedMemSegment *sharedMemPtr = static_cast<sharedMemSegment*> (mmap(NULL, 500, PROT_READ | PROT_WRITE, MAP_SHARED, sharedMemFileDesc, 0)); // put random but big integer value for totalSegmentSize
        if (sharedMemPtr == MAP_FAILED){
            cout << "mmap error in server" << endl;
        }
        else{
        	cout << "mmap success in server" << endl;
        }

//close(sharedMemFileDesc);
cout << "ATTEMPTING TO memset shared mem buf" << endl;
//memset(sharedMemPtr->buffer, '\0', 500);

// Writing to shared memory character buffer
cout << "ATTEMPTING TO WRITE" << endl;
int sprintfResult = sprintf(sharedMemPtr->buffer, "Hamza is ");
sharedMemPtr->currentFileSize = 16.22; // 16 is size of Hamza is  

if (sprintfResult < 0){
	cout << "sprintf error" << endl;
}
else{
	cout << "sprinf success" << endl;
}

cout << "reached end of server" << endl;

// when done using shared memory, do the following:
// shm_unlink("sharedMemoryKey");

return 0;
}
