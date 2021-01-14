#include <iostream>
using namespace std; 
#include "hash.hpp"
#include <cmath> //for exponent operation



HashTable::HashTable(){
    tableSize = 40009;  
    //array of nodes initalization   
    for(int n = 0; n < 40009; n++){
        chainingTable[n] = NULL;
    }
    //array of integers initalization
    for(int n = 0; n < tableSize; n++){
        intTable[n] = -1; 
    }
}

/*implement 3 collision resolution mechanisms: 
        open addressing: linear probing
        open addressing: quadratic probing 
        (for open addressing use a circular array mechanism)(goes from idx40008 to idx0, to idx1, etc.)
        chaining w/ a linked list
*/

//--------------------------------- C H A I N I N G --------------------------------------------------
void HashTable::chainingInsert(int trackingID){
    int index = hashFunction(trackingID); //index value = ID mod 40009
    //cout << "TrackingID=" << trackingID  << ", index=" << index << endl;      
    if(chainingTable[index] == NULL)
    { 
        //if bucket(linked list) at this index is empty
        hashNode* newNode = new hashNode; 
        newNode->key = trackingID; 
        newNode->next = NULL; 
        chainingTable[index] = newNode; //"head" of linked list
    }
    else
    { 
        //cout << "Starting Collision. TrackingID=" << trackingID  << ", index=" << index << endl;      
        collisionCount++; 
        hashNode* curr = chainingTable[index]; 
        while(curr->next != NULL){
            curr = curr->next; 
        }
        hashNode* newNode = new hashNode; 
        newNode->key = trackingID; 
        newNode->next = NULL; 
        curr->next = newNode; 
    }
    return; 
}

void HashTable::chainingSearch(int trackingID){
    int index = hashFunction(trackingID); 
    hashNode* curr = chainingTable[index]; //curr initialized to "head" of linked list
    while(curr != NULL){ //while not at end of linked list
        if(curr->key == trackingID){ //node found
            //return true; 
            return; 
        }else{ //continue LL traversal
            collisionCount++; 
            curr = curr->next; 
        }
    }
    //if this spot is reached, trackingID DNE
    //return false; 
    return; 
}


//--------------------------------- L I N E A R - P R O B I N G ------------------------------------
void HashTable::linearInsert(int trackingID)
{
    int index = hashFunction(trackingID); 
    int hashIdx = index; //constant 
    while ( intTable[index] != -1 ) //loop until empty array position is found
    {
        collisionCount++; 
        index = (hashIdx + collisionCount)%tableSize; 
    }
    intTable[index] = trackingID;
    return;  
}
void HashTable::linearSearch(int trackingID)
{
    int index = hashFunction(trackingID);
    int hashIdx = index;  
    int n = 0; 
    while ( intTable[index] != trackingID ) { //while no match to trackingID is found, keep searching
        n++; 
        collisionCount++; 
        index = (hashIdx + n)%tableSize; 
        if( intTable[index] == -1){ //trackingID match could not be found
            //return false for boolean version
            return; 
        }
    }
    //if while loop is exited, match to trackingID found
    //return true for boolean version
    return; 
}


//--------------------------------- Q U A D R A T I C - P R O B I N G ------------------------------------
void HashTable::quadraticInsert(int trackingID){
    int index = hashFunction(trackingID);
    int hashIdx = index; 
    int i = 1; 
    while( intTable[index] != -1) //loop until empty arr position found
    {
        collisionCount++; 
        index = (hashIdx + pow(i,2));
        index = index%tableSize;
        i++; 
    }
    //empty spot found
    intTable[index] = trackingID; 
    return; 
}
void HashTable::quadraticSearch(int trackingID){
    int index = hashFunction(trackingID); 
    int hashIdx = index; 
    int i = 1; 
    while( intTable[index] != trackingID )
    {
        collisionCount++; 
        index = hashIdx + pow(i,2); 
        index = index%tableSize; 
        i++; 
        if( intTable[index] == -1){ //trackingID match DNE
            //return false for boolean version
            return; 
        } 
    }   
    //return true for boolean version
    return; 
}


void HashTable::display(){

}

int HashTable::getNumOfCollision(){
    int collisionCountFinal = collisionCount; 
    collisionCount = 0; //resets collisionCount for following iteration
    return collisionCountFinal;
}

//- - - Helper Functions - - - 
hashNode* HashTable::createNode(int trackingID){
    hashNode* newNode = new hashNode; 
    newNode->key = trackingID; 
    newNode->next = NULL; 
    return newNode; 
}
unsigned int HashTable::hashFunction(int trackingID){ //gets index for node with trackingID = <int key>
    //tableSize = 40009
   int index = trackingID%tableSize; 
   return index; 
}