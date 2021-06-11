#include <limits.h>
#include <stdio.h>
#include <stdlib.h>


struct Queue* createQueue(unsigned capacity);
void enqueue(struct Queue* queue, int item);
int dequeue(struct Queue* queue);