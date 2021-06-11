#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
//#include <heap.h>
#include <stdbool.h>

#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2


struct _Record
{
    int id;
    char name[15];
    char surname[15];
    char email[26];
    int grade;
};

//<------------------------------------------ HEAP IMPLEMENTATION ---------------------------------------->

typedef struct node {
    struct _Record record;
} node ;

typedef struct minHeap {
    int size ;
    node *elem ;
} minHeap ;


/*
    Function to initialize the min heap with size = 0
*/
minHeap initMinHeap() {
    minHeap hp ;
    hp.size = 0 ;
    return hp ;
}


/*
    Function to swap data within two nodes of the min heap using pointers
*/
void swap(node *n1, node *n2) {
    node temp = *n1 ;
    *n1 = *n2 ;
    *n2 = temp ;
}

/*
    Heapify function is used to make sure that the heap property is never violated
    In case of deletion of a node, or creating a min heap from an array, heap property
    may be violated. In such cases, heapify function can be called to make sure that
    heap property is never violated
*/
void heapify(minHeap *hp, int i) {
    int smallest = (LCHILD(i) < hp->size && hp->elem[LCHILD(i)].record.id < hp->elem[i].record.id) ? LCHILD(i) : i ;
    if(RCHILD(i) < hp->size && hp->elem[RCHILD(i)].record.id < hp->elem[smallest].record.id) {
        smallest = RCHILD(i) ;
    }
    if(smallest != i) {
        swap(&(hp->elem[i]), &(hp->elem[smallest])) ;
        heapify(hp, smallest) ;
    }
}


/* 
    Build a Min Heap given an array of numbers
    Instead of using insertNode() function n times for total complexity of O(nlogn),
    we can use the buildMinHeap() function to build the heap in O(n) time
*/
void buildMinHeap(minHeap *hp, int *arr, int size) {
    int i ;

    // Insertion into the heap without violating the shape property
    for(i = 0; i < size; i++) {
        if(hp->size) {
            hp->elem = realloc(hp->elem, (hp->size + 1) * sizeof(node)) ;
        } else {
            hp->elem = malloc(sizeof(node)) ;
        }
        node nd ;
        nd.record.id = arr[i] ;
        hp->elem[(hp->size)++] = nd ;
    }

    // Making sure that heap property is also satisfied
    for(i = (hp->size - 1) / 2; i >= 0; i--) {
        heapify(hp, i) ;
    }
}


/*
    Function to insert a node into the min heap, by allocating space for that node in the
    heap and also making sure that the heap property and shape propety are never violated.
*/
void insertNode(minHeap *hp, struct node node) {
    if(hp->size) {
        hp->elem = realloc(hp->elem, (hp->size + 1) * sizeof(node)) ;
    } else {
        hp->elem = malloc(sizeof(node)) ;
    }
    int i = (hp->size)++ ;
    while(i && node.record.id< hp->elem[PARENT(i)].record.id) {
        hp->elem[i] = hp->elem[PARENT(i)] ;
        i = PARENT(i) ;
    }
    hp->elem[i] = node ;
}


/*
    Function to delete a node from the min heap
    It shall remove the root node, and place the last node in its place
    and then call heapify function to make sure that the heap property
    is never violated
*/
struct _Record deleteNode(minHeap *hp) {
    struct _Record saved;
    if(hp->size) {
        saved = hp->elem[0].record;

        hp->elem[0] = hp->elem[--(hp->size)] ;
        hp->elem = realloc(hp->elem, hp->size * sizeof(node)) ;
        heapify(hp, 0) ;
        //printf("%d %s %s %s %d",saved.id,saved.name,saved.surname,saved.email,saved.grade);
        return saved;
        
    } else {
        printf("\nMin Heap is empty!\n") ;
        free(hp->elem);
        return saved; 
    }
}


/*
    Function to get maximum node from a min heap
    The maximum node shall always be one of the leaf nodes. So we shall recursively
    move through both left and right child, until we find their maximum nodes, and
    compare which is larger. It shall be done recursively until we get the maximum
    node
*/
int getMaxNode(minHeap *hp, int i) {
    if(LCHILD(i) >= hp->size) {
        return hp->elem[i].record.id ;
    }

    int l = getMaxNode(hp, LCHILD(i)) ;
    int r = getMaxNode(hp, RCHILD(i)) ;

    if(l >= r) {
        return l ;
    } else {
        return r ;
    }
}


/*
    Function to clear the memory allocated for the min heap
*/
void deleteMinHeap(minHeap *hp) {
    free(hp->elem) ;
}


/*
    Function to display all the nodes in the min heap by doing a inorder traversal
*/
void inorderTraversal(minHeap *hp, int i) {
    if(LCHILD(i) < hp->size) {
        inorderTraversal(hp, LCHILD(i)) ;
    }
    printf("%d ", hp->elem[i].record.id) ;
    if(RCHILD(i) < hp->size) {
        inorderTraversal(hp, RCHILD(i)) ;
    }
}


/*
    Function to display all the nodes in the min heap by doing a preorder traversal
*/
void preorderTraversal(minHeap *hp, int i) {
    if(LCHILD(i) < hp->size) {
        preorderTraversal(hp, LCHILD(i)) ;
    }
    if(RCHILD(i) < hp->size) {
        preorderTraversal(hp, RCHILD(i)) ;
    }
    printf("%d ", hp->elem[i].record.id) ;
}


/*
    Function to display all the nodes in the min heap by doing a post order traversal
*/
void postorderTraversal(minHeap *hp, int i) {
    printf("%d ", hp->elem[i].record.id) ;
    if(LCHILD(i) < hp->size) {
        postorderTraversal(hp, LCHILD(i)) ;
    }
    if(RCHILD(i) < hp->size) {
        postorderTraversal(hp, RCHILD(i)) ;
    }
}


/*
    Function to display all the nodes in the min heap by doing a level order traversal
*/
void levelorderTraversal(minHeap *hp) {
    int i ;
    for(i = 0; i < hp->size; i++) {
        printf("%d %s %s %s %d", hp->elem[i].record.id, hp->elem[i].record.name, hp->elem[i].record.surname, hp->elem[i].record.email, hp->elem[i].record.grade) ;
    }
}
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



struct _MultiIndex{
    int id;
    int index;
};


int findNumberOfRecord(char* fileName){
    FILE *fp;
    struct _Record rec;
    int count= 0;
    char chr;

    fp = fopen(fileName,"r");

    if (fp == NULL)
    {
      perror("Error while opening the file.\n");
      return -1;
    }

    //extract character from file and store in chr
    chr = getc(fp);

   for (chr = getc(fp); chr != EOF; chr = getc(fp))
        if (chr == '\n') // Increment count if this character is newline
            count = count + 1;
    //printf("There are %d lines in %s  in a file\n", count, fileName);
    fclose(fp);
    // decrease count by one because first line is a header line
    return count - 1;
}


int readFile(char* fileName){
    FILE *fp;
    struct _Record rec;
    struct _MultiIndex multiIndex;

    fp = fopen(fileName,"r");

    int numberOfRecord = findNumberOfRecord(fileName);


     int i;

    for (i = 0; i < numberOfRecord; ++i)
    {
        fread(&rec, sizeof(struct _Record), 1, fp);

        multiIndex.id = rec.id;
        multiIndex.index = i;

        printf("%d \n", rec.id);

        //printf("%d \n",i);
    }

    fclose(fp);
    return -1;
}


// Function to find how many record can be added to a buffer
int getNumbOfRecordToAdd(int pageSize){
    // we can find that each record is 64 bit 
    // input given in kb format so we can multiply with 1000
    // and divide with 64 byte to find number of record to added.
    return pageSize * 1000 / 64;

}


// void writeToBuffer(int indexOfBuffer, struct _Record arr_rec[], int sizeOfArray){
   
//     char *fileName;
//     sprintf(fileName,"buffer%d.bin",indexOfBuffer);
//     FILE *fp = fopen(fileName, "wb");
//     if (fp != NULL) {
//         int i=0;
//         for (i = 0; i < sizeOfArray; i++)
//         {
//             fwrite(&arr_rec[i], sizeof(struct _Record), 1, fp);
//         }
        
       
//         fclose(fp);
//     }

// }

void writeToBuffer(int indexOfBuffer, minHeap* minHeap, int sizeOfHeap){
   
    char *fileName;
    sprintf(fileName,"buffer%d.bin",indexOfBuffer);
    struct _Record rec;
    FILE *fp = fopen(fileName, "wb");
    if (fp != NULL) {
        int i=0;
        for (i = 0; i < sizeOfHeap; i++)
        {
            
            rec = deleteNode(minHeap);
            //printf("%d %s %s %s %d \n",rec.id,rec.name,rec.surname,rec.email,rec.grade);
            fwrite(&rec, sizeof(struct _Record), 1, fp);
        }
        
       
        fclose(fp);
    }

}

void readFromABuffer(char* fileName){
    FILE *fp = fopen(fileName,"rb");
    int pageSize = 8;
    int numberOfRecordToAdd = getNumbOfRecordToAdd(pageSize);
    struct _Record arr_rec[numberOfRecordToAdd];
   
    fread(&arr_rec, sizeof(struct _Record), numberOfRecordToAdd, fp);
    int i = 0;
    for ( i = 0; i < numberOfRecordToAdd; i++)
    {
       printf("%d %s %s %s %d\n",arr_rec[i].id,arr_rec[i].name,arr_rec[i].surname,arr_rec[i].email,arr_rec[i].grade);
    }

    fclose(fp);
    
}



void getSplittedLine(char* line, char* array[]){
    char* splitted;
    splitted = strtok(line, ";");
    int i=0;
    while (splitted != NULL)//Read the data of each row
    {
        array[i++] = splitted;
        //printf("%s ", splitted);//Print out every data read
        splitted = strtok(NULL, ";");
    }

} 


void readIntoRecord(struct _Record* rec, char* array[]){
    rec->id = atoi(array[0]);
    strcpy(rec->name,array[1]);
    strcpy(rec->surname,array[2]);
    strcpy(rec->email,array[3]);
    rec->grade = atoi(array[4]);
    //return rec;
}


int readCSV(char* fileName){
    
    FILE *fp = NULL;
	char *line;
	char lineBuffer[1024];
    bool isFirstLine = true;
    int counter = 0;
    struct _Record rec;
    struct _MultiIndex multiIndex;
   

    char *array[4];

    int numberOfBuffer = 5;
    int pageSize = 8;
    int bufferIndex = 1;
    int numberOfRecordToAdd = getNumbOfRecordToAdd(pageSize);
    struct _Record arr_rec[numberOfRecordToAdd];

    minHeap heap = initMinHeap(numberOfRecordToAdd);
    

	if ((fp = fopen(fileName, "at+")) != NULL)
	{
		 while ((line = fgets(lineBuffer, sizeof(lineBuffer), fp))!=NULL)//The loop continues when the end of the file is not read
		{
            // if reader reads first line skip that line
            if(isFirstLine){
                isFirstLine = false;
                continue;
            }
            // split line and add into array
            getSplittedLine(line,array);
            //Read splitted line into record
            rec.id = atoi(array[0]);
            strcpy(rec.name,array[1]);
            strcpy(rec.surname,array[2]);
            strcpy(rec.email,array[3]);
            rec.grade = atoi(array[4]);
            //readIntoRecord(&rec,array);
            //Add records to record array
            //rec = readIntoRecord(rec,array);

            // Create record array
            arr_rec[counter % numberOfRecordToAdd] = rec;
            // Create multi index
            // multiIndex.id = rec.id;
            // multiIndex.index = counter;

            //<----------- Replacement Selection Sort -------------->
            // create node for heap
            struct node node;
            node.record = rec;
            insertNode(&heap,node);
            counter += 1;
            if(counter % numberOfRecordToAdd == 0){
                //levelorderTraversal(&heap);
                writeToBuffer(bufferIndex,&heap,numberOfRecordToAdd);
                //writeToBuffer(bufferIndex,arr_rec,numberOfRecordToAdd);
                bufferIndex += 1;
                if(bufferIndex == 5){
                    // merge files and add to output buffer
                    bufferIndex = 1;
                    break;
                }
            }  
            //printf("%d %s %s %s %d",rec.id,rec.name,rec.surname,rec.email,rec.grade);
			//printf("\n");   
		 }
		fclose(fp);
		fp = NULL;
    }
}



// function to sort the subsection a[i .. j] of the array a[]
void merge_sort(int i, int j, int a[], int aux[]) {
    if (j <= i) {
        return;     // the subsection is empty or a single element
    }
    int mid = (i + j) / 2;

    // left sub-array is a[i .. mid]
    // right sub-array is a[mid + 1 .. j]
    
    merge_sort(i, mid, a, aux);     // sort the left sub-array recursively
    merge_sort(mid + 1, j, a, aux);     // sort the right sub-array recursively

    int pointer_left = i;       // pointer_left points to the beginning of the left sub-array
    int pointer_right = mid + 1;        // pointer_right points to the beginning of the right sub-array
    int k;      // k is the loop counter

    // we loop from i to j to fill each element of the final merged array
    for (k = i; k <= j; k++) {
        if (pointer_left == mid + 1) {      // left pointer has reached the limit
            aux[k] = a[pointer_right];
            pointer_right++;
        } else if (pointer_right == j + 1) {        // right pointer has reached the limit
            aux[k] = a[pointer_left];
            pointer_left++;
        } else if (a[pointer_left] < a[pointer_right]) {        // pointer left points to smaller element
            aux[k] = a[pointer_left];
            pointer_left++;
        } else {        // pointer right points to smaller element
            aux[k] = a[pointer_right];
            pointer_right++;
        }
    }

    for (k = i; k <= j; k++) {      // copy the elements from aux[] to a[]
        a[k] = aux[k];
    }
}


int main(){


    //readCSV("students1.csv");
    // minHeap heap = initMinHeap();
    // struct _Record rec;
    readFromABuffer("buffer1.bin");
    readFromABuffer("buffer2.bin");
    readFromABuffer("buffer3.bin");
    readFromABuffer("buffer4.bin");



  
    //readCSV("students1.csv");
    // readFromABuffer("buffer1.bin");
    // readFromABuffer("buffer2.bin");
    // readFromABuffer("buffer3.bin");
    // readFromABuffer("buffer4.bin");

    // minHeap minHeap = initMinHeap(50);
    // struct _Record rec;

    // struct _Record r1, r2, r3, r4, r5, r6;

    // r1.id=3;
    // r2.id=5;
    // r3.id=1;
    // r4.id = 17;
    // r5.id=4;
    // r6.id = 33;
    // node n1,n2,n3,n4,n5,n6;

    // n1.record =r1;
    // n2.record =r2;
    // n3.record =r3;
    // n4.record =r4;
    // n5.record =r5;
    // n6.record =r6;


    // insertNode(&minHeap,n1);
    // insertNode(&minHeap,n2);
    // insertNode(&minHeap,n3);
    // insertNode(&minHeap,n4);
    // insertNode(&minHeap,n5);
    // insertNode(&minHeap,n6);
  

    // levelorderTraversal(&minHeap);

    // rec = deleteNode(&minHeap);
    // printf("%d \n",rec.id);

    // levelorderTraversal(&minHeap);

    // rec = deleteNode(&minHeap);
    // printf("%d \n",rec.id);




    return -1;

}








