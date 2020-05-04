//
//  q1.h
//  hw3

#ifndef q1_h
#define q1_h

/*1. (10 points) R-9.7 p. 417
 Draw the 11-entry hash table that results from using the has function, h(k) = (3k + 5) mod 11, to
 hash the keys 12, 44, 13, 88, 23, 94, 11, 39, 20, 16, and 5, assuming collisions are handled by chaining.*/

#include <iostream>
#include <vector>
using namespace std;

class HashNode{
public:
    int key, value;
    HashNode(int K, int V) :key(K), value(N), next(NULL) {}
    HashNode* next;
};

class HashMap{
public:
    HashNode* table[100];
    vector<int> track;
    int hashFunc(int value){int index = (value * 3 + 5)%11; return index;}
    void insert(HashNode* h){
        index = hashFunc(h->value);
        if(table[index]!=NULL){HashNode* temp = table[index]->next; while(temp->next!=NULL){temp = temp->next;}}
        track.pushback(index);
    }
    void print(){
        
    }
};

#endif /* q1_h */
