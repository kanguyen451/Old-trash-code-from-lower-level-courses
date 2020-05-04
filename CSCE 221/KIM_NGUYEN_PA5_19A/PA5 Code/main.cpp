//
//  main.cpp
//  pa5
//
//  Created by Kim Nguyen on 4/4/19.
//  Copyright © 2019 Kim Nguyen. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "skip_list.h"
using namespace std;

vector<int> read_file(string filename){
    vector<int>input;ifstream myfile(filename);while(!myfile.eof()){myfile>>input;}
    return input;}

int main() {
    srand(time(NULL));
    SkipList sl_p,sl_r,sl_l; vector<int> vp,vr,vl;
    cout<<"We have three inputs: perfect, linear, and random."<<endl;
    vp = read_file("3p"); vl = read_file("3l"); vr = read_file("3r");
    cout<<"Perfect input: "<<endl; for(int i=0; i<vr.size(); ++i){cout<<vp[i]<<" ";}
    cout<<endl<<endl<<"Linear input: "<<endl; for(int i=0; i<vr.size(); ++i){cout<<vl[i]<<" ";}
    cout<<endl<<endl<<"Random input: "<<endl; for(int i=0; i<vr.size(); ++i){cout<<vr[i]<<" ";}
    cout<<endl<<endl;

    //insert the input integers into the skip lists
    cout<<endl<<"Inserting all of the perfect intput into a skip list:"<<endl;
    for(int i=0;i<vr.size();++i){sl_p=sl_p.insert(sl_p,vp[i]);}
    cout<<endl<<"Inserting all of the linear intput into a skip list:"<<endl;
    for(int i=0;i<vr.size();++i){sl_l=sl_l.insert(sl_l,vl[i]);}
    cout<<endl<<"Inserting all of the random intput into a skip list:"<<endl;
    for(int i=0;i<vr.size();++i){sl_r=sl_r.insert(sl_r,vr[i]);}
    
    cout<<"\nThis is what the skip list looks for perfect input: \n"; sl_p.print();
    cout<<"\nThis is what the skip list looks for linear input: \n"; sl_l.print();
    cout<<"\nThis is what the skip list looks for random input: \n"; sl_r.print();
    
    cout<<"We will now delete nodes from the lists:"<<endl;
    
    cout<<"Deleting 1 from perfect skip list: "<<endl;
    sl_p = sl_p.del(sl_p,1);
    cout<<endl<<"Deleting 1 from linear skip list: "<<endl;
    sl_l = sl_l.del(sl_l,1);
    cout<<endl<<"Deleting 1 from random skip list: "<<endl;
    sl_r = sl_r.del(sl_r,1);
    
    exit(0);
}
