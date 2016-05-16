#include <iostream>
#include <stdbool.h>
#include <algorithm>
#include <stdlib.h>
#include <cstdlib>
using namespace std;

long long N;
typedef struct Record{
    long long cook;
    long long sum;
    long long num;
    long long diff;
}record;

bool cmp(pair<long long, long long> a, pair<long long, long long> b);
bool cmp2(pair<long long, long long> a, pair<long long, long long> b);
bool cmp3(record a, record b);

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>N;
    pair<long long, long long> time[500000];
    record group[500000];
    long long m;

    for (long long i = 0; i<N; i++){
        cin>>m;
        long long cook = 0;
        long long eat = 0;
        for(long long j = 0; j<m; j++){
            cin>>time[j].first>>time[j].second;
            cook += time[j].first;
            eat += time[j].second;
        }
        group[i].cook = cook;
        stable_sort(time, time+m, cmp);
        //cout<<time[0].first<<" "<<time[1].first<<"\n";
        stable_sort(time, time+m, cmp2);
        long long sum = 0;
        long long max = 0;
        for (long long j = m-1; j>=0; j--){
            long long temp = cook-sum+time[j].second;
            sum += time[j].first;
            if (temp > max)
                max = temp;
        }
        group[i].sum = max;
        group[i].num = m;
        group[i].diff = (max-cook);
        //cout<<group[i].cook<<" "<<group[i].sum<<"\n";
    }
    //cout<<group[0].sum;

    stable_sort(group, group+N, cmp3);
    long long sum = 0;
    long long ans = 0;
    for (long long i = 0; i<N; i++){
        ans += (sum+group[i].sum)*group[i].num;
        sum += group[i].cook;
        //cout<<sum<<" "<<ans<<"\n";
        
    }
    cout<<ans;
    return 0;
}

bool cmp(pair<long long, long long> a, pair<long long, long long> b){
    return a.first < b.first;
}
bool cmp2(pair<long long, long long> a, pair<long long, long long> b){
    return a.second > b.second;
}
bool cmp3(record a, record b){
    long long tempa = a.num*b.cook;
    long long tempb = b.num*a.cook;
    return tempa>tempb;
}

