#include <iostream>
#include <limits.h>
#include <stdbool.h>
#include <vector>
#include <list>
#include <stdio.h>
#include <queue>
using namespace std;

typedef struct Vertex{
	long long id;
    long long l;
    long long c;
    long long record;
}vertex;

long long V;
long long M;
vector<vertex> map[1000000];
vertex key[1000000];
bool mstSet[1000000] = {0};
long long parent[1000000];

struct cmp{
	bool operator()(vertex a, vertex b){
        if (a.l != b.l)
			return a.l > b.l;
        else
            return a.c > b.c;
	}
};

priority_queue<vertex, vector<vertex>, cmp> pq;

void printMST(){
	long long sum = 0;
	for (long long i = 0; i < V; i++){
		sum += key[i].c;
		
	}
		
	cout<<sum<<"\n";
	return;
}

int check(long long a, long long b){
    if (a > b){
        return 0;
    }
    else if (a == b){
        return 1;
    }
    else{
        return 2;
    }
}

void primMST(){

	for (long long i = 0; i < V; i++){
		key[i].l = INT_MAX;
        key[i].c = INT_MAX;
		key[i].id = i;
        key[i].record = -1;
		parent[i] = -1;
    }
	vertex cap = {0, 0, 0, -1};
	parent[0] = -1;
    key[0] = (vertex){0, 0, 0, -1};
	pq.push(cap);
	while (!pq.empty()){
		vertex cur = pq.top();
		pq.pop();
		long long u = cur.id;
		mstSet[u] = true;
		long long len = map[u].size();
		//cout<<u<<" : \n";
		for (long long v = 0; v < len; v++){
			vertex ptr = map[u][v];
            if (mstSet[ptr.id] == false){
                //cout<<ptr.id<<"-"<<key[ptr.id].c<<" "<<key[ptr.id].l<<" "<<key[ptr.id].record<<" ";
                vertex ptr2 = ptr;
                //cout<<"++"<<ptr2.c<<"++";
                if (ptr.l < key[ptr.id].l){
                    ptr2.record = key[ptr.id].record;
                    switch(check(ptr.l, key[u].record)){
                        case 0:
                            ptr2.record = ptr.l;
                            break;
                        case 1:
                            ptr2.c = ptr.c + key[u].c;
                            ptr2.record = key[u].record;
                            break;
                        case 2:
                            ptr2.c = key[u].c;
                            ptr2.record = key[u].record;
                            break;
                    }
                    key[ptr.id] = ptr2;
                    parent[ptr.id] = u;
                    pq.push(key[ptr.id]);
                }
                else if (ptr.l == key[ptr.id].l){
                    ptr2.record = key[u].record;
                    switch(check(ptr.l, key[u].record)){
                        case 0:
                            ptr2.record = ptr.l;
                            break;
                        case 1:
                            ptr2.c = ptr.c + key[u].c;
                            ptr2.record = key[u].record;
                            break;
                        case 2:
                            ptr2.c = key[u].c;
                            ptr2.record = key[u].record;
                            break;
                    }
                    if (ptr2.c < key[ptr.id].c){
                        key[ptr.id] = ptr2;
                        parent[ptr.id] = u;
                        pq.push(key[ptr.id]);
                    }
                }
            }
            /*cout<<"|";
            cout<<ptr.id<<"-"<<key[ptr.id].c<<" "<<key[ptr.id].l<<" "<<key[ptr.id].record<<"\n";*/
        }
		
	}
	printMST();
	return;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    cin>>V>>M;
	for (long long i = 0; i<M; i++){
        long long a, b, l, c;
        cin>>a>>b>>l>>c;
        vertex city;
		city.l = l;
		city.id = b;
        city.c = c;
		map[a].emplace_back(city);
		vertex city2;
		city2.l = l;
		city2.id = a;
        city2.c = c;
		map[b].emplace_back(city2);
    }
	primMST();

	return 0;
}
