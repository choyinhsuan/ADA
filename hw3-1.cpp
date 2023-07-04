#include <iostream>
#include <stdbool.h>
#include <stdlib.h>
#include <stack>
#include <string.h>
#include <algorithm>
using namespace std;

long long m, num;
stack <long long> rod;
string command;
long long sum[1000000] = {0};

void PUT();
void TAKE();
void CC();
void DD();

int main(){
    ios_base::sync_with_stdio(false);
    cin>>m;
    stack <long long> rod;
    string command;
    num = 0;
    for (long long i = 0; i<m; i++){
        cin>>command;
        switch(command[0]){
            case 'P':
                PUT();
                break;
            case 'T':
                TAKE();
                break;
            case 'C':
                CC();
                break;
            case 'D':
                DD();
                break;
        }
    }
    return 0;

}
void PUT(){
    long long w;
    cin>>w;
    rod.push(w);
    num++;
    sum[num] = sum[num-1]+w;
    return;
}
void TAKE(){
    cout<<rod.top()<<'\n';
    rod.pop();
    num--;
    return;
}
void CC(){
    long long x, k;
    cin>>x>>k;
    long long target = (x%k == 0)?x/k:x/k+1;
    long long temp[x+5] = {0};
    long long temp2[x+5] = {0};
    for(long long i = 0; i<x; i++){
        temp[i] = rod.top();
        rod.pop();
        temp2[i] = temp[i];
    }
    sort(temp, temp+x);
    long long thew = temp[x-target];
    long long thesum = 0;
    long long count = 0;
    long long index = num-x;
    for (long long i = x-1; i>=0; i--){
        if (temp2[i] >= thew){
            thesum += temp2[i];
            count++;
        }
        else{
            rod.push(temp2[i]);
            index++;
            sum[index] = sum[index-1]+temp2[i];
        }
    }
    
    num -= count;
    cout<<thesum<<'\n';
    return;
}
void DD(){
    long long x;
    cin>>x;
    long long thesum = sum[num]-sum[num-x];
    cout<<thesum<<'\n';
    return;
}
