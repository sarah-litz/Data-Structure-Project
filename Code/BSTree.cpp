#include <iostream>
using namespace std; 
#include "BSTree.hpp"

Tree::Tree(){
    root = NULL; 
}

//--------------------------------------------------------INSERT NODE IN TREE--------------------
treeNode* Tree::insertHelper(treeNode* curr, int trackingID){
    if(curr == NULL){ //empty location found
        treeNode* newNode = new treeNode; 
        newNode->key = trackingID; 
        newNode->right = NULL; 
        newNode->left = NULL; 
        return newNode; 
    }
    else if(trackingID < curr->key){ //if ID less than curr
        curr->left = insertHelper(curr->left, trackingID); //traverse to left child 
    }
    else if(trackingID > curr->key){ //if ID greater than curr
        curr->right = insertHelper(curr->left, trackingID); //traverse to right child 
    }else{ //trackingID == curr->key
        return curr; //node w/ key 'trackingID' already exists. returns that node if this is the case. 
    }
}
void Tree::insert(int trackingID){
    root = insertHelper(root, trackingID); 
}

//--------------------------------------------------------------SEARCH BY KEY------------------------------
treeNode* Tree::searchHelper(treeNode* curr, int trackingID){
    if(curr == NULL){
        return NULL; 
    }    
    else if(curr->key == trackingID){
        return curr; 
    }
    else if(trackingID < curr->key){
        return searchHelper(curr->left, trackingID); 
    }
    else{ //trackingID > curr->key
        return searchHelper(curr->right, trackingID); 
    }
}
void Tree::search(int trackingID){ //returns true if node w/ trackingID is found
    treeNode* found = searchHelper(root, trackingID); 
    if(found==NULL){
        return; //for boolean algorithm, return false  
    }else{
        return; //return true 
    }
}

//--------------------------------------------------------DISPLAY NODES---------------------
void Tree::displayHelper(treeNode* curr){
    if(curr){
        displayHelper(curr->left);
        cout <<" " << curr->key; 
        displayHelper(curr->right);
    }
}
void Tree::display(){
    displayHelper(root); 
    cout << endl; 
}