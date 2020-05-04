#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h>
#include <errno.h>
using namespace std;

int main(){
    if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) {
        perror(0);
        exit(1);}
    if(fork()==0){ //child
        cout<<"Hello"<<endl;
        exit(0);
    }else{ //parent
        cout<<"Howdee"<<endl;
        while(true);
    }
}