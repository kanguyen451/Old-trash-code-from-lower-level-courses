#include "BuddyAllocator.h"
#include <iostream>
#include<cmath>
#include<cstdint>
using namespace std;

//tanzir notes
BuddyAllocator::BuddyAllocator (uint _basic_block_size, uint _total_memory_length){
    basic_block_size = _basic_block_size;
    total_memory_size = _total_memory_length;
    start = new char[total_memory_size];
    uint position_num = log2(total_memory_size/basic_block_size);
    for (uint i = basic_block_size; i <= total_memory_size; i*=2){
        LinkedList* temp = new LinkedList;
        FreeList.push_back(*temp);
    }
    FreeList[position_num].head = (BlockHeader*) start;
    FreeList[position_num].head->block_size = total_memory_size;
    FreeList[position_num].head->next = NULL;
    FreeList[position_num].head->is_free = true;
    
}
//deconstructr
BuddyAllocator::~BuddyAllocator (){delete (start);}

char* BuddyAllocator::alloc(uint _length) {
    /* This preliminary implementation simply hands the call over the
     the C standard library!
     Of course this needs to be replaced by your implementation.
     */
    
    //real x - gives us the position of the smallest block we need to allocate
    uint rx = _length  + sizeof(BlockHeader);
    //position of the smallest block we need to allocate
    int _i = (int) ceil(log2(double(rx)/basic_block_size));
    //total amount of indexes that the FreeList can have
    uint k = log2(total_memory_size/basic_block_size);
    BlockHeader* final1;
    
    //there is a chance that i can output as negative
    //to prevent this, make it 0
    if (_i < 0){_i = 0;}
    if (FreeList[_i].head){
        BlockHeader* b = FreeList[_i].head;
        b->is_free = false;
        FreeList[_i].remove(b);
        return (char*)(b+1);
    }
    else {
        //set j to i and manipulate it
        int j = _i;
        while ((FreeList[j].head == NULL) && (j<k)){j++;}
        //split
        while (j>_i){
            BlockHeader* b = FreeList[j].head;
            BlockHeader* bb = split(b);
            b->is_free = true;
            FreeList[j-1].insert(b);
            FreeList[j].remove(b);
            j--;
        }
    }
    
    //return the allocated block
    final1 = FreeList[_i].head;
    final1->is_free=false;
    FreeList[_i].remove(final1);
    //add one to offset the size
    return (char*) (final1+1);
}

BlockHeader* BuddyAllocator::getbuddy(BlockHeader *addr){
    BlockHeader* buddy = (BlockHeader*) (((char*)addr - start) ^ (uintptr_t)((addr->block_size)+start));
    return buddy;
}

int BuddyAllocator::free(char* _a) {
    /* Same here! */
    BlockHeader* b = (BlockHeader*)(_a - sizeof(BlockHeader));
    uint _i = (uint) ceil(log2(b->block_size/basic_block_size));
    b->is_free = true;
    while(true && _i < FreeList.size()-1)
    {
        //bb is buddy of b
        BlockHeader* bb = getbuddy(b);
        if (bb->is_free == false){
            //i dont think this ever gets touched
            FreeList[_i].insert(b);
            return 0;}
        else{
            //remove b and bb from old level, only insert one block into new level
            FreeList[_i].remove(b);
            FreeList[_i].remove(bb);
            BlockHeader* m = merge(b,bb);
            FreeList[_i+1].insert(m);
        }
        ++_i;
    }
    return 0;
}

BlockHeader* BuddyAllocator::split (BlockHeader* b){
    //get hald of address
    int s = b->block_size/2;
    char* buddy_conv = (char*) b + s;
    //conversion of address
    BlockHeader* buddy_b = (BlockHeader*) buddy_conv;
    //set new sizes
    buddy_b->block_size = s;
    b->block_size = s;
    //make rightmost block next null
    buddy_b->next = NULL;
    //find position of where buddy should be
    uint pos_of_b = (uint) (log2((double)b->block_size/basic_block_size));
    FreeList[pos_of_b].insert(buddy_b);
    //return b
    return b;
    
}

BlockHeader* BuddyAllocator::merge(BlockHeader* block1, BlockHeader* block2){
    //prereq conditions
    if (block1->block_size){return NULL;}
    if(block1 != getbuddy(block2)){return NULL;}
    if(block2 != getbuddy(block1)){return NULL;}
    uint pos = log2(block2->block_size/basic_block_size);
    
    //depending on which is the leftmost block
    //we then increase the size of one
    //remove both from old level
    if(block1 < block2){
        block1->block_size =block1->block_size*2;
        FreeList[pos].remove(block1);
        FreeList[pos].remove(block2);
        block1->next = NULL;
        return block1;}
    if (block2 < block1){
        block2->block_size = block2->block_size*2;
        FreeList[pos].remove(block1);
        FreeList[pos].remove(block2);
        block2->next = NULL;
        return block2;}

    
    return NULL;
}

void BuddyAllocator::printlist (){
    cout << "Printing the Freelist in the format \"[index] (block size) : # of blocks\"" << endl;
    for (int i=0; i<FreeList.size(); i++){
        cout << "[" << i <<"] (" << ((1<<i) * basic_block_size) << ") : ";  // block size at index should always be 2^i * bbs
        int count = 0;
        BlockHeader* b = FreeList [i].head;
        // go through the list from head to tail and count
        while (b){
            count ++;
            // block size at index should always be 2^i * bbs
            // checking to make sure that the block is not out of place
            if (b->block_size != (1<<i) * basic_block_size){
                cerr << "ERROR:: Block is in a wrong list" << endl;
                exit (-1);
            }
            b = b->next;
        }
        cout << count << endl;
    }
}
