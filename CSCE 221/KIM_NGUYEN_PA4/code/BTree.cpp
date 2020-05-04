#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <ostream>
#include <istream>
#include <cmath>
#include <deque>
#include <stack>
#include "BTree.h"
using namespace std;
ostream& operator<<(ostream& out, BTree& tree){tree.print_level_by_level(out);return out;}
ostream& operator<<(ostream& out, Node& node){
    out << "( "
    << node.value
    << ", "
    << node.search_cost
    << " )";
    return out;}

istream& operator>>(istream& in, BTree& tree){
    int num;
    in>>num;
    tree.insert(num);
    return in;}

BTree::BTree(const BTree& other){
    Node* root = new Node;
    set_root(root);
    Node* root2 = new Node;
    root2 = other.root;
    int sizes = other.size;
    queue<Node*> q;
    q.push(root2);
    int i=0;
    while(!q.empty()) {
        Node *temp = q.front();
        q.pop();
        if(temp) {
            if (i==sizes) break;
            if (temp->value != 0) {insert(temp->value);i++;}
            q.push(temp->left);
            q.push(temp->right);}}}

BTree::BTree(BTree&& other){size = other.get_size(); root = other.get_root();}

BTree& BTree::operator=(const BTree& other){
    if (this != &other) {
        Node* root = new Node;
        set_root(root);
        Node* root2 = new Node;
        root2 = other.root;
        int sizes = other.size;
        queue<Node*> q;
        q.push(root2);
        int i=0;
        while(!q.empty()) {
            Node *temp = q.front();
            q.pop();
            if(temp) {
                if (i==sizes) break;
                if (temp->value != 0) {insert(temp->value);i++;}
                q.push(temp->left);
                q.push(temp->right);}}}
    return *this;}

BTree& BTree::operator=(BTree&& other){
    if (this != &other) {
        this->size = other.get_size();
        this->root = other.get_root();
        other.size=0;
        other.root=nullptr;}
    return *this;}

Node* BTree::insert(int obj){
    this->size = this->size + 1;
    if(this->root->value ==0) {this->root->value = obj; this->root->search_cost=1; return nullptr; }
    Node* current = new Node;
    current = this->root;
    //the while loop will eventually break
    while(1==1){
        //enter the right side of the tree
        if(obj > current->value){
            if(current->right == nullptr){ Node* new_node = new Node;new_node->value=obj;
                new_node->search_cost = current->search_cost +1;current->right = new_node; return nullptr;}
            else { current = current->right; }}
        //enter the left side of the tree
        else{
            if(current->left == nullptr){ Node* new_node = new Node;new_node->value=obj;
                new_node->search_cost = current->search_cost +1;current->left = new_node; return nullptr;}
            else { current = current->left; }}}
    return nullptr;}

Node* BTree::search(int obj,Node* node){
    if(obj==node->value) return node;
    if(obj<node->value) return search(obj, node->left);
    if(obj>node->value) return search(obj, node->right);
    return nullptr;}

void BTree::update_search_cost(){
    Node* root = new Node;
    root = this->get_root();
    int tracker1=0,tracker2=0,level=0;
    queue<Node*> q;
    Node *fake = nullptr;
    q.push(root);
    while(!q.empty()) {
        Node *temp = q.front();
        q.pop();
        if (temp == nullptr) {tracker2++; q.push(fake);q.push(fake);}
        if(temp) {
            tracker1++;
            tracker2++;
            q.push(temp->left);
            q.push(temp->right);}
        if(tracker1==size && tracker2==pow(2,level)) {cout<<endl<<endl;break;}
        if(tracker2==(pow(2,level))){cout<<endl;level++;tracker2=0; }}}

void BTree::inorder(ostream& out, const Node& tree){
    static int total;
    static int size_tracker;
    static double calc;
    if(tree.left != NULL) {inorder(out, *tree.left);}
    out<<tree.value<<"["<<tree.search_cost<<"]"<<" "; total = total+tree.search_cost;size_tracker++;
    if (size_tracker==this->size) {
        cout<<endl<<endl<<"Total search cost: "<<total<<endl<<endl;
        cout<<"Avg search cost: ";
        calc=total/(this->size*1.0);
        cout<<calc;
        size_tracker=0;total=0;calc=0;}
    if(tree.right != NULL){ inorder(out, *tree.right);}
    return;}

void BTree::print_level_by_level(ostream& out){
    Node* root = new Node; root = this->get_root();
    //tracker1 keeps track of whether or not we have reached the size of the amount of nodes on tree
    //tracker 2 keeps track of number of nodes each level
    //level keeps track of how many levels we need to print out
    int size = this->size; int tracker1=0,tracker2=0,level=0;
    //queue to keep track of what to print out
    queue<Node*> q; Node *fake = nullptr;
    q.push(root);
    while(!q.empty()) {
        Node *temp = q.front();
        q.pop();
        if (temp == nullptr) {tracker2++;cout<<" X "; q.push(fake);q.push(fake);}
        if(temp){
            tracker1++;tracker2++;
            cout<<temp->value<<"["<<temp->search_cost<<"] ";
            q.push(temp->left);
            q.push(temp->right);}
        if(tracker1==size && tracker2==pow(2,level)) {cout<<endl<<endl;break;}
        if(tracker2==(pow(2,level))){cout<<endl;level++;tracker2=0; }
    }
}
