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

//<---------------------------------------- MERGE OPERATIONS ------------------------------------>
// function to sort the subsection a[i .. j] of the array a[]
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(struct _Record recordArr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    /* create temp arrays */
    struct _Record L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = recordArr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = recordArr[m + 1 + j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i].id <= R[j].id) {
            recordArr[k] = L[i];
            i++;
        }
        else {
            recordArr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        recordArr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        recordArr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(struct _Record recordArr[], int l, int r)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;
 
        // Sort first and second halves
        mergeSort(recordArr, l, m);
        mergeSort(recordArr, m + 1, r);
 
        merge(recordArr, l, m, r);
    }
}

/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(struct _Record recordArr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d,", recordArr[i].id);
    printf("\n");
}


// struct _MultiIndex{
//     int id;
//     int index;
// };

// function to find number of records in given csv file
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


// Function to find how many record can be added to a buffer
int getNumbOfRecordToAdd(int pageSize){
    // we can find that each record is 64 bit 
    // input given in kb format so we can multiply with 1000
    // and divide with 64 byte to find number of record to added.
    return pageSize * 1000 / 64;

}

// method to write merged records into output buffer
void writeMergedRecs(int chunkFileIdx, struct _Record arr_rec[], int sizeOfArray){
   
    char *fileName = (char*)malloc(11 * sizeof(char));;
    sprintf(fileName,"%s%d%s","chunk",chunkFileIdx,".bin");
    //sprintf(fileName,"buffer5.bin",indexOfBuffer);
    FILE *fp = fopen(fileName, "wb");
    //fseek(fp,0,SEEK_END);
    struct _Record rec;
    if (fp != NULL) {
        int i;
        for (i = 0; i < sizeOfArray; i++)
        {
            rec = arr_rec[i];   
            fwrite(&arr_rec[i], sizeof(struct _Record), 1, fp);
        }
        fclose(fp);
    }
}


// write records that sorted with replacement sort to buffers
void writeRSortedToBuffer(int indexOfBuffer, minHeap* minHeap, int sizeOfHeap){
    char *fileName = (char*)malloc(11 * sizeof(char));;
    sprintf(fileName,"%s%d%s","buffer",indexOfBuffer,".bin");
    struct _Record rec;
    FILE *fp = fopen(fileName, "wb");
    if (fp != NULL) {
        int i;
        for (i = 0; i < sizeOfHeap ; i++)
        {
            
            rec = deleteNode(minHeap);
            //printf("%d %s %s %s %d \n",rec.id,rec.name,rec.surname,rec.email,rec.grade);
            fwrite(&rec, sizeof(struct _Record), 1, fp);
        }
 
        fclose(fp);
    }

}


// void readFromABuffer(char* fileName){
//     FILE *fp = fopen(fileName,"rb");
//     int pageSize = 8;
//     int numberOfRecordToAdd = getNumbOfRecordToAdd(pageSize);
//     struct _Record arr_rec[numberOfRecordToAdd];
   
//     fread(&arr_rec, sizeof(struct _Record), numberOfRecordToAdd, fp);
//     int i = 0;
//     for ( i = 0; i < numberOfRecordToAdd*2; i++)
//        printf("%d %s %s %s %d\n",arr_rec[i].id,arr_rec[i].name,arr_rec[i].surname,arr_rec[i].email,arr_rec[i].grade);

//     fclose(fp);
// }





// read records from a buffer and read them into an array
void readRecordsIntoArray(struct _Record recordArr[], int startIdx,int lastIdx, FILE *fp){
    int i;
    for ( i = startIdx; i < lastIdx; i++)
        fread(&recordArr[i], sizeof(struct _Record), 1, fp);
    
    fclose(fp);
}


//TODO: Dosya bitene kadar okuma yapacak hale getir
// take two buffer inputs merge and write them into output buffer 
void mergeBuffers(char* bufferName1, char* bufferName2,int chunkFileIdx){
    
    int pageSize = 8;
    int numberOfRecordToAdd = getNumbOfRecordToAdd(pageSize);
    struct _Record arr_rec[numberOfRecordToAdd];
    FILE *fp = fopen(bufferName1,"rb");
    //Read first half of first buffer
    readRecordsIntoArray(arr_rec,0,numberOfRecordToAdd/2,fp);
    fp = fopen(bufferName2,"rb");
    //Read first half of second buffer
    readRecordsIntoArray(arr_rec,numberOfRecordToAdd/2,numberOfRecordToAdd,fp);
    //merge these records
    mergeSort(arr_rec,0,numberOfRecordToAdd - 1);
    //write merged records to output buffer (buffer5)
    writeMergedRecs(chunkFileIdx,arr_rec,numberOfRecordToAdd);

    
    //number of byte to reach second half of buffer
    int byteToSeek =  sizeof(struct _Record)*((int)numberOfRecordToAdd/2);
    fp = fopen(bufferName1,"rb");
    //seek to middle of the first buffer
    fseek(fp,byteToSeek, SEEK_SET);
    //read records into array
    readRecordsIntoArray(arr_rec,0,numberOfRecordToAdd/2,fp);
    fp = fopen(bufferName2,"rb");
    //seek to middle of the second buffer
    fseek(fp,byteToSeek, SEEK_SET);
    //read records into array
    readRecordsIntoArray(arr_rec,numberOfRecordToAdd/2,numberOfRecordToAdd,fp);
    //merge records
    mergeSort(arr_rec,0,numberOfRecordToAdd - 1);
    //write merged records to output buffer
    writeMergedRecs(chunkFileIdx,arr_rec,numberOfRecordToAdd);
}

int findIndexOfDeletedNode(struct _Record arr[],struct _Record rec,int sizeOfArray){
    int i;
    for (i = 0; i < sizeOfArray; i++)
    {
        if(arr[i].id == rec.id){
            return i;
        }
    }
    return -1;
}



// method to split a csv line
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

// Method to read splitted csv line into struct record
void readIntoRecord(struct _Record* rec, char* array[]){
    rec->id = atoi(array[0]);
    strcpy(rec->name,array[1]);
    strcpy(rec->surname,array[2]);
    strcpy(rec->email,array[3]);
    rec->grade = atoi(array[4]);
}


//TODO: Number of recordu dinamik hale getir
void readFromOutputBuffer(char* fileName){

    struct _Record rec;
    FILE *fp = fopen(fileName, "rb");
    fseek(fp,0,SEEK_END);
    int sizeOfRecord = sizeof(struct _Record);
    int numberOfByte = ftell(fp);
    fseek(fp,0,SEEK_SET);
    int numbOfRecord = numberOfByte / sizeOfRecord;
    //printf("%d",numbOfRecord);
    int i;
    for (i = 0; i < numbOfRecord; i++)
    {
        fread(&rec,sizeof(struct _Record),1,fp);
        printf("%d %s %s %s %d  \n",rec.id,rec.name,rec.surname,rec.email,rec.grade);
    }
    
    // int i;
    // for (i = 0; i < numbOfRecord; i++)
    // {
    //     fread(&rec,sizeOfRecord,1,fp);
    //     printf("%d %s %s %s %d %d\n",rec.id,rec.name,rec.surname,rec.email,rec.grade,i);
    // }
    fclose(fp);
}

// function to find where minimum element come from
int findWhichFile(struct _Record recArr[], struct _Record rec, int numberOfFile){
    int i;
    for (i = 0; i < numberOfFile; i++)
       if(recArr[i].id == rec.id)
           return i;
    printf("%s","An error is happened in 'findWhichFile' function.");
    return -5;
}
// function to check if opened files closed
bool areFilesClosed(FILE* filePointers[],int sizeOfPointerArr){
    int i;
    for (i = 0; i < sizeOfPointerArr; i++)
        if(filePointers[i] != NULL)
            return false;

    return true;
}

void createChunk(int numberOfFile,int indexOfChunk){
    FILE* filePointers[numberOfFile];
    char *fileName = (char*)malloc(12 * sizeof(char));

    char *outputFileName = (char*)malloc(12 * sizeof(char));
    sprintf(outputFileName,"%s%d%s","chunk",indexOfChunk,".bin");
    
    FILE *outputFile=fopen(outputFileName,"wb");
    struct _Record rec;
    struct node recNode;
    // open files to merge
    int i;
    for (i = 0; i < numberOfFile; i++)
    {
        sprintf(fileName,"%s%d%s","buffer",i,".bin");
        filePointers[i]= fopen(fileName,"rb");
    }

    minHeap heap = initMinHeap();
    struct _Record recArr[numberOfFile];
    struct _Record deletedRec;
    int fileIdx;
    // insert record into heap one by one from files
    int k;
    for (k = 0; k < numberOfFile; k++)
    {
        fread(&rec,sizeof(struct _Record),1,filePointers[k]);
        recNode.record = rec;
        recArr[k] = rec;
        insertNode(&heap,recNode);  
    }

    // add record into heap and write min to output sorted file
    //until all files are sorted
    int ctr=0;
    while ( !areFilesClosed(filePointers,numberOfFile))
    {
        deletedRec = deleteNode(&heap);
        fileIdx=findWhichFile(recArr,deletedRec,numberOfFile);
        // check if file pointer points end of the file
        if(fread(&rec,sizeof(struct _Record),1,filePointers[fileIdx]) == 0){
            rec.id = INT_MAX;
            fclose(filePointers[fileIdx]);
            filePointers[fileIdx] = NULL;
        } 
        recNode.record = rec;
        recArr[fileIdx] = rec;
        insertNode(&heap,recNode);
        ctr += 1;
        fwrite(&deletedRec,sizeof(struct _Record),1,outputFile);
        //printf("%d %s %s %s %d ctr:%d IDX:%d\n",deletedRec.id,deletedRec.name,deletedRec.surname,deletedRec.email,deletedRec.grade,ctr,fileIdx);
    }
    
    fclose(outputFile);
}


void createSortedFile(int numberOfChunk,char* OutputFileName){
    FILE* filePointers[numberOfChunk];
    char *fileName = (char*)malloc(12 * sizeof(char));

    FILE *outputFile=fopen(OutputFileName,"w");
    struct _Record rec;
    struct node recNode;
    // open files to merge
    int i;
    for (i = 0; i < numberOfChunk; i++)
    {
        sprintf(fileName,"%s%d%s","chunk",i,".bin");
        filePointers[i]= fopen(fileName,"rb");
    }

    minHeap heap = initMinHeap();
    struct _Record recArr[numberOfChunk];
    struct _Record deletedRec;
    int fileIdx;
    // insert record into heap one by one from files
    int k;
    for (k = 0; k < numberOfChunk; k++)
    {
        fread(&rec,sizeof(struct _Record),1,filePointers[k]);
        recNode.record = rec;
        recArr[k] = rec;
        insertNode(&heap,recNode);  
    }

    // add record into heap and write min to output sorted file
    //until all files are sorted
    int ctr=0;
    char* fileNameToRemove= (char*)malloc(12 * sizeof(char));
    while ( !areFilesClosed(filePointers,numberOfChunk))
    {
        deletedRec = deleteNode(&heap);
        fileIdx=findWhichFile(recArr,deletedRec,numberOfChunk);
        // check if file pointer points end of the file
        if(fread(&rec,sizeof(struct _Record),1,filePointers[fileIdx]) == 0){
            rec.id = INT_MAX;
            sprintf(fileNameToRemove,"%s%d%s","chunk",fileIdx,".bin");
            // close and remove merged chunks
            fclose(filePointers[fileIdx]);
            remove(fileNameToRemove);
            //printf("%s %s \n",fileNameToRemove,"is merged and removed.");
            filePointers[fileIdx] = NULL;
        } 
        recNode.record = rec;
        recArr[fileIdx] = rec;
        insertNode(&heap,recNode);
        ctr += 1;
        fprintf(outputFile, "%d %s %s %s %d\n", deletedRec.id, deletedRec.name, deletedRec.surname,deletedRec.email,deletedRec.grade);
        //fwrite(&deletedRec,sizeof(struct _Record),1,outputFile);
        //printf("%d %s %s %s %d ctr:%d IDX:%d\n",deletedRec.id,deletedRec.name,deletedRec.surname,deletedRec.email,deletedRec.grade,ctr,fileIdx);
    }
    
    fclose(outputFile);
}
// core function does so many things
int readCSV(char* fileName,char* outputFileName, int numberOfBuffer, int pageSize){
    
    FILE *fp = NULL;
	char *line;
	char lineBuffer[1024];
    bool isFirstLine = true;
    int counter = 0;
    struct _Record rec;
   
    char *array[5];
    // int numberOfBuffer = 5;
    // int pageSize = 8;
    int bufferIndex = 0;
    int numberOfRecordToAdd = getNumbOfRecordToAdd(pageSize);
    struct _Record arr_rec[numberOfRecordToAdd];
    int chunkIdx=0;

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
            //<----------- Replacement Selection Sort -------------->
            // create node for heap
            struct node node;
            node.record = rec;
            insertNode(&heap,node);
            counter += 1;
            
            if(counter % (numberOfRecordToAdd) == 0){
                counter = 0;
                writeRSortedToBuffer(bufferIndex,&heap,numberOfRecordToAdd);
                bufferIndex += 1;
                if(bufferIndex == numberOfBuffer){
                    createChunk(numberOfBuffer,chunkIdx);
                    chunkIdx += 1;
                    bufferIndex = 0;     
                }
            }  
            //printf("%d %s %s %s %d",rec.id,rec.name,rec.surname,rec.email,rec.grade);
			//printf("\n");   
		 }
		fclose(fp);
		fp = NULL;
        createSortedFile(chunkIdx,outputFileName);
    }
}

int main(){
    readCSV("students.csv","sortedFile.txt",5,32);
    return -1;
}
