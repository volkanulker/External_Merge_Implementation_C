#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 10

//building a min-heap
typedef struct heap{
	int data[HEAP_SIZE + 1];  //the body of the heap
	int total_elements; //the current number of elements in the heap
}heap;

void heap_insert(heap *heap, int x);
void heap_init(heap *heap);
void make_heap(heap *heap, int s[], int n);
void print_heap(heap *heap);
int get_minimum(heap *heap);
int get_parent(int n);
int young_child(int n);
int remove_minimum(heap *heap);
void bubble_up(heap *heap, int total_elements);
void bubble_down(heap *heap, int index);
void heap_insert(heap *heap, int x);