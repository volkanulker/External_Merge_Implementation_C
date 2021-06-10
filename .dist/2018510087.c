#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <heap.h>
#include <stdbool.h>
#include "heap.h";

#define MY_BUFFER_SIZE sizeOf(record)

struct _Record
{
    int id;
    char name[15];
    char surname[15];
    char email[26];
    int grade;
};

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


int writeToBuffer(int indexOfBuffer, struct _Record arr_rec[], int sizeOfArray){
   
    char *fileName;
    sprintf(fileName,"buffer%d.bin",indexOfBuffer);
    FILE *fp = fopen(fileName, "wb");
    if (fp != NULL) {
        int i=0;
        for (i = 0; i < sizeOfArray; i++)
        {
            fwrite(&arr_rec[i], sizeof(struct _Record), 1, fp);
        }
        
       
        fclose(fp);
    }

}

int readFromABuffer(char* fileName){
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


int readCSV(char* fileName){
    
    FILE *fp = NULL;
	char *line,*splitted;
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

    // heap *my_heap = malloc(sizeof(heap));
    // heap_init(my_heap);

	if ((fp = fopen(fileName, "at+")) != NULL)
	{
		 while ((line = fgets(lineBuffer, sizeof(lineBuffer), fp))!=NULL)//The loop continues when the end of the file is not read
		{
            // if reader reads first line skip that line
            if(isFirstLine){
                isFirstLine = false;
                continue;
            }
			splitted = strtok(line, ";");
            int i=0;
			while (splitted != NULL)//Read the data of each row
			{
                array[i++] = splitted;
				//printf("%s ", splitted);//Print out every data read
				splitted = strtok(NULL, ";");
			}
            
            // Read into _Record rec
            rec.id = atoi(array[0]);
            strcpy(rec.name,array[1]);
            strcpy(rec.surname,array[2]);
            strcpy(rec.email,array[3]);
            rec.grade = atoi(array[4]);
            // Add records to record array
            arr_rec[counter % numberOfRecordToAdd] = rec;

            // Create multi index
            multiIndex.id = rec.id;
            multiIndex.index = counter;
            counter += 1;
            if(counter % numberOfRecordToAdd == 0){
                printf("%s","test");
                writeToBuffer(1,arr_rec,numberOfRecordToAdd);
                bufferIndex += 1;
                if(bufferIndex == 4){
                    bufferIndex = 0;
                }
                
                
            }
            
            //printf("%d %s %s %s %d",rec.id,rec.name,rec.surname,rec.email,rec.grade);
            

			printf("\n");
            
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

    //readFile("students1.csv");
    //readCSV("students1.csv");
    readCSV("students1.csv");
    readFromABuffer("buffer1.bin");
    return 0;

}








