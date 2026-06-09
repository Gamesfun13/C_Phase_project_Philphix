

#include "hashtable.h"
#include <ctype.h>
/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * String utility routines.
 */
#include <string.h>


/*
 * This creates a new hash table of the specified size and with
 * the given hash function and comparison function.
 */
HashTable *createHashTable(int size, unsigned int (*hashFunction)(void *),int (*equalFunction)(void *, void *)) {
  int i = 0;
  HashTable *newTable = malloc(sizeof(HashTable));
  if (NULL == newTable) {
    fprintf(stderr, "malloc failed \n");
    exit(1);
  }
  newTable->size = size;
  newTable->buckets = malloc(sizeof(struct HashBucketEntry *) * size);
  if (NULL == newTable->buckets) {
    fprintf(stderr, "malloc failed \n");
    exit(1);
  }
  for (i = 0; i < size; i++) {
    newTable->buckets[i] = NULL;
  }
  newTable->hashFunction = hashFunction;
  newTable->equalFunction = equalFunction;
  return newTable;
}

/* Task 1.2 */
void insertData(HashTable *table, void *key, void *data) {
  // -- TODO --
  // HINT:
  /// 1. Find the right hash bucket location with table->hashFunction.

  int bucketPosition=table->hashFunction(key) % table->size;
  /// 2. Allocate a new hash bucket entry struct.
  struct HashBucketEntry * N=(struct HashBucketEntry *) malloc(sizeof(struct HashBucketEntry));
  N->key=key;
  N->data=data;
  N->next=NULL;
  /// 3. Append to the linked list or create it if it does not yet exist.
  struct HashBucketEntry **head=&(table->buckets[bucketPosition]);
    
 //if head is NULL, it is an empty list
  if(*head == NULL)
       *head = N;
  //Otherwise, find the last node and add the newNode
  else
  {
      struct HashBucketEntry *lastNode = *head;

      //if the key/data pair is present in bucket
      if(table->equalFunction(lastNode->key,key) && table->equalFunction(lastNode->data,data))
        return;
      //last node's next address will be NULL.
      while(lastNode->next != NULL)
      {

        lastNode = lastNode->next;
        //if the key/data pair is present in bucket
        if(table->equalFunction(lastNode->key,key) && table->equalFunction(lastNode->data,data))
          return;
      }

      //add the newNode at the end of the linked list
      lastNode->next = N;
  }



  //insertAtBuckketPos(N,head);
}


void * searchElement (struct HashBucketEntry *head, void * key)
{
  struct HashBucketEntry *current = head;	// Initialize current

  // traverse till then end of the linked list
  while (current != NULL)
    {
      if (current->key == key)
        {
        return current;
        }
      current = current->next;
    }
  return NULL;
}

/* Task 1.3 */
void *findData(HashTable *table, void *key) {
  // -- TODO --
  // HINT:
  // 1. Find the right hash bucket with table->hashFunction.

    int bucketPosition=table->hashFunction(key) % table->size;
  // 2. Walk the linked list and check for equality with table->equalFunction.
    struct HashBucketEntry *current = table->buckets[bucketPosition];
    while (current != NULL)
    {
        if((table->equalFunction(current->key,key)))
            return current->data;
      current = current->next;
    }

return NULL;

}

/* Task 2.1 */
unsigned int stringHash(void *s) {
  // -- TODO --
  //fprintf(stderr, "need to implement stringHash\n");
  /* To suppress compiler warning until you implement this function, */
  unsigned int hashcode=0;
  //jenkin hash algo

   int length =strlen((char *)s);
    for (int i = 0; i < length; i++) {
        hashcode += ((unsigned char *)s)[i];
        hashcode += (hashcode << 10);
        hashcode ^= (hashcode >> 6);
    }
    hashcode += (hashcode << 3);
    hashcode ^= (hashcode >> 11);
    hashcode += (hashcode << 15);

  return hashcode;
}

/* Task 2.2 */
int stringEquals(void *s1, void *s2) {
  // -- TODO --
    //fprintf(stderr, "You need to implement stringEquals");
  /* To suppress compiler warning until you implement this function */

    if(!strcmp((char *)s1,(char *)s2))
      return 1;

return 0;
}

