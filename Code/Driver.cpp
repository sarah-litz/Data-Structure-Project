#include <iostream>
using namespace std; 
#include <fstream>
#include <sstream>
#include <chrono> 
#include "linkedList.hpp"
#include "BSTree.hpp"
#include "hash.hpp"


int main(int argc, char** argv){ 

    /*--------(step 1) SET UP TEST DATA-----------*/ 
    //for storing data
    int testData[40000];  
    //for recording the time measurements 
    float insert[400]; 
    float search[400];
    int count = 0; //count for reading data into array testData

    //read in test data into the array of integers:
    ifstream file; 
    if(argv[1] == NULL){
        cout << "missing command line argument" << endl; 
        return 0; 
    }
    file.open(argv[1]); 
    if(file.is_open()){
        string line; 
        char delim = ',';
        while(getline(file, line)){
            while(line != "" && count < 40000){
                //split up line by delimiter
                string addNum = line.substr(0, line.find(delim)); //grabs substr 
                testData[count] = stoi(addNum); //convert to int and add to array 
                line.erase(0, line.find(delim) + 1); //erases num that has already been added to array 
                count++;
                //loops until end of line is reached. 
            }
        }
    file.close();
    }


   //---Switch Statement for diff Structure implementation---: 
   //user input: 
    bool quit = false; 
    string s_input; 
    int input;
    string s_hashType;
    int hashType; 
    // loop until the user quits
    while (!quit)
    {
        cout << "Choose Menu Option to test the specified Data Structure: " << endl; 
        cout << "1. Linked List Test" << endl; 
        cout << "2. Binary Search Tree" << endl;  
        cout << "3. Hash Table" << endl; 
        cout << "4. Quit" << endl; 

        // read in input, assuming a number comes in
        getline(cin, s_input);
        try
        {
            input = stoi(s_input);
        }
        catch (exception& e)
        {
            // non-numeric input. trigger the default switch case.
            input = 10;
        }
        if(input == 3){
            cout << "which collision resolution mechanism would you like to run?" << endl; 
            cout << " 1. Chaining (linked list) \n 2. Linear Probing (open addressing) \n 3. Quadratic Probing (open addressing) \n"; 
            getline(cin, s_hashType); 
            try{
                hashType = stoi(s_hashType); 
            }catch (exception& e){
                input = 10; 
            }
        }
        
        //----------------------------------------------
        /*initialization needed for switch statments:*/
        int count = 0; //(insert section)
        int startCount = 0; 
        int randID[100]; //(search section)
        int idx = 0; 
        ofstream file; //output file 
        ofstream collisionCountFile; 
        ofstream fileSearchCollisions;

        //case 1 linked list;
        LL list; 
        //case 2 binary search tree 
        Tree tree; 
        //case 3 hash table
        HashTable table; 

        //For Time Stamps: 
        auto start = chrono::high_resolution_clock::now(); 
        auto finish = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = finish - start;
        //------------------------------------------------

        switch (input)
        {   //-------------------------LINKED LIST--------------------------
            case 1: //linked list 
                for(int iteration = 0; iteration < 400; iteration++){ //100 data points at a type for 400 times = 40,000 total nums in testData[]
                    //-----Time for 100 Inserts:---------
                    startCount = count; 
                    start = chrono::high_resolution_clock::now(); //START TIME STAMP for first 100 inserts
                    while(count < startCount + 100){ //inserts 100 nodes into linked list
                        list.insertNode(testData[count]); 
                        count ++; //at exit of first while iteration, count = 100... 2nd time count = 200, etc. 
                    } 
                    finish = chrono::high_resolution_clock::now(); //STOP TIME STAMP
                    elapsed = finish - start;  
                    insert[iteration] = elapsed.count()/100; //record avg time in array 
                    
                    //------Time for 100 Searches:-----------
                    for(int n = 0; n < 100; n++){ //get random generated id nums to search for 
                        idx = rand() % (count-1); //idx in the range 0 to val(linked list size = count)
                        randID[n] = testData[idx]; //add randID retrieved from testData[] using random idx
                    }  
                    start = chrono::high_resolution_clock::now(); //start time stamp
                    for(int n = 0; n < 100; n++){
                        list.searchList(randID[n]); 
                    }
                    finish = chrono::high_resolution_clock::now(); //stop time stamp
                    elapsed = finish - start;  
                    search[iteration] = elapsed.count()/100; //record avg time in array 
                }
                //list.displayList();
                file.open("ll_performance.csv");
                break;

            //-----------------------BINARY SEARCH TREE-------------------
            case 2: //binary search tree
                count = 0; //reset variables from use in linked list case 
                startCount = 0; 
                for(int iteration = 0; iteration < 400 ; iteration++){ //100*400=40,000 numbers in data set 
                    //-----------Time for 100 Inserts: 
                    startCount = count; 
                    start = chrono::high_resolution_clock::now(); //time stamp 1
                    while(count < startCount + 100){ //calls insert funciton for 100 data points at a time
                        tree.insert(testData[count]);
                        count++; 
                    }
                    finish = chrono::high_resolution_clock::now(); //time stamp 2 
                    elapsed = finish - start; 
                    insert[iteration] = elapsed.count()/100; //record avg time in array 
                    
                    //--------Time for 100 Searches: 
                    for(int n = 0; n < 100; n++){ //retrieve 100 random indexes to search for 
                        idx = rand() % (count-1); //idx in the range 0 to val(linked list size = count)
                        randID[n] = testData[idx]; //add randID retrieved from testData[] using random idx
                    }
                    start = chrono::high_resolution_clock::now(); //time stamp 1 
                    for(int n = 0; n < 100; n++){
                        tree.search(randID[n]); 
                    }
                    finish = chrono::high_resolution_clock::now(); //time stamp 2 
                    elapsed = finish - start; //total time 
                    search[iteration] = elapsed.count()/100; //add avg time to array  
                }
                //write to output file; adding insert[] and search[] findings 
                file.open("bst_performance.csv");
                break;
            //------------------------HASH TABLE-------------------------------
            case 3: //hash table 
                cout << "you chose the data structure HASH TABLE using collision mechanism ";
                count = 0; //reset variables
                startCount = 0; 
                collisionCountFile.open("collisionCount.csv"); //collisions in insert function
                fileSearchCollisions.open("searchCollisions.csv"); //collisions in search function
                //switch statement determines type of collision resolution hashtable executes
                switch (hashType){
                    case 1: //chaining 
                        collisionCountFile << "Chaining Collision Count" << endl;
                        fileSearchCollisions << "Chaining Search Collision Count" << endl; 
                        cout << "chaining" << endl; 
                        for(int iteration = 0; iteration < 400; iteration++)
                        { //400*100 = 40,000 data points total
                            //---------Time for 100 Inserts: 
                            startCount = count;                     
                            start = chrono::high_resolution_clock::now(); //time stamp 1 
                            while(count < startCount + 100){
                                table.chainingInsert(testData[count]); 
                                count++; 
                            }
                            finish = chrono::high_resolution_clock::now(); //time stamp 2 
                            elapsed = finish - start; 
                            insert[iteration] = elapsed.count()/100; //record avg time 
                            collisionCountFile << table.getNumOfCollision() << endl; //record collision num for every 100 inserts

                            //--------Time for 100 Searches: 
                            for(int n = 0; n < 100; n++){ //retrieve 100 random indexes to search for 
                                idx = rand() % (count-1); //idx in the range 0 to val(linked list size = count)
                                randID[n] = testData[idx]; //add randID retrieved from testData[] using random idx
                            }
                            start = chrono::high_resolution_clock::now(); //time stamp 1 
                            for(int n = 0; n < 100; n++){
                                table.chainingSearch(randID[n]); 
                            }
                            finish = chrono::high_resolution_clock::now(); //time stamp 2 
                            elapsed = finish - start; //total time 
                            search[iteration] = elapsed.count()/100; //add avg time to array 
                            fileSearchCollisions << table.getNumOfCollision() << endl;
                        }
                        file.open("hashChaining_performance.csv");
                        break; 

                    case 2: //linear probing
                        collisionCountFile << "Linear Probing Collision Count" << endl;
                        fileSearchCollisions << "Linear Probing Search Collision Count" << endl; 
                        cout << "linear probing" << endl; 
                        for(int iteration = 0; iteration < 400; iteration++)
                        { 
                            //--------Time for 100 Inserts: 
                            startCount = count; 
                            start = chrono::high_resolution_clock::now(); //time stamp 1 
                            while(count < startCount + 100){
                                table.linearInsert(testData[count]); 
                                count++; 
                            }
                            finish = chrono::high_resolution_clock::now(); //time stamp 2 
                            elapsed = finish - start; 
                            insert[iteration] = elapsed.count()/100; //record avg time 
                            collisionCountFile << table.getNumOfCollision() << endl; //record collision num for ever 100 inserts

                            //--------Time for 100 Searches: 
                            for(int n = 0; n < 100; n++){ //retrieve 100 random trackingIDs from testData 
                                idx = rand() % (count-1); 
                                randID[n] = testData[idx]; 
                            }
                            start = chrono::high_resolution_clock::now(); //time stamp 1 
                            for(int n = 0; n < 100; n++){
                                table.linearSearch(randID[n]); 
                            }
                            finish = chrono::high_resolution_clock::now(); //time stamp 2 
                            elapsed = finish - start; //total time 
                            search[iteration] = elapsed.count()/100; //add avg time to array 
                            fileSearchCollisions << table.getNumOfCollision() << endl; 
                        }
                        file.open("hashLinear_performance.csv"); 
                        break; 
                    case 3: //quadratic probing 
                        collisionCountFile << "Quadratic Probing Collision Count" << endl; 
                        fileSearchCollisions << "Quadratic Probing Search Collision Count" << endl; 
                        cout << "quadratic probing" << endl; 
                        for(int iteration = 0; iteration < 400; iteration++){
                            //-----------Time for 100 Inserts:
                            startCount = count; 
                            start = chrono::high_resolution_clock::now(); //time stamp 1 
                            while(count < startCount + 100){
                                table.quadraticInsert(testData[count]); 
                                count++; 
                            }
                            finish = chrono::high_resolution_clock::now(); //time stamp 2 
                            elapsed = finish - start; 
                            insert[iteration] = elapsed.count()/100; //record avg time 
                            collisionCountFile << table.getNumOfCollision() << endl;

                            //--------Time for 100 Searches: 
                            for(int n = 0; n < 100; n++){ //retrieve 100 random trackingIDs from testData 
                                idx = rand() % (count-1); 
                                randID[n] = testData[idx]; 
                            }
                            start = chrono::high_resolution_clock::now(); //time stamp 1 
                            for(int n = 0; n < 100; n++){
                                table.quadraticSearch(randID[n]); 
                            }
                            finish = chrono::high_resolution_clock::now(); //time stamp 2 
                            elapsed = finish - start; //total time 
                            search[iteration] = elapsed.count()/100; //add avg time to array 
                            fileSearchCollisions << table.getNumOfCollision() << endl; 
                        }
                        file.open("hashQuadratic_performance.csv"); 
                        break;  
                    default: 
                        //invalid input
                        cout << "invalid input" << endl; 
                        return 0; 
                }//end of Case 3's inner switch statement, still in outer switch statement. 
                collisionCountFile.close(); 
                fileSearchCollisions.close(); 
                break; 

            case 4: //quit
                cout << "k bye" << endl; 
                quit = true; 
                return 0;  

            default: //invalid input
                cout << "invalid input" << endl; 
                return 0; 
        }
        
        //Add data to file and close file
        
        file << "iteration          avg Insert time(s)          avg Search time(s)     " << endl;  
        for(int n = 0; n < 400; n++){
            file << n+1 << "                     " << insert[n] << "                         " << search[n] << endl; 
        }
        file.close(); 
    }
}
