#include <iostream>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

#define grey -1
#define white 0
#define black 1

typedef struct node{
    long long name;
    long long fin;
}Node;

long long N, M;
long long t = 0;
long long parent[3001];
vector<long long> adj[3001];
long long color[3001] = {0};
long long fin[3001] = {0};
long long c[3001];
long long d[3001];
long long price[3001];
long long child[3001] = {0};
long long cnum[3001] = {0};

long long DFS(long long i);
bool cmp(Node x, Node y){
    return x.fin < y.fin;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin>>N>>M;
    for (long long i = 0; i<N; i++){
        long long f;
        cin>>f;
        parent[i] = f;
        if (f >= 0){
            adj[i].push_back(f);
            adj[f].push_back(i);
        }
    }
    
    for (long long i = 0; i<N; i++){
        long long cost, dollar;
        cin>>cost>>dollar;
        c[i] = cost;
        d[i] = dollar;
    }
    for(long long i = 0; i<N; i++){
        if (color[i] == white)
            DFS(i);
    }
    vector <Node> vertex;
    for(long long i = 0; i<N; i++){
        Node v;
        v.fin = fin[i];
        v.name = i;
        vertex.push_back(v);
    }
    /*cout<<'\n';
    for (long long i = 0; i<N; i++){
        cout<<fin[i]<<' ';
    }*/
    sort(vertex.begin(), vertex.end(), cmp);
    
    /*for (long long i = 0; i<N; i++){
        cout<<vertex[i].name<<" "<<cnum[vertex[i].name]<<" "<<child[vertex[i].name]<<"  ";
    }*/
    long long green[N+1][M+1];
    for (long long i = 0; i<=N; i++){
        for (long long j = 0; j<=M; j++){
            green[i][j] = 0;
        }
    }
    for (long long i = 1; i<=N; i++){
        for (long long j = 1; j<=M; j++){
            long long index = vertex[i-1].name;
            long long ctmp = 0;
            long long dtmp = 0;
            //cout<<i-1<<" "<<j-c[index]<<"\n";
            if (i-1 >= 0 && j-c[index] >= 0){
                ctmp = green[i-1][j-c[index]]+c[index];
                //cout<<c[index]<<" ";
            }
            if (i-cnum[index] >= 0 && j-d[index] >= 0)
                dtmp = green[i-cnum[index]][j-d[index]]+child[index];
            //cout<<"|"<<i-cnum[index]<<" "<<child[index]<<"|";
            //printf("%lld-%lld %lld  %lld %lld %lld\n", i, j, index, dtmp, green[i][j]);
            green[i][j] = max(dtmp, ctmp);
            green[i][j] = max(green[i][j], green[i-1][j]);
        }
        /*cout<<vertex[i-1].name<<"-";
        for (long long j = 1; j<=M; j++){
            cout<<green[i][j]<<" ";
        }*/
        //cout<<"\n";
    }
    
    
    


    cout<<green[N][M];

    return 0;
}

long long DFS(long long i){
    color[i] = grey;
    long long length = adj[i].size();
    long long sum = 0;
    long long ccnum = 0;
    for (long long j = 0; j<length; j++){
        if (color[adj[i][j]] == white){
            ccnum += DFS(adj[i][j]);
            sum += child[adj[i][j]];
        }
    }
    sum += c[i];
    ccnum++;
    child[i] = sum;
    cnum[i] = ccnum;
    color[i] = black;
    t++;
    fin[i] = t;
    return ccnum;
}
