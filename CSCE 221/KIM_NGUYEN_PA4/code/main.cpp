#include <iostream>
#include <cmath>
#include <istream>
#include <ostream>
#include <fstream>
#include "BTree.h"

BTree read_file(string file_name){
    BTree tree;
    Node* addnode = new Node;
    tree.set_root(addnode);
    ifstream myfile(file_name);
    //insert all of the integer inputs into the tree
    while(!myfile.eof()){myfile>>tree;}
    return tree;}

int main(){
    BTree tree1;
    int search_for; //when asking user to insert an integer to look for
    string file_name;
    tree1 = read_file(file_name);
    
    cout<<"This is tree1: \n\n"<<tree1<<" The total number of nodes is: "<<tree1.get_size();
    cout<<"\n\n";
    cout<<"printing nodes in inorder travesal for tree1: \n";
    //using inorder traversal
    //printing the single line inorder traversal
    tree1.inorder(cout,*tree1.get_root());
    cout<<"\n\n";
    cout<<"Enter a number to search in binary tree tree1:";
    cin>>search_for;
    cout<<*tree1.search(search_for,tree1.get_root());
    cout<<"\n\n";
    
    //using sopy constructor
    BTree tree2(tree1);
    cout<<"tree2 is now a copy of tree1: \n"<<tree2<<endl;
    cout<<"The total number of nodes is: "<<tree2.get_size();
    cout<<"\n\n";
    //inserting 128 into tree1
    tree1.insert(128);
    cout<<"tree1 after inserting value(128): \n"<<tree1;
    cout<<" The total number of nodes is: "<<tree1.get_size();
    cout<<"\n\n";
    cout<<"printing nodes in inorder travesal for tree1: \n";
    
    tree1.inorder(cout,*tree1.get_root());
    cout<<"\n\n";
    cout<<"tree2: \n"<<tree2;
    cout<<"The total number of nodes is:"<<tree2.get_size();
    cout<<"\n\n";
    return 0;
}

