#ifndef _SHM_CHANNEL_H_
#define _SHM_CHANNEL_H_



#define MESSAGE_QUEUE "/message_queue"
#define SHARED_MEMORY_SEGMENT_NAME "SHARED-MEMORY-3"
#define MAX_MSG_SIZE 4096
#define MAX_MESSAGES 10

void printError(const char * msg);

typedef struct sharedMemSegment {

    ssize_t totalFileSize;
    double currentFileSize;
    char buffer[500];
} sharedMemSegment;

#endif
