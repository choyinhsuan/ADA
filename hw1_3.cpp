#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include <stdbool.h>
using namespace std;
long inversion(long l, long r);
long combine(long l, long r, long mid);
long N;
typedef struct XY{
    long x;
    long y;
    long c;
}xy;
xy x_y[1000100];
bool two = false;
bool compare(xy a, xy b){
    return a.x < b.x;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);

    cin>>N;
    long l1, l2, r1, r2;
    cin>>l1>>l2>>r1>>r2;


    for (long i = 0; i<N; i++){
        cin>>x_y[i].x>>x_y[i].y;
        x_y[i].c = (r1*x_y[i].x-r2*x_y[i].y)*r2;
    }

    long l, r;
    l = l1/l2;
    r = r1/r2;
    sort(x_y, x_y+N, compare);

    long pairs = 0;
    if (l == -1000000000){
        pairs += inversion(0, N-1);
    }
    else{
        pairs += inversion(0, N-1);
        two = true;
        sort(x_y, x_y+N, compare);
        for (long i = 0; i<N; i++){
            x_y[i].c = (l1*x_y[i].x-l2*x_y[i].y)*l2;
        }
        pairs -= inversion(0, N-1);

    }
    cout<<pairs;
    return 0;
}
long inversion(long l, long r){
    long pairs = 0;
    if (l == r)
        return pairs;
    else{
        long mid = (r+l)/2;
        pairs += inversion(l, mid);
        pairs += inversion(mid+1, r);
        pairs += combine(l, r, mid);
    }
    return pairs;
}
long combine(long l, long r, long mid){
    long pairs = 0;
    long lindex = 0;
    long rindex = 0;
    xy left[mid-1+1+5];
    xy right[r-mid+5];
    for (long i = 0; i <= r-l; i++){
        if (i < mid-l+1)
            left[i] = x_y[l+i];
        else
            right[i-mid+l-1] = x_y[l+i];
    }
    for (long i = l; i <= r; i++){
        if (lindex >= mid-l+1){
            x_y[i] = right[rindex];
            rindex++;
        }
        else if (rindex >= r-mid){
            x_y[i] = left[lindex];
            lindex++;
        }
        else if (left[lindex].c < right[rindex].c || (left[lindex].c == right[rindex].c && two == false)){
            pairs += (mid+1)-(l+lindex);
            x_y[i] = right[rindex];
            rindex++;
        }
        else{
            x_y[i] = left[lindex];
            lindex++;
        }
    }


    return pairs;
}

