#include <iostream>
#include <algorithm>
using namespace std;

long simplebuy(long index, long remain, long *price, long ans);
long smartbuy(long index, long remain, long *price);

long dp[5000][5000];
long N, W;

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin >> N >> W;
    long price[N];
    long index = 0;
    for (long i = 0; i<5000; i++){
        for (long j = 0; j<5000; j++){
            dp[i][j] = -1;
        }

    }
    for (long i = 0; i<N; i++){
        cin>>price[i];
    }

    sort(price,price+N);
    
    for (long i = 1; i <= W; i++){
        long ans = smartbuy(0, i, price)-simplebuy(N-1, i, price, 0);
        //cout<<smartbuy(0, i, price)<<" "<<simplebuy(0, i, price, 0)<<"\n";
        cout <<ans <<"\n";
    }


    return 0;
}

long simplebuy(long index, long remain, long *price, long ans){

    while(index >= 0 && remain > 0){
        if (price[index] <= remain){
            ans += price[index];
            remain -= price[index];
        }
        else{
            index--;
        }
    }
    return ans;

}

long smartbuy(long index, long remain, long *price){
    if (index == N || remain == 0)
        return 0;
    else if (dp[index][remain] != -1)
        return dp[index][remain];
    long no = smartbuy(index+1, remain, price);

    if (remain < price[index]){
        dp[index][remain] = no;
        return dp[index][remain];
    }
    else{
        long yes = price[index]+smartbuy(index, remain-price[index], price);
        dp[index][remain] = max(yes, no);
        return dp[index][remain];
    }

}

/*void quicksort(int *price, int left, int right){
    if (left >= right){
        return;
    }
    int pivot = price[left];
    int l = left;
    int r = right;
    while(l != r){
        while(price[r] > pivot && r > l){
            r--;
        }
        while(price[l] < pivot && l < r){
            l++;
        }
        if (l < r){
            price[l], price[r] = price[r], price[l];
        }
    }

    price[left], price[r] = price[r], price[left];

    quicksort(price, left, right-1);
    quicksort(price, l+1, right);
}*/
