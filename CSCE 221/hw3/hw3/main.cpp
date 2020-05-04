#include <iostream>
#include <vector>
using namespace std;

/*1. (10 points) R-9.7 p. 417
 Draw the 11-entry hash table that results from using the has function, h(k) = (3k + 5) mod 11, to
 hash the keys 12, 44, 13, 88, 23, 94, 11, 39, 20, 16, and 5, assuming collisions are handled by chaining.
 
 2. (10 points) R-9.8 p. 417
 What is the result of the previous exercise, assuming collisions are handled by linear probing?
 
 3. (10 points) R-9.10 p. 417
 What is the result of Exercise R-9.7, when collisions are handled by double hashing using the secondary
 hash function hs(k) = 7 − (k mod 7)?*/

int main(){
    vector<int> v_q1 = {12, 44, 13, 88, 23, 94, 11, 39, 20, 16, 5};
    return 0;
}
