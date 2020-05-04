#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <errno.h>
#include "header.h"
#include <semaphore.h>
using namespace std;

int main (){
    KernelSemaphore ks ("/my_kernel_sema", 0);
    ks.P();
    cout << "I can tell the producer is done"<< endl;
}
