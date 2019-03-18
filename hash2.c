#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash2.h"


//NEW STRUCTURES
//New node
Node *newNode(char *data, char *key){
  Node *new = malloc(sizeof(Node));
  new->next = NULL;
  new->data = data;
  new->key = key;
  return new;
}

//New hash table
HashTable *newHash(int size){
  HashTable *h = malloc(sizeof(HashTable));
  h->size = size;
  h->count = 0;
  h->array = calloc(h->size, sizeof(Node));
  return h;
}

//Free hash table
void freeHash(HashTable *h){
  int i;
  Node *temp;
  Node *next;
  for(i=0;i < h->size;i++){
    for (temp = h->array[i]; temp!= NULL; temp = next){
      next = temp->next;
      free(temp);
      temp = next;
    }
  }
  free(h->array);
  free(h);
}

//Hash Function
int HashFunction (const char *key, HashTable *h){
  unsigned long hash = 1;
  int size = strlen(key);
  for (int i = 0; i < size; i++){
    hash = 31*hash + key[i];
  }
  return (hash % h->size);
}

//Checks if the current linked list in the array is empty
bool ListEmpty(HashTable *h, int index){
  if(h->array[index] == NULL) return true;
  return false;
}

//Finds the index for where the data is in the linked list.
int getIndex(HashTable *h, int index, char *key){
  Node *temp = h->array[index];
  int listIndex = 0;
  while (temp != NULL){
    if(strcmp(temp->key,key)==0) return listIndex;
    temp = temp->next;
    listIndex++;
  }
  return -1;
}

//Returns the node given an index in an array and a index in a list.
Node *getNode(HashTable *h, int listIndex,int index){
  Node *temp =h->array[index];
  for (int i = 0 ; i < listIndex; i++){
    temp = temp->next;
  }
  return temp;
}

/*Inserts a new element in the hash table, checks if the linked
list is empty or if the list already has that key already in it
, if so replace the data with the new data coming in*/
void insert(HashTable *h, char *key, char *ch){
  int index = HashFunction(key, h);
  Node *new = newNode(ch, key);
  int listIndex = getIndex(h, index, key);
  if (ListEmpty(h, index)==true){
    h->array[index]=new;
    ++h->count;
  }
  else if(listIndex != -1){
      Node *node = getNode(h, listIndex, index);
      node->data = ch;
    }
  else{
    Node *nextNode = h->array[index]->next;
    h->array[index]->next = new;
    new->next = nextNode;
    ++h->count;
  }
  if(h->count >= h->size * 0.7){
    increaseSize(h);
  }
}

//Prints the data of a given key.
char *search(HashTable *h, char *key){
  int index = HashFunction(key, h);
  Node *temp = h->array[index];
  while (temp != NULL){
    if (strcmp(temp->key,key)==0){
      printf("The data at key: %s is %s\n",key, temp->data);
      printf("\n\\");
      return temp->data;
    }
    temp = temp->next;
  }
  printf("There is no data with key: %s\n", key);
  printf("\n\\");
  return NULL;
}

/*Deletes a node with the key. Checks where the node is in the
list and treats it accordingly*/
void delete(HashTable *h, char *key){
  int index = HashFunction(key, h);
  Node *node = h->array[index];
  Node *temp = node;
  if(node == NULL){
    printf("This key has no data\n");
    return;
  }
  while(node!=NULL){
    if (strcmp(node->key, key)==0){
      if (node == h->array[index]){
        h->array[index] = node->next;
      }
      else {
        temp->next = node->next;
      }
      h->count--;
      printf("Deleting entry with key: %s\n", key);
      free(node);
      break;
    }
    temp = node;
    node = node->next;
  }
  printf("\n\\");
}

//Doubles the size of the table
void increaseSize(HashTable *h){
  int newSize = h->size *2;
  rehash(h, newSize);
}

/*Creates a new hash table with double the size, copies over elements
from old table and then switch elements so old table has double the size*/
void rehash(HashTable *h, int newSize){
  HashTable *temp = newHash(newSize);
  Node *t;
  for (int i = 0; i<h->size; i++){
    for (t = h->array[i]; t != NULL; t = t->next){
      insert(temp, t->key, t->data);
    }
  }
  h->size = temp->size;
  h->count = temp->count;
  Node** temparray = h->array;
  h->array = temp->array;
  temp->array = temparray;
  freeHash(temp);
}

//Prints the value(s) and key(s) of each index in the hash table
void printHash(HashTable *h){
  int i = 0;
  printf("New print sequence:\n");
  for (i = 0; i < h->size; i++){
    Node *temp = h->array[i];
    if (temp == NULL){
      printf("array[%d] has no elements\n", i);
    }
    else{
      printf("array[%d] has elements-: ", i);
      while (temp != NULL){
        printf("key= %s, value= %s ",temp->key, temp->data);
        temp = temp->next;
      }
      printf("\n");
    }
  }
  printf("\n\\");
}

void test(){
  testHF();
  testGetIndex();
  testInsert();
  testSearch();
  testDelete();
  testRehash();
  testPrint();
  printf("All tests pass\n");
}

void testHF(){
  HashTable *h = newHash(8);
  assert(HashFunction("31", h) == 7);
  assert(HashFunction("32", h) == 0);
  assert(HashFunction("33", h) == 1);
  assert(HashFunction("34", h) == 2);
  assert(HashFunction("35", h) == 3);
  freeHash(h);
  HashTable *s = newHash(5);
  assert(HashFunction("31", s) == 1);
  assert(HashFunction("32", s) == 2);
  assert(HashFunction("33", s) == 3);
  freeHash(s);
}

void testGetIndex(){
  HashTable *h = newHash(8);
  insert(h, "31","I");
  insert(h, "32","Wish");
  insert(h, "43","You");
  insert(h, "53","A");
  insert(h, "54","Merry");
  assert(getIndex(h, 0, "32") == 0);
  assert(getIndex(h, 0, "54") == 1);
  assert(getIndex(h, 0, "43") == 2);
  assert(getIndex(h, 7, "31") == 0);
  assert(getIndex(h, 7, "53") == 1);
  freeHash(h);
}

void testInsert(){
  HashTable *h = newHash(8);
  insert(h, "31","I");
  assert(strcmp(h->array[HashFunction("31", h)]->data, "I")==0);
  insert(h, "32","Wish");
  assert(strcmp(h->array[HashFunction("32", h)]->data, "Wish")==0);
  insert(h, "43","You");
  assert(strcmp(h->array[HashFunction("43", h)]->next->data, "You")==0);
  insert(h, "53","A");
  assert(strcmp(h->array[HashFunction("53", h)]->next->data, "A")==0);
  insert(h, "54","Merry");
  assert(strcmp(h->array[HashFunction("54", h)]->next->data, "Merry")==0);
  assert(strcmp(h->array[HashFunction("43", h)]->next->next->data, "You")==0);
  insert(h, "57","Xmas");
  //Test for rehash in insert function. Notice index changes from 7 to 15;
  assert(getIndex(h, 15, "31") == 0);
  assert(getIndex(h, 15, "53") == 1);
  freeHash(h);
}

void testSearch(){
  HashTable *h = newHash(8);
  insert(h, "31","I");
  insert(h, "32","Wish");
  insert(h, "43","You");
  insert(h, "53","A");
  insert(h, "54","Merry");
  assert(strcmp(search(h, "31"), "I") == 0);
  assert(strcmp(search(h, "32"), "Wish") == 0);
  assert(strcmp(search(h, "43"), "You") == 0);
  assert(strcmp(search(h, "53"), "A") == 0);
  assert(strcmp(search(h, "54"), "Merry") == 0);
  assert(search(h,"57")== NULL);
  assert(search(h,"58")== NULL);
  freeHash(h);
}

void testDelete(){
  HashTable *h = newHash(8);
  insert(h, "31","I");
  insert(h, "32","Wish");
  insert(h, "43","You");
  insert(h, "53","A");
  insert(h, "54","Merry");
  delete(h, "31");
  assert(strcmp(h->array[HashFunction("31", h)]->data, "A")==0);
  delete(h, "32");
  assert(strcmp(h->array[HashFunction("32", h)]->data, "Merry")==0);
  delete(h, "43");
  assert(strcmp(h->array[HashFunction("32", h)]->data, "Merry")==0);
  delete(h, "53");
  assert(h->array[HashFunction("53", h)]== NULL);
  delete(h, "54");
  assert(h->array[HashFunction("54", h)] == NULL);
  freeHash(h);
}

void testRehash(){
  HashTable *h = newHash(10);
  insert(h, "31","I");
  insert(h, "32","Wish");
  insert(h, "43","You");
  insert(h, "53","A");
  insert(h, "54","Merry");
  insert(h, "57","Xmas");
  assert(h->size == 10);
  insert(h, "58","I");
  assert(h->size == 20);
  freeHash(h);
}

void testPrint(){
  HashTable *h = newHash(8);
  insert(h, "31","OSX");
  printHash(h);
  insert(h, "32","Windows");
  printHash(h);
  insert(h, "43","LINUX");
  printHash(h);
  insert(h, "33","BeOS");
  printHash(h);
  insert(h, "34","MS-DOS");
  printHash(h);
  insert(h, "54","IRIX");
  printHash(h);
  search(h, "31");
  search(h, "32");
  search(h, "33");
  search(h, "34");
  search(h, "43");
  search(h, "54");
  delete(h, "32");
  printHash(h);
  delete(h, "33");
  printHash(h);
  delete(h, "34");
  printHash(h);
  delete(h, "31");
  printHash(h);
  delete(h, "43");
  printHash(h);
  delete(h, "54");
  printHash(h);
  freeHash(h);
}

int main(){
  test();
  return 0;
}
