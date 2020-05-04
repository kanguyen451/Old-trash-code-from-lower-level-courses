#include "Ackerman.h"
#include "BuddyAllocator.h"
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void easytest(BuddyAllocator* ba){
  // be creative here
  // know what to expect after every allocation/deallocation cycle

  // here are a few examples
  ba->printlist();
  // allocating a byte
  char* mem = ba->alloc (1);
    ba->printlist ();
  // now print again, how should the list look now
  
  //char* mem1 = new char [1];
  ba->free (mem); // give back the memory you just allocated
    ba->printlist();

}

int main(int argc, char ** argv) {
    int basic_block_size = 128, memory_length =  1024*1024*128;
    //piazza post websites - https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
//    int opt;
//    while((opt=getopt(argc,argv, "b:s:")) !=-1){
//        if((char)opt == 'b'){
//            basic_block_size = stoi(optarg);
//        }
//        else if((char)opt=='s'){
//            memory_length = stoi(optarg);
//        }
//        else{
//            cout<<"Invalid input"<<endl;
//            return 0;
//        }
//    }
  // create memory manager
  BuddyAllocator * allocator = new BuddyAllocator(basic_block_size, memory_length);

  // the following won't print anything until you start using FreeList and replace the "new" with your own implementation
  easytest (allocator);
  
  // stress-test the memory manager, do this only after you are done with small test cases
  Ackerman* am = new Ackerman ();
  am->test(allocator); // this is the full-fledged test.
  
  // destroy memory manager
  delete allocator;
    return 0;
}
