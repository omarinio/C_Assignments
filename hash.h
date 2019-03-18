#include <stdbool.h>


struct node;
typedef struct node node;

struct hashTable;
typedef struct hashTable hashTable;

hashTable *newHash(int size);
node *newNode(char *data, char *key);
void freeHash(hashTable *h);
int hashFunction (const char *key, hashTable *h);
bool isEmpty(hashTable *hash, int index);
bool checkSize(hashTable *hash);
void increaseSize(hashTable *hash);
void insert(hashTable *hash, char *key, char *data);
char *find(hashTable *hash, char *key);
void del(hashTable *hash, char *key);
void rehash(hashTable *hash, int size);
void printHash(hashTable *hash);

void tests();
void testHF();
void testGetIndex();
void testInsert();
void testFind();
void testRehash();
void testPrint();
