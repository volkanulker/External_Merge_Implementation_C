#define _SVID_SOURCE
#include <stdio.h>
#include <string.h>

struct record {
    char name[64]; //utf16
    char surname[32]; //utf8
    char gender[1];
    char email[32];
    char phone_number[16];
    char address[32];
    char level_of_education[8];
    unsigned int income_level; // given little-endian
    unsigned int expenditure; // given big-endian
    char currency_unit[16];
    char currentMood[32];
    float height;
    unsigned int weight;

};

struct tag {
    char name[5];
    char surname[8];
    char gender[7];
    char email[10];
    char phone_number[13];
    char address[8];
    char level_of_education[19];
    char income_level[13];
    char expenditure[12];
    char currency_unit[14];
    char currentMood[12];
    char height[7];
    char weight[7];

};

/*
 * Converts big endian to little or little endian to big endian
 */
unsigned int endian_swap(unsigned int x)
{
    x = (x>>24) | 
        ((x<<8) & 0x00FF0000) |
        ((x>>8) & 0x0000FF00) |
        (x<<24);
        
    return x;
}

/*
 * Find uncorrect tag headers and fixed 
 */
struct tag rearrange_tag_names(struct tag t){
    struct tag *tagPtr;
    tagPtr = &t;
    // Check name header
    if(strcmp(t.name,"name") != 0) {
        strncpy(tagPtr->name,"name",5);
    }
     // Check surname header
    if(strcmp(t.surname,"surname") != 0) {
        strncpy(tagPtr->surname,"surname",8);
        
    }
     // Check gender header
    if(strcmp(t.gender,"gender") != 0) {
        strncpy(tagPtr->gender,"gender",7);
    }
    // Check email header
    if(strcmp(t.email,"email") != 0) {
        strncpy(tagPtr->email,"email",10);
    }
    // Check phone_number header
    if(strcmp(t.phone_number,"phone_number") != 0) {
        strncpy(tagPtr->phone_number,"phone_number",13);        
    }
    // Check address header
    if(strcmp(t.address,"address") != 0) {
        strncpy(tagPtr->address,"address",8);
    }
    // Check level_of_education header
    if(strcmp(t.level_of_education,"level_of_education") != 0) {
        strncpy(tagPtr->level_of_education,"level_of_education",20);
    }
    // Check income_level header
    if(strcmp(t.income_level,"income_level") != 0) {
        strncpy(tagPtr->income_level,"income_level",14);        
    }
    // Check expenditure header
    if(strcmp(t.expenditure,"expenditure") != 0) {
        strncpy(tagPtr->expenditure,"expenditure",12);
    }
    // Check currency_unit header
    if(strcmp(t.currency_unit,"currency_unit") != 0) {
        strncpy(tagPtr->currency_unit,"currency_unit",14);
    }
    // Check currentMood header
    if(strcmp(t.currentMood,"currentMood") != 0) {
        strncpy(tagPtr->currentMood,"currentMood",12);
    }
    // Check height header
    if(strcmp(t.height,"height") != 0) {
        strncpy(tagPtr->height,"height",7);
    }
    // Check weight header
    if(strcmp(t.weight,"weight") != 0) {
        strncpy(tagPtr->weight,"weight",7);
    }


    // print to test
    //printf("%s \t %s \t %s \t %s \t %s \t %s \t %s \t %s \t %s \t %s \t %s \t %s",t.name,t.surname,t.gender,t.email,t.phone_number,t.address,t.level_of_education,t.income_level,t.expenditure,t.currency_unit,t.currentMood,t.height,t.weight);
    return t;
}

/*
 * Creates XML from given records
 */
void createXML(struct record* arr,struct tag tag,char *xml_name)
{
    // Create file pointer
    FILE  *fxml;
    //Check if error is occured
    if ((fxml = fopen(xml_name,"wt")) == NULL) {    
        printf("%s","Some error is occured.");
                                          
    }


    fprintf (fxml,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
    fprintf(fxml,"<records>\n");
    int i;

    // Print tag to test
    //printf("%s",tag.email);
    //printf("%s",tag.level_of_education);
    // printf("%s",tag.level_of_education);
    // printf("%s",tag.income_level);
    // printf("%s",tag.expenditure);
    // printf("%s",tag.height);
    // printf("%s",tag.weight);
    
    // Crate xml rows
    for (i = 1; i < 51; i++) {
        
        fprintf(fxml,"   <row id='%d'>\n",i);
        fprintf(fxml,"       <%s>%s</%s>\n",tag.name,arr[i].name,tag.name);
        fprintf(fxml,"       <%s>%s</%s>\n",tag.surname,arr[i].surname,tag.surname);
        fprintf(fxml,"       <%s>%s</%s>\n",tag.gender,arr[i].gender,tag.gender);
        fprintf(fxml,"       <%s>%s</%s>\n",tag.email,arr[i].email,tag.email);
        fprintf(fxml,"       <%s>%s</%s>\n",tag.phone_number,arr[i].phone_number,tag.phone_number);
        fprintf(fxml,"       <%s>%s</%s>\n",tag.address,arr[i].address,tag.address);
        fprintf(fxml,"       <%s>%s</%s>\n",tag.level_of_education,arr[i].level_of_education,tag.level_of_education);
        fprintf(fxml,"       <%s>%d</%s>\n",tag.income_level,arr[i].income_level,tag.income_level);
        fprintf(fxml,"       <%s>%d</%s>\n",tag.expenditure,arr[i].expenditure,tag.expenditure);
        fprintf(fxml,"       <%s>%s</%s>\n",tag.currency_unit,arr[i].currency_unit,tag.currency_unit);
        fprintf(fxml,"       <%s>%s</%s>\n",tag.currentMood,arr[i].currentMood,tag.currentMood);
        fprintf(fxml,"       <%s>%.2f</%s>\n",tag.height,arr[i].height,tag.height);
        fprintf(fxml,"       <%s>%d</%s>\n",tag.weight,arr[i].weight,tag.weight);
        fprintf(fxml,"   </row>\n");
        
    }
    fprintf(fxml,"</records>\n");

    fclose(fxml); //Close file
}


/*
 * Converts bin file to XML
 */
int Bin2XML(char* rafname,char* xml_name)      
{
    // Create necessary variables
    FILE *fraf;
    struct record rec;
    struct tag tag;
    
    struct record arr_rec[50];
    int number_of_record = 51;


    // Encode file in utf-8 format
    if ((fraf = fopen(rafname,"rb, ccs=UTF-8")) == NULL)
        return 0;                                   // failure

    

    fread(&arr_rec, sizeof(struct record), number_of_record, fraf);

    // Read first line into tag and 
    // make necessary convertion and arrangement
    strcpy(tag.name,arr_rec[0].name);
    strcpy(tag.surname,arr_rec[0].surname);
    strcpy(tag.email,arr_rec[0].email);
    strcpy(tag.phone_number,arr_rec[0].phone_number);
    strcpy(tag.address,arr_rec[0].address);
    strcpy(tag.level_of_education,arr_rec[0].level_of_education);
    // convert int income level to string format
    char converted_income_level[10];
    sprintf(converted_income_level,"%d",arr_rec[0].income_level);
    strcpy(tag.income_level,converted_income_level);
    // convert int expenditure  to string format
    char converted_expenditure[10];
    sprintf(converted_expenditure,"%d",arr_rec[0].expenditure);
    strcpy(tag.expenditure,converted_expenditure);
    strcpy(tag.currency_unit,arr_rec[0].currency_unit);
    strcpy(tag.currentMood,arr_rec[0].currentMood);
    // convert float height  to string format
    char buf[10];
    snprintf(buf,5,"%s",arr_rec[0].height);
    
    strcpy(tag.height,buf);
    // convert unsigned weight to string format
    char converted_weight[10];
    sprintf(converted_weight,"%d",arr_rec[0].weight);
    strcpy(tag.weight,converted_weight);
    
    
    tag = rearrange_tag_names(tag);
   
    // Rearrange formats
    int i;
    for(i=1;i<number_of_record;i++){
        arr_rec[i].expenditure = endian_swap(arr_rec[i].expenditure); // Convert big endian to little endian
        // Income level is already little endian but if it was not little endian we can read as little endian
        // with endian_swap function.
        //arr_rec[i].income_level =endian_swap(arr_rec[i].income_level);    
        
        }

    // Create an XML file with readed records
    // First record readed into tag,so we can decrease number of record by one
    createXML(arr_rec,tag,xml_name);

    // close file
    fclose(fraf);
    
    return 1;                                       // success
}



int main(void)
{
    //Create input variables
    char input_file[50];
    char output_file[50];
    // Take inputs 
    printf( "Enter name of input file:");
    gets(input_file);
    printf( "Enter name of output file:");
    gets(output_file);


    // create XML file from .dat file
    if( Bin2XML(input_file,output_file)==1){
        printf("Bin file is readed and XML file is created successfully.");
    } else{
        printf("(!) An error occured please check your input file name. (!)");
    }

    return 0;
}


