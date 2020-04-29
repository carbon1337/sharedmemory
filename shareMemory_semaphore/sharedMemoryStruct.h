#ifndef _SHM_CHANNEL_H_
#define _SHM_CHANNEL_H_



void printError(const char * msg);

typedef struct sharedMemSegment {

    ssize_t totalFileSize;
    double currentFileSize;
    char buffer[500];
} sharedMemSegment;

#endif
