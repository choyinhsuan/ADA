#include <iostream>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

using namespace std;

long compare(long l, long r);
long combine(long l, long mid, long r);
long N;
long mini[500100] = {0};
long recordl[500100] = {0};
long recordr[500100] = {0};
long a[500100];

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);

    cin >> N;
    for(long i = 0; i<N; i++){
        cin >> a[i];
    }
    //record[N] = {0};
    long pairs = 0;
    pairs = compare(0, N-1);
    cout<<pairs;
    return 0;
}

long compare(long l, long r){
    //cout<<a[0]<<" ";
    long pairs = 0;

    if (l == r){
        return pairs;
    }

    else{
        long mid = (r+l)/2;
        //cout<<"Ве"<<l<<"-"<<a[l]<<" "<<r<<"-"<<a[r]<<" "<<pairs<<"\n";
        pairs += compare(l, mid);
        pairs += compare(mid+1, r);
        pairs += combine(l, mid, r);
    }
    return pairs;
}

long combine(long l, long mid, long r){

    long pairs = 0;
    if (l == r)
        return 0;
    mini[mid] = a[mid];
    for (long i = 1; mid+i <= r; i++){
            mini[mid+i] = min(mini[mid+i-1], a[mid+i]);
    }
    for (long i = 1; mid-i >= l; i++){
            mini[mid-i] = min(mini[mid-i+1], a[mid-i]);
    }


    /*cout<<"record ";
    for (long i = l; i<=r; i++){
        cout<<mini[i]<<" ";
    }
    cout<<"\n";*/



    long indexl = mid;
    long indexr = mid+1;
    bool donel = false;
    bool doner = false;
    for (long i = l; i<=r; i++){
        if ((mini[indexl] > mini[indexr] && indexl >= l)||indexr > r){
            long pplus = a[indexl]+mini[indexl];
            long mminus = a[indexl]-mini[indexl];
            pairs += recordr[pplus];
            pairs += recordr[mminus];
            recordl[a[indexl]]++;
            //cout<<a[indexl];
            indexl--;

        }
        else if(indexr <= r || indexl < l){
            long pplus = a[indexr]+mini[indexr];
            long mminus = a[indexr]-mini[indexr];
            pairs += recordl[pplus];
            pairs += recordl[mminus];
            recordr[a[indexr]]++;
            indexr++;
        }

    }
    for (long i = l; i<= mid; i++){
        recordl[a[i]] = 0;
    }
    for (long i = mid+1; i<=r; i++){
        recordr[a[i]] = 0;
    }
    /*cout<<"recordl ";
    for (long i = 1; i<=N; i++){
        cout<<recordl[i]<<" ";
    }
    cout<<"\n";
    cout<<"recordr ";
    for (long i = 1; i<=N; i++){
        cout<<recordr[i]<<" ";
    }
    cout<<"\n";*/


    //cout<<pairs<<"\n";
    return pairs;
}

