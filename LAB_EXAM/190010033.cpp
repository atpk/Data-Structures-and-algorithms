// I referred my bfs assignment for this exam
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
 
// Find path from source to destination
void findpath(vector<int> adj[], int v, int s, int dest)
{
    // pred[i] array stores predecessor of i
    // dist[i] array stores distance of i from s
    int pred[v], dist[v];
    
    if (s == dest)
        return;
    
    // If destination can't be reached
    if (BFS(adj, s, dest, v, pred, dist) == false)
        return;
        
    // Output file
    FILE *fp = fopen("directions.txt", "w");
    
    // Creating path from source to destination
    int i = dest;
    vector<int> path;
    path.push_back(i);
    while (pred[i] != s) {
        path.push_back(pred[i]);
        i = pred[i];
    }
    
    // Write path in the output file
    int j = s;
    for (i = path.size()-1; i >= 0; i--) {
        fprintf(fp, "move ");
        
        if (path[i] == j+1)
            fprintf(fp, "north");
        else if (path[i] == j-1)
            fprintf(fp, "south");
        else if (path[i] == j+10)
            fprintf(fp, "east");
        else
            fprintf(fp, "west");
        
        j = path[i];
        fprintf(fp, "\n");
    }
    
    fclose(fp);
    
    return;
}

int main (int argc, char *argv[])
{
    int V = 100;// #vertices
    int E;// #edges
    int home;// destination to be reached
    
    // Adjecency list
    vector<int> adj[V];
    
    // Input file
    FILE *fp = fopen(argv[1], "r");
  
    // Creating graph
    fscanf(fp, "%d", &home);
    fscanf(fp, "%d", &E);
  
    // adding edges to graph
    for (int i = 0; i < E; i++) {
        int u, v;// source, destination
    
        fscanf(fp,"%d",&u);
        fscanf(fp,"%d",&v);
        createEdge(adj, u, v);
    }
  
    fclose(fp);
    
    // Search path using BFS
    int source = 0;
    findpath(adj, V, source, home);
    
    return 0;
}

// Code by: Pranav Kanire