#include <bits/stdc++.h>
using namespace std;
 
// Creating edge between two given points
void createEdge(vector<int> adj[], int src, int dest)
{
    adj[src].push_back(dest);
    adj[dest].push_back(src);
}

// BFS algo to store predecessor and distance from source
bool BFS(vector<int> adj[], int src, int dest, int v, int pred[], int dist[])
{
    list<int> queue;
 
    // If vertex is in reach from the source
    bool visit[v];
 
    // Initially all vertices are unvisited and
    // dist[i] for all i set to infinity
    for (int i = 0; i < v; i++) {
        visit[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
 
    // Now source is first to be visited and
    // Distance from source to itself should be 0
    visit[src] = true;
    dist[src] = 0;
    queue.push_back(src);
 
    // standard BFS algorithm
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (visit[adj[u][i]] == false) {
                visit[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);
 
                // If destination is reached
                if (adj[u][i] == dest)
                    return true;
            }
        }
    }
 
    return false;
}
 
// Finds shortest distance
int shortestDist(vector<int> adj[], int v, int s, int dest)
{
    // pred[i] array stores predecessor of i
    // dist[i] array stores distance of i from s
    int pred[v], dist[v];
    
    if (s == dest)
        return 0;
        
    if (BFS(adj, s, dest, v, pred, dist) == false)
        return -1;

    return dist[dest];
}

int main (int argc, char *argv[])
{
    // Input file
    FILE *fp = fopen(argv[1], "r");

    // #vertices and #edges
    int v,e;
    
    int c, n = 2, i = 0;
    while (n--) {
        
        c=fgetc(fp);
        while (c >= '0' && c <= '9') {
            i = i*10 + c-48;
            c = fgetc(fp);
        }
        
        if (n > 0)
            v = i;
        else
            e = i;
        
        i = 0;
    }
    
    // Adjecency list
    vector<int> adj[v];
    
    // Create graph
    int ed1,ed2;
    for (int k = 0; k < e; k++) {
        n = 2;
        while (n--) {
            c=fgetc(fp);
            while (c >= '0' && c <= '9') {
                i = i*10 + c-48;
                c = fgetc(fp);
            }
        
            if (n > 0)
                ed1 = i;
            else
                ed2 = i;
        
            i = 0;
        }
        
        createEdge(adj, ed1, ed2);
    }
    
    fclose(fp);
    
    // Output file
    fp = fopen("sd.txt","w");
    
    // Find shortest distance from 0 to every other vertex
    int source = 0;
    for (int dest = 0; dest < v; dest++) {
        int sd = shortestDist(adj, v, source, dest);
        fprintf(fp, "%d\n",sd);
    }
    
    fclose(fp);
    
    return 0;
}

// Code by: Pranav Kanire