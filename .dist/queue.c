// // C program for array implementation of queue
// #include <limits.h>
// #include <stdio.h>
// #include <stdlib.h>
 

// struct Queue* createQueue(unsigned capacity);
// void enqueue(struct Queue* queue, int item);
// int dequeue(struct Queue* queue);
// A structure to represent a queue
//<------------------------------------------QUEUE IMPLEMENTATION-------------------------------------------------------->



/* a link in the queue, holds the info and point to the next Node*/
// typedef struct {
//     int info;
// } DATA;

// typedef struct Node_t {
//     struct _Record data;
//     struct Node_t *prev;
// } NODE;

// /* the HEAD of the Queue, hold the amount of node's that are in the queue*/
// typedef struct Queue {
//     NODE *head;
//     NODE *tail;
//     int size;
//     int limit;
// } Queue;

// Queue *ConstructQueue(int limit);
// void DestructQueue(Queue *queue);
// int Enqueue(Queue *pQueue, NODE *item);
// NODE *Dequeue(Queue *pQueue);
// int isEmpty(Queue* pQueue);

// Queue *ConstructQueue(int limit) {
//     Queue *queue = (Queue*) malloc(sizeof (Queue));
//     if (queue == NULL) {
//         return NULL;
//     }
//     if (limit <= 0) {
//         limit = 65535;
//     }
//     queue->limit = limit;
//     queue->size = 0;
//     queue->head = NULL;
//     queue->tail = NULL;

//     return queue;
// }

// void DestructQueue(Queue *queue) {
//     NODE *pN;
//     while (!isEmpty(queue)) {
//         pN = Dequeue(queue);
//         free(pN);
//     }
//     free(queue);
// }

// int Enqueue(Queue *pQueue, NODE *item) {
//     /* Bad parameter */
//     if ((pQueue == NULL) || (item == NULL)) {
//         return false;
//     }
//     // if(pQueue->limit != 0)
//     if (pQueue->size >= pQueue->limit) {
//         return false;
//     }
//     /*the queue is empty*/
//     item->prev = NULL;
//     if (pQueue->size == 0) {
//         pQueue->head = item;
//         pQueue->tail = item;

//     } else {
//         /*adding item to the end of the queue*/
//         pQueue->tail->prev = item;
//         pQueue->tail = item;
//     }
//     pQueue->size++;
//     return true;
// }

// NODE * Dequeue(Queue *pQueue) {
//     /*the queue is empty or bad param*/
//     NODE *item;
//     if (isEmpty(pQueue))
//         return NULL;
//     item = pQueue->head;
//     pQueue->head = (pQueue->head)->prev;
//     pQueue->size--;
//     return item;
// }

// int isEmpty(Queue* pQueue) {
//     if (pQueue == NULL) {
//         return false;
//     }
//     if (pQueue->size == 0) {
//         return true;
//     } else {
//         return false;
//     }
// }


 
// // Driver program to test above functions./
// int main()
// {
//     struct Queue* queue = createQueue(1000);
 
//     enqueue(queue, 10);
//     enqueue(queue, 20);
//     enqueue(queue, 30);
//     enqueue(queue, 40);
 
//     printf("%d dequeued from queue\n\n",
//            dequeue(queue));
 
//     printf("Front item is %d\n", front(queue));
//     printf("Rear item is %d\n", rear(queue));
 
//     return 0;
// }