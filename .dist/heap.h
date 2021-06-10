#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2

typedef struct node {
    int id;
    int index;
} node ;

typedef struct minHeap {
    int size ;
    node *elem ;
} minHeap ;


minHeap initMinHeap(int size);
void insertNode(minHeap *hp, struct node node);
void deleteNode(minHeap *hp);
void levelorderTraversal(minHeap *hp);