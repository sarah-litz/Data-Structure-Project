#include <iostream>
using namespace std; 
#pragma once

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

struct Node{
    int key; 
    Node* next; 
}; 

//class for storing and manipulating linked-list of nodes
class LL{
    private: 
        //pointer to head node of linked-list 
        Node* head; 
        /* ------- helper functions --------*/
    public: 
        LL(); 
        void insertNode(int trackingID); 
        //float time100inserts(int pos);

        Node* searchList(int trackingID); 
        void displayList(); 
}; 

#endif