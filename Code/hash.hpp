#ifndef HASH_HPP
#define HASH_HPP

#include <string>


using namespace std;

struct hashNode
{
    int key;
    struct hashNode* next;
};

class HashTable
{
    int tableSize;  // No. of buckets (linked lists)
    int collisionCount = 0;
    hashNode* chainingTable[40009]; //for chaining
    int intTable[40009]; //for open addressing


public:
    HashTable();  // Constructor
    unsigned int hashFunction(int trackingID); // hash function to map values to key
    hashNode* createNode(int trackingID); //allocates space for new node and sets key val
    //Collision Method: chaining with a linked list
    void chainingInsert(int trackingID);
    void chainingSearch(int trackingID);

    //collision method: open addressing, linear probing
    void linearInsert(int trackingID); 
    void linearSearch(int trackingID); 

    //colision method: open addressing, quadratic probing
    void quadraticInsert(int trackingID); 
    void quadraticSearch(int trackingID); 

    void display();
    int getNumOfCollision();

};

#endif