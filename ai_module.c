#include <stdio.h>
#include <string.h>
#include "ai_module.h"

typedef struct {
    char name[50];
    int avg_execution_time;
} ProcessHistory;

ProcessHistory history[] = {
    {"editor", 200},
    {"browser", 500},
    {"compiler", 700},
    {"network", 300}
};

#define HISTORY_SIZE (sizeof(history) / sizeof(history[0]))

int calculate_priority(Process *process) {
    int base_priority = 10;
    int penalty = 0;

    for (int i = 0; i < HISTORY_SIZE; i++) {
        if (strcmp(process->name, history[i].name) == 0) {
            if (process->execution_time > history[i].avg_execution_time) {
                penalty = (process->execution_time - history[i].avg_execution_time) / 50;
            }
            break;
        }
    }

    return base_priority - penalty;
}
