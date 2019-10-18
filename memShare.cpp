// bridge struct
typedef struct sharedMemSegment {

    ssize_t totalFileSize;
    ssize_t currentFileSize;
    char buffer[];
} sharedMemSegment;


// WRITING
char nameOfsharedMem [100]; 
memset(nameOfsharedMem, '\0', 100);
strcpy(nameOfsharedMem, "sharedMemoryKey");

// It opens a POSIX shared memory object and makes it available to the calling process via the returned file descriptor.
int sharedMemFileDesc = shm_open(sharedMemName, O_RDWR, 0);	
        if (sharedMemFileDesc == -1){
            printError("shm_open error in cache");
        }

// we can map a POSIX shared memory object to the calling process's virtual address space
sharedMemSegment *sharedMemPtr = mmap(NULL, totalSegmentSize, PROT_READ | PROT_WRITE, MAP_SHARED, sharedMemFileDesc, 0); // put random but big integer value for totalSegmentSize
        if (sharedMemPtr == MAP_FAILED){
            printError("mmap error in cache");
        }

close(sharedMemFileDesc);

memset(&sharedMemPtr->buffer, 0, 1000);

// Writing to shared memory character buffer
strcpy(&sharedMemPtr->buffer, "Hamza is GAYYYYY");
sharedMemPtr->currentFileSize = 16; // 16 is size of Hamza is GAYYYYY

// when done using shared memory, do the following:
shm_unlink("sharedMemoryKey");

// READING

int sharedMemoryFileDesc = shm_open("sharedMemoryKey", O_RDWR, 0);
    if (sharedMemoryFileDesc == -1){
        printError("shm_open error in handle_with_cache");
    }

    sharedMemSegment *sharedMemoryPtr = mmap(NULL, totalSegmentSize, PROT_READ | PROT_WRITE, MAP_SHARED, sharedMemoryFileDesc, 0); // put random but big integer value for totalSegmentSize
    if (sharedMemoryPtr == MAP_FAILED){
        printError("mmap error in handle_with_cache");
    }

    close(sharedMemoryFileDesc);

    char fileContRecv[1000];
    strcpy (fileContRecv, & sharedMemPtr->buffer);

// print receiving msg here

// when done using shared memory, do the following:
shm_unlink("sharedMemoryKey");