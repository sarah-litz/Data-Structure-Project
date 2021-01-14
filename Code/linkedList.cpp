#include <iostream>
using namespace std; 
#include "linkedList.hpp"

LL::LL(){
    head = NULL; 
}

void LL::insertNode(int trackingID){
    if(head==NULL) { //if linked list is empty, set newNode as head
        head = new Node;
        head->key = trackingID; 
        head->next = NULL; 
    }
    else{ //insert into linkedList at first open location 
        Node* curr = head; 
        while(curr->next!=NULL){
            curr = curr->next; 
        }//at loop exit, curr is the last filled node in the linked list
        Node* addNode = new Node; 
        addNode->key = trackingID; 
        addNode->next = NULL; 
        curr->next = addNode; //attaches to LL 
    }
    return; 
}

Node* LL::searchList(int trackingID){
    Node* curr = head; 
    while(curr->key!=trackingID && curr!=NULL){
        curr = curr->next; 
    }
    return curr; //return the node, or NULL if trackingID DNE
}

void LL::displayList(){
    cout << "Linked List contents:" << endl; 
    if(head == NULL){
        cout << "linked list is empty." << endl; 
    }else{
        Node* curr = head; 
        while(curr != NULL){
            cout << curr->key << " "; 
            curr = curr->next; 
        }
    }
    return; 
}
