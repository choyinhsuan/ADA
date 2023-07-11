#include <bits/stdc++.h>
using namespace std;
#define INF INT_MAX
 

typedef pair<long long, long long> iPair;
 
class Graph {
    long long V; 

    list<pair<long long, long long> >* adj;
 
public:
    Graph(long long V);
    void addEdge(long long u, long long v, long long w);
    void eraseEdge(long long u);
    long long shortestPath(long long s);
};
 
Graph::Graph(long long V){
    this->V = V;
    adj = new list<iPair>[V];
}
 
void Graph::addEdge(long long u, long long v, long long w){
    adj[u].push_back(make_pair(v, w));
}
void Graph::eraseEdge(long long u){
    adj[u].pop_back();
}

long long Graph::shortestPath(long long src)
{
    priority_queue<iPair, vector<iPair>, greater<iPair> >
        pq;
 
    
    vector<long long> dist(V, INF);

    pq.push(make_pair(0, src));
    dist[src] = 0;
 
    while (!pq.empty()) {
    
        long long u = pq.top().second;
        pq.pop();
 
        list<pair<long long, long long> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            
            long long v = (*i).first;
            long long weight = (*i).second;
 
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    long long sum = 0;
    for (long long i = 0; i<V; i++){
        sum += dist[i];
    }

    return sum;
}
 
int main()
{
    long long V;
    cin>>V;
    long long M;
    cin>>M;
    Graph g(V);
    for (long long i = 0; i<M; i++){
        long long a, b, c;
        cin>>a>>b>>c;
        g.addEdge(a-1, b-1, c);
    }
    
    g.shortestPath(0);
    long long min = -1;
    for (long long i = 0; i<V; i++){
        g.addEdge(0, i, 0);
        long long sum = g.shortestPath(0);
        if (sum < min || min == -1)
            min = sum;
        g.eraseEdge(0);
    }
    printf("%lld", min);
 
    return 0;
}
