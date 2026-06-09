#ifndef _PHILPHIX_H
#define _PHILPHIX_H

/* The pointer to store the dictionary for replacement entries */
extern struct HashTable *dictionary;

extern void readDictionary(char *dictName);

extern void processInput();

void *variation1(HashTable * dict, void * key);


void *variation2(HashTable * dict, void * key);

int myupperCase(char *str);

int mylowerCase(char *str);

#endif /* _PHILPHIX_H */
