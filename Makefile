CC = gcc
CFLAGS = -Wall

all: scheduler

scheduler: scheduler.c ai_module.c
	$(CC) $(CFLAGS) scheduler.c ai_module.c -o scheduler

clean:
	rm -f scheduler
