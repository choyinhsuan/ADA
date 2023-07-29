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
}vertex;

long long V;
long long M;
vector<vertex> map[1000000];
vertex key[1000000];
bool mstSet[1000000] = {0};
long long parent[1000000];
long long record[1000000] = {0};

struct cmp{
	bool operator()(vertex a, vertex b){
			return a.l > b.l;
	}
};

priority_queue<vertex, vector<vertex>, cmp> pq;

void printMST(){
	long long sum = 0;
	for (long long i = 0; i < V; i++){
		sum += record[i];
		//cout<<parent[i]<<" "<<record[i]<<" ";
	}
		//cout << parent[i] << " - " << i << " \t"<< graph[i][parent[i]].c << " \n";
	cout<<sum<<"\n";
	return;
}

void primMST(){

	for (long long i = 0; i < V; i++){
		key[i].l = INT_MAX;
		key[i].id = i;
		parent[i] = -1;
		record[i] = INT_MAX;
    }
	vertex cap = {0, 0, 0};
	key[0] = (vertex){0, 0, 0};
	parent[0] = -1;
	record[0] = 0;
	pq.push(cap);
	long long u = 0;
	while (!pq.empty()){
		vertex cur = pq.top();
		pq.pop();
		long long u = cur.id;
		mstSet[u] = true;
		long long len = map[u].size();
		//cout<<u<<"-";
		for (long long v = 0; v < len; v++){
			vertex ptr = map[u][v];
			//cout<<ptr.id<<" ";
			if (mstSet[ptr.id] == false && ptr.l < key[ptr.id].l){
				parent[ptr.id] = u;
				if (ptr.l < record[ptr.id])
					record[ptr.id] = ptr.l;
				key[ptr.id].l = ptr.l;
				key[ptr.id].id = ptr.id;
				pq.push(key[ptr.id]);
			}
				//cout<<graph[u][v].des<<" "<<graph[u][v].c<<"|";
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
        long long a, b, l;
        cin>>a>>b>>l;
        vertex city;
		city.l = l;
		city.id = b-1;
		map[a-1].emplace_back(city);
		vertex city2;
		city2.l = l;
		city2.id = a-1;
		map[b-1].emplace_back(city2);

		
    }
	primMST();

	return 0;
}
