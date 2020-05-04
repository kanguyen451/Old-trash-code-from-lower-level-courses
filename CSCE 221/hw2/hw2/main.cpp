#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int maximum(int arr[], int& n, int& max){
    if(arr[n]>max){max = arr[n];}
    ++n;
    if(n<10){maximum(arr, n, max);}
    return max;
}

int main(){
    int arr[] = {1,1,1,99999999,1,1};
    int max=0, n=0;
    max = maximum(arr, n, max);
    cout<<"THe maximum is: "<<max<<endl;
    return 0;
}
