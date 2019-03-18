#include <stdbool.h>

struct Node;
typedef struct Node Node;

struct HashTable;
typedef struct HashTable HashTable;

struct Node{
  Node *next;
  char *data;
  char *key;
};

struct HashTable{
  Node **array;
  int count;
  int size;
};
bool HashFull(HashTable *h);
bool HashEmpty(HashTable *h);
void increaseSize(HashTable *h);


void rehash(HashTable *h, int newSize);
void insert(HashTable *h, char *key, char *ch);

void test();
void testHF();
void testGetIndex();
void testInsert();
void testSearch();
void testDelete();
void testRehash();
void testPrint();
