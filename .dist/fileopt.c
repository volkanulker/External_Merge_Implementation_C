#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


struct _MultiIndex{
    int id;
    int index;
};



int main(){

    char *fileName = "test1.bin";
    struct _MultiIndex mIndex;
    mIndex.id = 555;
    mIndex.index = 0;
    // FILE *fp = fopen(fileName, "ab+");
    int i;
    for (i = 0; i < 5; i++)
    {
        writeToBuffer(1,mIndex);
    }
    
    writeToBuffer(1,mIndex);
    
    // if(fp != NULL) {
    //     fwrite(&mIndex, sizeof(struct _MultiIndex), 1, fp);
    //     fclose(fp);
    // } 
    
    // fclose(fp);
    FILE *fp;
    fp = fopen(fileName,"rb");
    struct _MultiIndex mIndexArr[5];
    if(fp != NULL){
        fread(&mIndexArr,sizeof(struct _MultiIndex),5,fp);
        
    }

    int k;
    for ( k = 0; k < 5; k++)
    {
        printf("%d %d \n",mIndexArr[k].id,mIndexArr[k].index);
    }
    
    

    return -1;
}


int writeToBuffer(int bufferIndex,struct _MultiIndex mIndex){
   
    char *fileName;
    sprintf(fileName,"test%d.bin",bufferIndex);
    FILE *fp = fopen(fileName, "ab+");
    if (fp != NULL) {
        fwrite(&mIndex, sizeof(struct _MultiIndex), 1, fp);
        fclose(fp);
    } 


}