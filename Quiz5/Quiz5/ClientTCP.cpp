#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
#include <fcntl.h>
#include <time.h>
#include <signal.h>

#include <sys/time.h>
#include <cassert>
#include <assert.h>

#include <cmath>
#include <numeric>
#include <algorithm>

#include <list>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;

void talk_to_server (int sockfd){
	char buf [1024];
    cout<<sockfd<<endl;
	while (true){
		/*if (recv (sockfd, buf, sizeof (buf), 0) < 0){
            perror ("client: Receive failure");    
            exit (0);
        }
        cout << buf; */
        cout << "Type a number for the server: "; 
        int num; 
        cin>> num;
		if (send (sockfd, &num, sizeof (int), 0) == -1){
            perror("client: Send failure");
            break;
        }
        
        if (recv (sockfd, buf, sizeof (buf), 0) < 0){
            perror ("client: Receive failure");    
            exit (0);
        }
        cout << "The server sent back " << *(int *)buf << endl; 

	}
    
}



int client (char * server_name, char* port)
{
	struct addrinfo hints, *res;
	int sockfd;
    int fd;
    string servername = (string) server_name;
    string substitute = "";
    string file_name = "https.txt";
	// first, load up address structs with getaddrinfo():
    fd = open(file_name.c_str(), O_CREAT | O_RDWR | O_TRUNC, 0777);
    
    if(servername.find("/") > 0 && servername.find("/")<100){
        substitute = servername.substr(servername.find("/"));
        servername.erase(servername.begin()+servername.find("/"),servername.end());
    }
    else{
        substitute = "/";
    }
    
    cout << "HELLO1" << substitute << endl;
    cout << "REHGBERY" << servername << endl;
    
    
    string get_string = "GET " + substitute + " HTTP/1.1\r\nhost: " + servername + "\r\n\r\n";
    
    
    
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	int status;
	//getaddrinfo("www.example.com", "3490", &hints, &res);
	if ((status = getaddrinfo(servername.c_str(), port, &hints, &res)) != 0) {
        cerr << "getaddrinfo: " << gai_strerror(status) << endl;
        return -1;
    }

	// make a socket:
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sockfd < 0)
	{
		perror ("Cannot create scoket");	
		return -1;
	}

	// connect!
	if (connect(sockfd, res->ai_addr, res->ai_addrlen)<0)
	{
		perror ("Cannot Connect");
		return -1;
	}
	cout << "Successfully connected to " << server_name << endl;
	cout <<"Now Attempting to send a message "<< server_name << endl;
	char buf [1024];
	//sprintf (buf, "hello");
	send (sockfd, get_string.c_str(), get_string.size(), 0);
	//recv (sockfd, buf, 1024, 0);
//	cout << "Received " << buf << " from the server" << endl;
//	talk_to_server(sockfd);
//	return 0;
    int count=1;
    string buff;
    string file;
    while(recv (sockfd, buf, 1024, 0)>0)
    {
        
        cout << buf;
        buff = (string) buf;
        if(count == 1)
        {
        if(buff.find("<")>0 ){
            write(fd, buff.substr(buff.find("<")).c_str(), buff.substr(buff.find("<")).size()-1);
        }
            count++;
        }else{
            write(fd, buff.c_str(), buff.size()-1);
        }
//        size_t pos1=-1, pos2=-1;
//        ofstream out(file_name);
//            string push_t = "<" + buff.substr(pos1+1, buff.length() - pos2) + ">";
//            buff.erase(pos1,buff.length() - pos2);
//            out << push_t;
        
        memset(buf,0,sizeof(buf));
    }
    return 0;
}


int main (int ac, char *argv[])
{
	if (ac < 3){
        cout << "Usage: ./client <server name/IP> <port no>" << endl;
        exit (-1);
    }
    cout<<"HEY: "<<argv[1]<<" "<<argv[2]<<endl;
	client (argv [1], argv [2]);
}
