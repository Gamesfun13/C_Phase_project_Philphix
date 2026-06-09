

/*
 * Include the provided hash table library.
 */
#include "hashtable.h"

/*
 * Include the header file.
 */
#include "philphix.h"

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Character utility routines.
 */
#include <ctype.h>

/*
 * String utility routines.
 */
#include <string.h>



/*
 * This hash table stores the dictionary.
 */
HashTable *dictionary;

/*
 * The MAIN routine.  You can safely print debugging information
 * to standard error (stderr) as shown and it will be ignored in
 * the grading process.
 */
#ifndef _PHILPHIX_UNITTEST
int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Specify a dictionary\n");
    return 1;
  }
  /*
   * Allocate a hash table to store the dictionary.
   */
  fprintf(stderr, "Creating hashtable\n");
  dictionary = createHashTable(0x61c, &stringHash, &stringEquals);
  

  fprintf(stderr, "Loading dictionary %s\n", argv[1]);
  readDictionary(argv[1]);
  fprintf(stderr, "Dictionary loaded\n");

  fprintf(stderr, "Processing stdin\n");
  processInput();

  /*
   * The MAIN function in C should always return 0 as a way of telling
   * whatever program invoked this that everything went OK.
   */
  return 0;
}
#endif /* _PHILPHIX_UNITTEST */

/* Task 3 */
void readDictionary(char *dictName) {
  // -- TODO --
  //fprintf(stderr, "You need to implement readDictionary\n");

    FILE *fileptr;
    if((fileptr=fopen(dictName,"r"))==NULL)
    {
        printf("Error1 file Not opened");
        exit(61);
    }

    
    char c;
    while(1)
    {

        while(((c=fgetc(fileptr))==' ' || c=='\t') && !feof(fileptr));
        int count=0;
        //c=fgetc(fileptr);
        while(c!=EOF && c!=' ' && c!='\t' )
        {
            count++;
            c=fgetc(fileptr);
        }
        char * keyStr=NULL;
        if (count)
        {
          keyStr=(char *) malloc((count+1)*sizeof(char));
        fseek(fileptr,-count-1,SEEK_CUR);
        fscanf(fileptr,"%s",keyStr);
        }
        
        while(((c=fgetc(fileptr))==' ' || c=='\t') && !feof(fileptr));
        count=0;
       
        while(c!=EOF && c!=' ' && c!='\t' )
        {
            count++;
            c=fgetc(fileptr);
        }
        char * dataStr=NULL;
        if(count)
        {
        dataStr=(char *) malloc((count+1)*sizeof(char));
        fseek(fileptr,-count-1,SEEK_CUR);
        fscanf(fileptr,"%s",dataStr);

        }

        if(keyStr!=NULL && dataStr!=NULL)
        insertData(dictionary,keyStr,dataStr);

      if(c==EOF)
          break;

     }
fclose(fileptr);
}

/* Task 4 */
void processInput() {
  // -- TODO --
  //fprintf(stderr, "You need to implement processInput\n");

  while(1)
  {
        
    int size=10000;
    char c;
    int count=0;
    char *array=malloc(sizeof(char)*size);

    while(  (c=fgetc(stdin))==' ' && c=='\t' && !feof(stdin))
      printf("%c",c );
    if(feof(stdin))
        break;

    while(c!=EOF  && isalnum(c))
    {
        
        array[count]=c;
        count++;
        if (count ==size)
          array=realloc(array,size+=10000);
        if(array==NULL)
          exit(62);
        c=fgetc(stdin);
    }

    array[count]='\0';

    char * keyStr=(char *) malloc((count+1)*sizeof(char));
    keyStr=strcpy(keyStr,array);
    //fseek(stdin,-count-1,SEEK_CUR);
    //fscanf(stdin,"%s",keyStr);
    struct HashBucketEntry* find;


    #ifdef VAR1
    if((find=variation1(dictionary,array))!=NULL)
    {  
        
        printf("%s",(char *)find);
        if (c!=EOF)
        printf("%c",c );
        
    }
    #endif

    #ifdef VAR2
    if((find=variation2(dictionary,array))!=NULL)
    {  
        
        printf("%s",(char *)find);
        if (c!=EOF)
        printf("%c",c );
        
    }
    #endif
    else
    {
        
        printf("%s",keyStr);
        if (c!=EOF)
        printf("%c",c );
        
    }
      
  }
}


void *variation1(HashTable * dict, void * key)
{


 char *target=malloc(sizeof(char)*(strlen(key)+1));
 target= strcpy(target,(char *)key);
 void * foundData;
  for (int i = 0; i < 3; ++i)
  {

    if((foundData=findData(dict,target))!=NULL)
      return foundData;
    if(i==0)
    mylowerCase(target+1);
    if(i==1)
    mylowerCase(target);


  }
  return NULL;
    
}



void *variation2(HashTable * dict, void * key)
{


 char *target=malloc(sizeof(char)*(strlen(key)+1));
 target= strcpy(target,(char *)key);
 void * foundData;
  for (int i = 0; i < 3; ++i)
  {

    if((foundData=findData(dict,target))!=NULL)
      return foundData;
    if(i==0)
    myupperCase(target);
    if(i==1)
    {
      target=realloc(target,sizeof(char)*(strlen(key)+2));
      if(strlen(key)==0)
        strcpy(target,"1");
      else
      strcpy(target,"1");
      strcat(target,key);

    }
  

  }
  return NULL;
    
}



//convert String into lowercase
int  mylowerCase(char *str)
{
  int length=strlen(str);
  if (length==0)
    return 0;

  for (int i = 0; i<length; ++i)
  {
    if(*(str+i)<65 || *(str+i)>90)
        continue;
    if(!(*(str+i)>=97 && *(str+i)<=122))
      *(str+i)+=32;
  }
return 1;

}

//convert String into uppercase
int myupperCase(char *str)
{
  int length=strlen(str);
  if (length==0)
    return 0;


  for (int i = 0; i<length; ++i)
  {
    if(*(str+i)<97 || *(str+i)>122)
      continue;
    if(!(*(str+i)>=65 && *(str+i)<=90))
      *(str+i)-=32;
  }
return 1;

}