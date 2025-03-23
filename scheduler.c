#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include "ai_module.h"  // Includes the fixed Process struct

#define MAX_PROCESSES 100

Process processQueue[MAX_PROCESSES];
int processCount = 0;

// Load processes from a file
void load_processes(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    while (fscanf(file, "%d %s %d %d",
                  &processQueue[processCount].id,
                  processQueue[processCount].name,
                  &processQueue[processCount].arrival_time,
                  &processQueue[processCount].execution_time) != EOF) {
        processQueue[processCount].priority = 0;
        processCount++;
    }

    fclose(file);
}

// Execute a process using fork() and exec()
void execute_process(Process *process) {
    process->pid = fork();  // Now pid is correctly recognized

    if (process->pid == 0) { // Child process
        printf("Executing Process: %s (PID: %d, Priority: %d)\n",
               process->name, getpid(), process->priority);
        sleep(process->execution_time / 1000);
        exit(0);
    } else if (process->pid > 0) { // Parent process
        waitpid(process->pid, NULL, 0); // Wait for child to finish
    } else {
        perror("Fork failed");
    }
}

// AI-based process scheduler
void ai_scheduler() {
    for (int i = 0; i < processCount; i++) {
        processQueue[i].priority = calculate_priority(&processQueue[i]);
    }

    // Sort processes by priority (higher priority first)
    for (int i = 0; i < processCount - 1; i++) {
        for (int j = i + 1; j < processCount; j++) {
            if (processQueue[i].priority < processQueue[j].priority) {
                Process temp = processQueue[i];
                processQueue[i] = processQueue[j];
                processQueue[j] = temp;
            }
        }
    }

    printf("\nExecuting AI-Enhanced Process Scheduling:\n");
    for (int i = 0; i < processCount; i++) {
        execute_process(&processQueue[i]);
    }
}

// FIFO process scheduler for comparison
void fifo_scheduler() {
    printf("\nExecuting FIFO Process Scheduling:\n");
    for (int i = 0; i < processCount; i++) {
        execute_process(&processQueue[i]);
    }
}

int main() {
  load_processes("test_cases/test2.txt");

  clock_t start, end;
  double fifo_time, ai_time;

  start = clock();
  fifo_scheduler();  // Run FIFO
  end = clock();
  fifo_time = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("\nFIFO Execution Time: %f seconds\n", fifo_time);

  start = clock();
  ai_scheduler();    // Run AI-based scheduler
  end = clock();
  ai_time = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("\nAI Execution Time: %f seconds\n", ai_time);

  printf("\nLatency Reduction: %f seconds\n", fifo_time - ai_time);
  return 0;
}
