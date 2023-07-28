#include <iostream>
#include <stack>
#include <vector>
#include <stdbool.h>
#include <algorithm>
#include <stdlib.h>
#include <cstdlib>
using namespace std;
#define white -1
#define grey -2
#define black -3

typedef struct Vertex{
    long long dic;
    long long fin;
    long long pre;
    int color;
    long long index;
}vertex;

void DFS(long long i);
void DFSt(long long i);
void set(long long i);

long long vnum;
long long ednum;
vertex vertice[500050];
pair <long long, long long> radj[500050];
vector <long long> adj[500050];
vector <long long> adjt[500050];
long long scc[500050];

long long t = 0;
long long record[500050] = {0};
long long record1[500050] = {0};
long long record2[500050] = {0};
long long ans = 0;
long long cal = 0;
long long time2 = 0;

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    scanf("%lld%lld", &vnum, &ednum);
    for (long long i = 0; i<ednum; i++){
        long long a, b;
        scanf("%lld%lld", &a, &b);
        record1[a]++;
        record2[b]++;
        radj[i].first = a;
        radj[i].second = b;
    }
    for (long long i = 0; i<=vnum; i++){
        if (record1[i] != 0)
            adj[i].resize(record1[i]);
        if (record2[i] != 0)
            adjt[i].resize(record2[i]);
        record1[i] = 0;
        record2[i] = 0;
    }
    for (long long i = 0; i<ednum; i++){
        long long x = radj[i].first;
        long long y = radj[i].second;
        adj[x][record1[x]] = y;
        adjt[y][record2[y]] = x;
        record1[x]++;
        record2[y]++;
    }
    
    for (long long i = 1; i<=vnum; i++){
        vertice[i].color = white;
        vertice[i].pre = -1;
        vertice[i].index = i;
    }
    t = 0;
    for (long long i = 1; i<=vnum; i++){
        if (vertice[i].color == white){
            DFS(i);
        }
    }
    
    for (long long i = 1; i<=vnum; i++){
        vertice[i].pre = -1;
    }
    
    t = 0;

    for (long long i = 0; i<vnum; i++){
        long long index = record[vnum-i];
        if (vertice[index].color == black){
            cal = 0;
            DFSt(index);
            ans += cal*(cal-1)/2;
        }
    }
    
    cout<<ans<<"\n";
    
    return 0;
}

void DFS(long long i){
    vertice[i].color = grey;
    t++;
    vertice[i].dic = t;
    long long length = record1[i];
    for (long long j = 0; j<length; j++){
        if (vertice[adj[i][j]].color == white){
            vertice[adj[i][j]].pre = i;
            DFS(adj[i][j]);
        }
    }
    vertice[i].color = black;
    t++;
    vertice[i].fin = t;
    time2++;
    record[time2] = i;
    return;
}
void DFSt(long long i){
    cal++;
    vertice[i].color = grey;
    long long length = record2[i];
    for (long long j = 0; j<length; j++){
        if (vertice[adjt[i][j]].color == black){
            vertice[adjt[i][j]].pre = i;
            DFSt(adjt[i][j]);
        }
    }
    vertice[i].color = white;
    return;
}

