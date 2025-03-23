#ifndef AI_MODULE_H
#define AI_MODULE_H

#include <sys/types.h> // For pid_t

typedef struct {
    int id;
    char name[50];
    int arrival_time;
    int execution_time;
    int priority;
    pid_t pid;  // Ensure pid is included
} Process;

int calculate_priority(Process *process);

#endif
