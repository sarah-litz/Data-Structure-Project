#include <iostream>
using namespace std; 

#ifndef BSTREE_HPP
#define BSTREE_HPP

struct treeNode{
    int key; 
    treeNode* left; 
    treeNode* right; 
}; 


class Tree{
    private: 
        treeNode* root;
        /*----helper functions-----*/
        treeNode* insertHelper(treeNode* curr, int trackingID);  
        treeNode* searchHelper(treeNode* curr, int trackingID);
        void displayHelper(treeNode* curr); 
    public: 
        Tree(); 
        void insert(int trackingID); 
        void search(int trackingID);
        void display();  
}; 

#endif
