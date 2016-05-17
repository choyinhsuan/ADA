#include <iostream>
#include <stdbool.h>
#include <stdlib.h>
using namespace std;

long long n, k;
long long a[1500];
long long record[1500][1500] = {0};
long long dp[1500][550] = {0};
long long discomfort(long long r, long long l);
//long findcut(long r, long l);


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>k;
    for (long long i = 0; i<n; i++){
        cin>>a[i];
    }
    for (long long i = 0; i<n; i++){
        for (long long j = 0; j<=i; j++){
            //cout<<i<<" "<<j<<" ";
            record[i][j] = discomfort(i, j);
            //cout<<record[i][j]<<" ";
            record[i][j] *= (i-j+1);
            //cout<<record[i][j]<<"\n";
        }
    }
    
    /*long long mini = 1000000;
    for (long long i = 0; i<n-1; i++){
        long long sum = record[n-1][i+1]+ record[i][0];
        if (sum < mini)
            mini = sum;
    }
    cout<<mini;*/
    for (long long i = n-1; i>=0; i--){
        for (long long j = 0; j<k; j++){
            dp[i][j] = 10000000000000;
            for (long long l = i; l<n; l++){
                if (j > 0){
                    dp[i][j] = min(dp[i][j], record[l][i]+dp[l+1][j-1]);
                }
                else
                    dp[i][j] = record[n-1][i];
                //cout<<i<<" "<<j<<"  "<<l<<" "<<dp[i][j]<<"\n";
            }
        }
    }
    cout<<dp[0][k-1]<<"\n";
    return 0;

}

long long discomfort(long long r, long long l){
    long long current = a[l];
    long long max = a[l];
    for (long long i = l+1; i<=r; i++){
        current += a[i];
        if (current < a[i]){
            current = a[i];
        }
        if (current > max){
            max = current;
        }
        //printf("%d\n", current);
        //printf("%d ", max);
    }
    return max;
}
/*long findcut(long r, long l){
    long num = k-1;
    for (long i = 0; i<n; i++){
        for (long j = num; j>record[])
    }
}*/