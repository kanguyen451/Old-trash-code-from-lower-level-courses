#include <fcntl.h>
#include <iostream>
#include <vector>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <vector>
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

string trim (string input){
    int i=0;
    while (i < input.size() && input [i] == ' ')
        i++;
    if (i < input.size())
        input = input.substr (i);
    else{
        return "";
    }
    
    i = input.size() - 1;
    while (i>=0 && input[i] == ' ')
        i--;
    if (i >= 0)
        input = input.substr (0, i+1);
    else
        return "";
    
    return input;
    
    
}

vector<string> split (string line, string separator=" "){
    vector<string> result;
    while (line.size()){
        if(line[0]=='\''){
           int nextq;
           char x = 135;
           for(int i=1; i<line.length(); ++i){
               if(line[i]=='\''){
                   nextq = i;
                   break;
               }
           }
        
        string needed = line.substr(1, nextq-1);
        if(line[1]=='{'){
            needed.erase(remove(needed.begin(), needed.end(), ' '), needed.end());
        }
        line = needed + line.substr(nextq + 1);
        }
        
        if(line[0]=='"'){
            int nextq;
            char x = 135;
            for(int i=1; i<line.length(); ++i){
                if(line[i]=='"'){
                    nextq = i;
                    break;
                }
            }
            string needed = line.substr(1, nextq-1);
            if(line[1]=='{'){
                needed.erase(remove(needed.begin(), needed.end(), ' '), needed.end());
            }
            line = needed + line.substr(nextq + 1);
        }
        
        size_t found = line.find(separator);
        if (found == string::npos){
            
            string lastpart = trim (line);
            if (lastpart.size()>0){
                result.push_back(lastpart);
            }
            break;
        }
        
        int piplock;
        bool b=false, e=true;
        int nextq = 0;
        for(int i=0; i<line.length(); ++i){
            if(line[i]=='|' && nextq!=4 && line.substr(0,4)=="echo"){
                piplock = i;
                b = true;
                e=false;
                line[i]=
            }
        }
        
        string segment = trim (line.substr(0, found));
        //cout << "line: " << line << "found: " << found << endl;
        line = line.substr (found+1);
        
        //cout << "[" << segment << "]"<< endl;
        if (segment.size() != 0)
            result.push_back (segment);
        
        
        //cout << line << endl;
    }
    return result;
}

char** vec_to_char_array (vector<string> parts){
    char ** result = new char * [parts.size() + 1]; // add 1 for the NULL at the end
    for (int i=0; i<parts.size(); i++){
        // allocate a big enough string
        result [i] = new char [parts [i].size() + 1]; // add 1 for the NULL byte
        strcpy (result [i], parts[i].c_str());
    }
    result [parts.size()] = NULL;
    return result;
}

void execute (string command){
    vector<string> argstrings = split (command, " "); // split the command into space-separated parts
    int fdswrite , fdsread;
    
    for (int i = 0; i<argstrings.size(); i++){
        if (argstrings[i] == ">"){
            fdswrite = open(argstrings[i+1].c_str(), O_CREAT | O_WRONLY | O_TRUNC,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            dup2(fdswrite,1);
            
            argstrings.erase(argstrings.begin()+i+1);
            argstrings.erase(argstrings.begin()+i);
        }
    }
    for (int i = 0; i<argstrings.size(); i++){
        if (argstrings[i] == "<"){
            fdsread = open(argstrings[i+1].c_str(), O_RDONLY,  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            dup2(fdsread,0);
            
            argstrings.erase(argstrings.begin()+i);
        }
    }
    
    //echo stuff
    for (int i = 0; i < argstrings.size(); i++){
        if (argstrings[i].front() == '"' || argstrings.front() == "\'"){
            argstrings[i].erase(0,1);
        }
        if (argstrings[i].back() == '"' || argstrings.back() == "\'"){
            argstrings[i].erase(argstrings[i].size()-1);
        }
    }
    
    
    if(argstrings[0]=="cd"){
        char stash[FILENAME_MAX];
        char stash2[FILENAME_MAX];
        if(argstrings.size()==1){
            getcwd(stash, sizeof(stash));
            chdir("/");
        }
        else if(argstrings[1]=="-"){
            getcwd(stash2, sizeof(stash2));
            chdir("/Users/");
            chdir(stash);
            strncpy(stash, stash2, sizeof(stash2));
        }else{
            getcwd(stash, sizeof(stash));
            chdir(argstrings[1].c_str());}
        
        return;
    }
    
    char** args = vec_to_char_array (argstrings);// convert vec<string> into an array of char*
    execvp (args[0], args);
}

int main (){
    int stdin = dup(0);
    while (true){ // repeat this loop until the user presses Ctrl + C
        char temp[FILENAME_MAX];
        cout << getcwd(temp, sizeof(temp)) << "$$$ ";
        string commandline = "ls";/*get from STDIN, e.g., "ls  -la |   grep Jul  | grep . | grep .cpp" */
        getline(cin,commandline);
        // split the command by the "|", which tells you the pipe levels
        if (commandline != ""){
            vector<string> tparts = split (commandline, "|");
            vector<string> v_pid;
            // for each pipe, do the following:
            for (int i=0; i<tparts.size(); i++){
                int fd[2];
                pipe(fd);
                // make pipe
                if (!fork()){
                    // redirect output to the next level
                    // unless this is the last level
                    if (i < tparts.size() - 1){
                        dup2(fd[1],1);
                        // redirect STDOUT to fd[1], so that it can write to the other side
                        close (fd[1]);   // STDOUT already points fd[1], which can be closed
                    }
                    //execute function that can split the command by spaces to
                    // find out all the arguments, see the definitionls
                    // cout<<tparts[i]<<endl;
                    execute (tparts [i]); // this is where you execute
                }else{
                    wait(0);            // wait for the child process
                    // then do other redirects
                    dup2(fd[0],0);
                    close(fd[1]);
                }
            }
            dup2(stdin, 0);
            // cout<<endl;
        }
    }
    // }
}
