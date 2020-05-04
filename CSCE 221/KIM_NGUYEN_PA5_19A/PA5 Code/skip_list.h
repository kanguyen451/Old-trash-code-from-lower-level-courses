#ifndef skip_list_h
#define skip_list_h

#include <iostream>
#include <vector>
#include <iterator>
#include <queue>
#include <list>
#include <string>
#include <limits>
#include <fstream>
#include <cmath>
#include <ctime>
#include <random>
#include <deque>
#include <stack>
using namespace std;

//use the iterators inside your nodes to connect up and down
struct Node{
    int value,op,comp,search_cost;list<Node>::iterator down;
    Node(int num,list<Node>::iterator d): value(num), down(d), comp(0), search_cost(0) {} //constructor
    Node(int num):value(num),comp(0),search_cost(0),op(0){}};

//vector of lists of nodes
class SkipList{
public:
    int size,total_comp;list<Node>l1,l2,l3;list<Node>::iterator it_l1,it_l2,it_l3;vector<list<Node>>vlist={l1,l2,l3};vector<list<Node>>::iterator it_vlist;
    
    //constructor
    //the lists are initialized with negative and positive "infinity" pushed inside them
    SkipList() : it_vlist(vlist.begin()), size(0), total_comp(0) {l3={Node(-1000,l3.begin()),Node(1000,l3.end())};l2={Node(-1000,l3.begin()),Node(1000,l3.end())};l1={Node(-1000,l2.begin()),Node(1000,l2.end())};
        vlist = {l1,l2,l3}; it_l1 = l1.begin(); it_l2 = l2.begin(); it_l3 = l3.begin();}
    int level_assign(); //done
    void print(); //print skip list
    bool search(int number); //done
    SkipList insert(SkipList sl, int number); //done
    SkipList del(SkipList sl, int number); //done
};

istream& operator>>(istream& in, vector<int>& v);

#endif
