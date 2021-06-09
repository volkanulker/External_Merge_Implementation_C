#include <stdio.h> //standart buffered input/output
#include <string.h> //string operations
#include <stdbool.h> //for Boolean type and values
#include <stdlib.h> //standart library definitions
#include <time.h>

#define RECORD_COUNT 10

struct _Person {
    char name[22];
    char ID[10];
    int score1;
    int score2;
    int score3;
};
typedef struct _Person Person;

typedef struct _SearchData
{
    Person personData;
    int index;
} SearchData;

int personNumber;


// if first input greater than second input than returns positive
// else if inputs are equal returns 0
// if second inout lower than first one returns negative
int comparePersons(const void* a, const void* b){
    return (strcmp(((Person*)a)->ID, ((Person*)b)->ID)); 
}

float avg(const Person p){
    return (p.score1+p.score2+p.score3)/3.0;
}

void generateRandomString(char* target, char* dictionary, int maxLength, int minLength){
    int length = minLength + rand()%(maxLength-minLength);
    int dictLength = strlen(dictionary);
    int i;
    for(i=0; i<length; i++){
        int dictIdx = rand()%dictLength;
        target[i] = dictionary[dictIdx];
    }
}

void generatePerson(Person* person){
    generateRandomString(person->name, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 22, 5);
    generateRandomString(person->ID,"0123456789",10,9);
    person->score1 = rand()%101;
    person->score2 = rand()%101;
    person->score3 = rand()%101;
    printf("name is %s, id is %s, score1 is:%d, score2 is:%d, score3 is:%d \n", person->name, person->ID, person->score1, person->score2, person->score3);
}

void generateRandomSortedDataFile(){
    srand(time(NULL)); //seed simple pseudo-random number generator
    FILE* fp;
    fp = fopen("randomdata.dat", "wb"); //open a stream in wb mode
    if(!fp)
        return;
    Person person[RECORD_COUNT];
    int i;
    for(i=0; i<RECORD_COUNT; i++){
        generatePerson(&person[i]);
    }
    
    qsort(person, RECORD_COUNT, sizeof(Person), comparePersons); //sort a table of data
    //inital element,sort an array of RECORD_COUNT objects, the size of each object, the comparison function
    
    printf("Writing %d bytes. \n", sizeof(Person)*RECORD_COUNT);
        
    fseek(fp, 0, SEEK_SET); //reposition a file position indicator in a stream
    fwrite(person, sizeof(Person), RECORD_COUNT, fp); //binary output
    fclose(fp); //close a stream

}

SearchData binaryFileSearch(FILE* fp, const char ID[], int firstIdx, int lastIdx){
    printf("Running Binary Search %d %d\n", firstIdx, lastIdx);
    Person first, last, middle;
    SearchData returnData;
    
    int middleIdx = (firstIdx+lastIdx)/2;
    // Read first record and return if it is the searched one.
    fseek(fp, firstIdx*(sizeof(Person)), SEEK_SET);
	fread(&first, sizeof(Person), 1, fp);
    if(strcmp(first.ID,ID) == 0)
    {
        returnData.personData = first;
        returnData.index = firstIdx;
        return returnData;
    }
    // Read last record and return if it is the searched one.
    fseek(fp, lastIdx*sizeof(Person), SEEK_SET);
	fread(&last, sizeof(Person), 1, fp);
    if(strcmp(last.ID,ID) == 0)
    {
        returnData.personData = last;
        returnData.index = lastIdx;
        return returnData;
    }
    // Recursion exit condition, If middle index is equal to first or last index
    // required comparisons are already made, so record is not found.
    // Create and return an empty person.
    if(middleIdx==firstIdx || middleIdx == lastIdx) {
        printf("The record is not found\n");
        SearchData d;
        return d;
    }

    // Read the middle record and return if it is the searched one.
    fseek(fp, middleIdx*sizeof(Person), SEEK_SET);
	fread(&middle, sizeof(Person), 1, fp);
    if(strcmp(middle.ID,ID) == 0)
    {
        returnData.personData = middle;
        returnData.index = middleIdx;
        return returnData;
    }
    // Determine the record position and recursively call with appropriate attributes.
    if(strcmp(middle.ID,ID)>0) {
		return binaryFileSearch(fp, ID, firstIdx+1, middleIdx-1);
	} 
	else {
		return binaryFileSearch(fp, ID, middleIdx+1, lastIdx-1);
	}
}

SearchData findRecordByID(char ID[]) {
    // Open the file
    FILE* inputFile;
    inputFile = fopen("randomdata.dat", "rb");

    // Calculate initial first and last indexes.
    int firstIdx = 0;    
    fseek(inputFile,0,SEEK_END);
    int lastIdx = (ftell(inputFile)/sizeof(Person))-1;

    // Initiate the search.
    SearchData result = binaryFileSearch(inputFile, ID, firstIdx, lastIdx);
    fclose(inputFile);
    return result;
}

void printFile()
{
    printf("personNumber: %d\n", personNumber);
    FILE* inputFile;
    inputFile = fopen("randomdata.dat","rb");
    fseek(inputFile, 0, SEEK_SET);
    int i;        
    for(i=0;i<personNumber;i++)
    {
        Person bufferPerson;
        fread(&bufferPerson,sizeof(Person),1,inputFile);
        printf("name is %s, id is %s, score is:%f \n", bufferPerson.name, bufferPerson.ID, avg(bufferPerson));
    }
    fclose(inputFile);
}

void deleteRecordByID(SearchData *whoData) 
{
    // Open the file
    FILE* inputFile;
    inputFile = fopen("randomdata.dat", "rb+"); //open file for update (reading and writing)
    printf("----------------------- deletion\n");
    fseek(inputFile, (whoData->index)*sizeof(Person), SEEK_SET);
    int i;	
    for(i=whoData->index+1;i<personNumber;i++)
    {
        fseek(inputFile,sizeof(Person),SEEK_CUR);
        Person bufferPerson;
        fread(&bufferPerson,sizeof(Person),1,inputFile);
        fseek(inputFile,-(2*sizeof(Person)),SEEK_CUR);
        fwrite(&bufferPerson,sizeof(Person),1,inputFile);
    } 
    personNumber--;
    fclose(inputFile);
}

void printMenu(int* answer){

    //print the user menu
    printf("You can perform the following tasks: \n");
    printf("(1) Generate Sorted Random Data File \n");
    printf("(2) Find Record by ID \n");
    printf("(3) Delete Record by ID \n");
    printf("(4) List File Data \n");
    printf("-------------------------------------\n");
    printf("(5) Quit \n");
    printf("Please Select one... \n");
    scanf("%d",answer);
}

int main(){

    int answer;
    SearchData who;
    personNumber = RECORD_COUNT;
    
    ab:
    //print the user menu and read user answer
    printMenu(&answer);

    while(answer>5 || answer<1)
    {
        printf("\nEnter a valid choice by pressing ENTER key again");
        printMenu(&answer);
    }

    switch(answer)
    {
        case 1: generateRandomSortedDataFile();
            printFile();
            goto ab;
            break;
        case 2: printf("Enter the id that you want to search :");
            char id[10];
            scanf("%s", id);
            who = findRecordByID(id);            
            printf("---Person of interest--- \n name is: %s \n ID is: %s \n index is %d \n", who.personData.name, who.personData.ID,who.index);
            goto ab;
            break;
        case 3: printf("Enter the id that you want to delete:");
            char id2[10];
            scanf("%s", id2);
            //printFile();
            who = findRecordByID(id2);
            printf("----------------------------\n");
            //printFile();
            printf("Person %s with %s has been found in the list with index %d\n",who.personData.name,who.personData.ID,who.index);
            deleteRecordByID(&who);
            printf("after deletion---------------\n");            
            printFile();
            goto ab;
            break;
        case 4: printf("List of the sorted File \n");
            printFile();
            goto ab;
            break;    
        case 5: printf("Program is terminating \n");
            break;
    }
}
