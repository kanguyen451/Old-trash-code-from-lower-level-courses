//
//  skip_list.cpp
//  pa5
//
//  Created by Kim Nguyen on 4/5/19.
//  Copyright © 2019 Kim Nguyen. All rights reserved.
//


#include "skip_list.h"


istream& operator>>(istream& in, vector<int>& v){
    int num;
    in>>num;
    v.push_back(num);
    return in;}

int SkipList::level_assign(){bool levelAssign = true; int num, count=0;
    while(levelAssign && count<2){num = rand() % 2; if(num==0) {levelAssign =false;} else {count++;}} return count;}

SkipList SkipList::del(SkipList sl, int number){
    int c = 0, avg=3, total_comp=0; it_l3 = l3.begin(); it_l2 = l2.begin(); it_l1 = l1.begin();
    for(int i=2; i>=0; --i){c=0;switch(i){
            //case 0 means that we are on level 3
            case 0:while(it_l3!=vlist[2].end() && vlist[2].empty()==false && c<8 && it_l3->value != number){++it_l3; ++total_comp; ++c;}
                if(it_l3->value==number && vlist[2].empty()==false&& c<8){
                    float print_avg = total_comp/avg;
                    cout<<"Deleting "<<number<<" took "<<total_comp<<" comparisons. The average cost is "<<print_avg<<endl;
                    vlist.at(2).erase(it_l3); --size;} c = 0; break;
            case 1:while(it_l2!=vlist[1].end() && vlist[1].empty()==false && c<8 && it_l2->value != number){++it_l2; ++total_comp; ++c;}
                if(it_l2->value==number && c<8&& vlist[1].empty()==false){
                    vlist.at(1).erase(it_l2); --size;} c = 0; break;
            //first case it will go to - delete it from the first level
            case 2:while(it_l1!=vlist[0].end() && vlist[0].empty()==false && c<8 && it_l1->value != number){++it_l1; ++total_comp; ++c;}
                if(it_l1->value==number && vlist[0].empty()==false && c<8){vlist.at(0).erase(it_l1); --size;} c = 0; break;}}
    return *this;}

SkipList SkipList::insert(SkipList sl, int number){
    Node node = Node(number); int lvl = level_assign();
    for(int i = 0; i<=lvl; ++i){switch(i){
                //case 0 means level 3 the most bottom level
            case 0: it_l3 = l3.begin();
                    while(it_l3!=vlist[2].end() && it_l3->value < number){++it_l3; ++node.comp; ++total_comp;}
            ++size; ++node.search_cost; it_l3 = vlist.at(2).insert(it_l3, node); break;
            case 1:  if(l2.empty()){break;}else{it_l2 = l2.begin();
                     while(it_l2!=vlist[1].end() && it_l2->value < number){++it_l2; ++node.comp; ++total_comp;}
                ++size; ++node.search_cost; it_l2 = vlist.at(1).insert(it_l2, node); break;}
            case 2:  if(l1.empty()){break;}else{it_l1 = l1.begin();
                     while(it_l1!=vlist[0].end() && it_l1->value < number){++it_l1; ++node.comp; ++total_comp;}
                ++size; ++node.search_cost; it_l1 = vlist.at(0).insert(it_l1, node);} break;}}
    float print_avg = node.comp/node.search_cost;
    cout<<"Inserting "<<number<<" took "<<node.comp<<" comparisons. The average cost is "<<print_avg<<endl;
    return *this;}

bool SkipList::search(int number){
    it_l3 = l3.begin(); it_l2 = l2.begin(); it_l1 = l1.begin(); int c = 0;
    for(int i=2; i>=0; --i){
        switch(i){
                //case 0 means that we are on level 3
            case 0:while(it_l3!=vlist[2].end() && c<8 && it_l3->value != number){++it_l3; ++total_comp; ++c;}
                if(it_l3->value==number && c<8){return true;} c = 0; break;
                
            case 1:while(it_l2!=vlist[1].end() && c<8 && it_l2->value != number){++it_l2; ++total_comp; ++c;}
                if(it_l2->value==number && c<8){return true;} c = 0; break;
                
                //first case it will go to - delete it from the first level
            case 2:while(it_l1!=vlist[0].end() && c<8 && it_l1->value != number){++it_l1; ++total_comp; ++c;}
                if(it_l1->value==number && c<8){return true;} c = 0; break;}}
    return false;}

void SkipList::print(){
    for(it_l1 = l1.begin(); it_l1!=l1.end(); ++it_l1){if(it_l1->value==-1000){cout<<"-infinity ";}
        else if(it_l1->value==1000){cout<<"infinity ";}else{cout<<it_l1->value<<" ";}} cout<<endl<<endl;
    for(it_l2 = l2.begin(); it_l2!=l2.end(); ++it_l2){if(it_l2->value==-1000){cout<<"-infinity ";}
        else if(it_l2->value==1000){cout<<"infinity ";}else{cout<<it_l2->value<<" ";}} cout<<endl<<endl;
    for(it_l3 = l3.begin(); it_l3!=l3.end(); ++it_l3){if(it_l3->value==-1000){cout<<"-infinity ";}
        else if(it_l3->value==1000){cout<<"infinity ";}else{cout<<it_l3->value<<" ";}} cout<<endl<<endl;}


