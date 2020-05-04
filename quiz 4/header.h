#define HEADER_H
#ifndef HEADER_H
#include <iostream.h>
#include <signal.h>
#include <cstring>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <errno.h>
#include <fcntl.h> 
#include <sys/stat.h>
#include <semaphore.h>
#include <iostream>
using namespace std;
class KernelSemaphore{
    string name;
    sem_t* sem;
public:
    KernelSemaphore (string _name, int _init_value){
        this->name = _name;
        this->sem = sem_open(_name.c_str(), 0664, O_CREAT, _init_value);
    }
    void P(){ 
        sem_wait(this->sem); // decrements/locks semaphore
    }
    void V(){
        sem_post(this->sem); // increments/unlocks semaphore
    }
    ~KernelSemaphore ();
};


#endif /* HEADER_H */
