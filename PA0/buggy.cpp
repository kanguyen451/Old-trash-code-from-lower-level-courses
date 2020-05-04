#include <iostream>
#include <vector> //to work with vectors
using namespace std; //to avoid putting std:: in front of everything
class node {
public: //made the class public
    int val;
    node* next;
};
void create_LL(vector<node*>& mylist, int node_num){
    mylist.assign(node_num, NULL);
    //create a set of nodes
    for (int i = 0; i < node_num; i++) {
        node* fill = new node();
        mylist[i] = fill; //initialized the vector elements
        mylist[i]->val = i; // . to ->
        mylist[i]->next = NULL; // . to ->
    }
    
    //create a linked list
    for (int i = 0; i < node_num-1; i++) { //subtracted one from node_num
        mylist[i]->next = mylist[i+1];
    }
    
}
int add_LL(node* ptr){
    int ret = 0;
    while(ptr) {
        ret += ptr->val;
        ptr = ptr->next;
    }
    return ret;
}

int main(int argc, char ** argv){
    const int NODE_NUM = 3;
    vector<node*> mylist;
    
    create_LL(mylist, NODE_NUM);
    int ret = add_LL(mylist[0]);
    cout << "The sum of nodes in LL is " << ret << endl;
    
    //delete nodes to prevent overflow
    for(int i=0; i<mylist.size(); ++i){
        mylist[i]->val = -1;
        mylist[i]->next = NULL;
    }
}
