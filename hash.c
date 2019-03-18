#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

//Declaring structs
struct node {
    struct node *next;
    char *data;
    char *key;
};
typedef struct node node;

struct hashTable {
    int size;
    int count;
    node **array;
};
typedef struct hashTable hashTable;

//Creates new hash table of specified size by the user
hashTable *newHash(int size) {

    hashTable *newHash = malloc(sizeof(hashTable));
    newHash->size = size;
    newHash->count = 0;
    newHash->array = calloc((size_t)newHash->size, sizeof(node*));

    return newHash;
}

//Creates a new node for the hash table
node *newNode(char *data, char *key) {
    node *newNode = malloc(sizeof(node));
    *newNode = (node) {NULL, data, key};

    return newNode;
}

//Frees the hash table of memory
void freeHash(hashTable *h){
    node *temp;
    node *next;
    for(int i = 0; i < h->size; i++){
      for (temp = h->array[i]; temp!= NULL; temp = next){
        next = temp->next;
        free(temp);
        temp = next;
      }
    }
    free(h->array);
    free(h);
}

//Java hash function to determine where the data is to be inserted
int hashFunction (const char *key, hashTable *h){
    unsigned long hash = 1;
    int size = strlen(key);
    for (int i = 0; i < size; i++){
      hash = 31 * hash + key[i];
    }
    return (hash % h->size);
}

//Checks if the linked list in the hash table is empty
bool isEmpty(hashTable *hash, int index) {
    if(hash->array[index] == NULL) return true;
    return false;
}

//Checks if hash table has a load factor that is too big
bool checkSize(hashTable *hash) {
    if(hash->count >= hash->size * 0.7) return true;
    return false;
}

//Doubles the size of the hash table
void increaseSize(hashTable *hash) {
    int newsize = hash->size * 2;
    rehash(hash, newsize);
}

//Inserts new node into the hash table, checks if the load factor
//is too high after insertion and increases size if necessary
void insert(hashTable *hash, char *key, char *data) {
    int index = hashFunction(key, hash);

    node *new = newNode(data, key);
    if (isEmpty(hash, index) == true) {
        hash->count++;
        hash->array[index] = new;
    }
    else {
        while(hash->array[index]->next != NULL) {
          hash->array[index] = hash->array[index]->next;
        }
        hash->array[index]->next = new;
        hash->count++;
    }

    if(checkSize(hash) == true) increaseSize(hash);

}

//Finds the specified data value in the hash table
char *find(hashTable *hash, char *key) {
    int index = hashFunction(key, hash);
    node *temp = hash->array[index];
    while (temp != NULL) {
        if(strcmp(key, temp->key) == 0) {
            printf("The data is %s\n", temp->data);
            return temp->data;
        }
        temp = temp->next;
    }
    printf("The %s key has no data\n", key);
    return NULL;
}

//Deletes a node from the hash table
void del(hashTable *hash, char *key) {
    int index = hashFunction(key, hash);
    node *delNode = hash->array[index];
    node *temp = delNode;
    node *prev;

    if(delNode == NULL) {
        printf("This key is empty\n");
        return;
    }
    while(temp != NULL && strcmp(key, temp->key) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    hash->count--;
    prev->next = temp->next;
    free(temp);

}

//Rehashes the hash table once the size is increased
void rehash(hashTable *hash, int size) {
    hashTable *new = newHash(size);

    for(int i = 0; i < hash->size; i++) {
      for(node *temp = hash->array[i]; temp != NULL; temp = temp->next) {
        insert(new, temp->key, temp->data);
      }
    }
    hash->size = new->size;
    hash->array = new->array;

}

//Prints out the hash table's values
void printHash(hashTable *hash) {

    for(int i = 0; i < hash->size; i++) {
        node *temp = hash->array[i];
        if (temp == NULL) printf("Array %d has no elements\n", i);
        else {
            printf("The array %d has these elements: \n", i);
            while (temp != NULL) {
                printf("%s\n", temp->data);
                temp = temp->next;
            }
        }
    }
}

void tests(){
    testHF();
    testInsert();
    testFind();
    testPrint();
    testRehash();
    printf("Module Successful\n");
}

void testHF(){
    hashTable *h = newHash(8);
    assert(hashFunction("31", h) == 7);
    assert(hashFunction("32", h) == 0);
    assert(hashFunction("33", h) == 1);
    assert(hashFunction("34", h) == 2);
    assert(hashFunction("35", h) == 3);
    freeHash(h);
    hashTable *s = newHash(16);
    assert(hashFunction("31", s) == 15);
    assert(hashFunction("32", s) == 0);
    assert(hashFunction("33", s) == 1);
    freeHash(s);
}

void testInsert(){
    hashTable *h = newHash(8);
    insert(h, "35","C");
    assert(strcmp(h->array[hashFunction("35", h)]->data, "C")==0);
    insert(h, "37","Is");
    assert(strcmp(h->array[hashFunction("37", h)]->data, "Is")==0);
    insert(h, "42","Better");
    assert(strcmp(h->array[hashFunction("42", h)]->data, "Better")==0);
    insert(h, "54","Than");
    assert(strcmp(h->array[hashFunction("54", h)]->data, "Than")==0);
    insert(h, "55","Haskell");
    assert(strcmp(h->array[hashFunction("55", h)]->data, "Haskell")==0);
    insert(h, "58","!!!");
    assert(strcmp(h->array[hashFunction("58", h)]->data, "!!!")==0);
    freeHash(h);
}

void testFind(){
    hashTable *h = newHash(8);
    insert(h, "35","C");
    insert(h, "37","Is");
    insert(h, "42","Better");
    insert(h, "54","Than");
    insert(h, "55","Haskell");
    assert(strcmp(find(h, "35"), "C") == 0);
    assert(strcmp(find(h, "37"), "Is") == 0);
    assert(strcmp(find(h, "42"), "Better") == 0);
    assert(strcmp(find(h, "54"), "Than") == 0);
    assert(strcmp(find(h, "55"), "Haskell") == 0);
    assert(find(h,"57")== NULL);
    assert(find(h,"58")== NULL);
    freeHash(h);
}

void testPrint(){
    hashTable *h = newHash(8);
    insert(h, "35","C");
    printHash(h);
    insert(h, "37","Is");
    printHash(h);
    insert(h, "42","Better");
    printHash(h);
    insert(h, "54","Than");
    printHash(h);
    insert(h, "55","Haskell");
    printHash(h);
    insert(h, "59","!!!");
    printHash(h);
    find(h, "35");
    find(h, "37");
    find(h, "42");
    find(h, "54");
    find(h, "55");
    find(h, "59");
    freeHash(h);
}

void testRehash(){
    hashTable *h = newHash(8);
    insert(h, "35","C");
    insert(h, "32","Is");
    insert(h, "42","Better");
    insert(h, "53","Than");
    insert(h, "55","Haskell");
    assert(h->size == 8);
    insert(h, "57","!!!");
    assert(h->size == 16);
    freeHash(h);
}

int main() {
    tests();
    return 0;
}
