#include <bits/stdc++.h>
using namespace std;

// Edges of the graph
struct Edge {
  int u;// source
  int v;// destination
  int w;// weight
};

// Graph
struct Graph {
  int V;// #vertices
  int E;// #edges
  struct Edge* edge; // Array of edges
};

// Createing graph
struct Graph* createGraph (int V, int E) {
  struct Graph* graph = new Graph;
  graph->V = V;// Total Vertices
  graph->E = E;// Total edges

  // Array of edges
  graph->edge = new Edge[E];
  return graph;
}

// Printing the solution
void output (int arr[], int size, int flag[]) {
  // Output file
  FILE *fp = fopen("sd.txt", "w");
    
  for (int i = 0; i < size; i++) {
    fprintf(fp, "%d ",i);
    
    if (arr[i] == INT_MAX)
      fprintf(fp, "+inf");
    else {
      if (flag[i])
        // -ve cycle exists in their path from source
        fprintf(fp, "-inf");
      else
        fprintf(fp, "%d",arr[i]);
    }
    
    fprintf(fp, "\n");
  }
  
  fclose(fp);
}

// BellmanFord algorithm
void Bellman_Ford (struct Graph* graph, int s) {
  int V = graph->V;// #vertices
  int E = graph->E;// #edges
  int dist[V];// array to store shortest distance

  // initially distance is infinity
  for (int i = 0; i < V; i++)
    dist[i] = INT_MAX;

  // distance of source
  dist[s] = 0;

  // array for vertices if -ve cycle exist in their path 
  int flag[V] = {0};
  
  // relax edges
  for (int i = 1; i <= V - 1; i++) {
    for (int j = 0; j < E; j++) {
      int u = graph->edge[j].u;
      int v = graph->edge[j].v;
      int w = graph->edge[j].w;
      if (dist[u] != INT_MAX && dist[u] + w < dist[v])
        dist[v] = dist[u] + w;
    }
  }

  // checking if -ve cycle exists in their path
  for (int i = 1; i <= V - 1; i++) {
    for (int j = 0; j < E; j++) {
      int u = graph->edge[j].u;
      int v = graph->edge[j].v;
      int w = graph->edge[j].w;
      if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
        // -ve cycle exists in the path for vertex v
        dist[v] = dist[u] + w;
        flag[v] = 1;
      }
    }
  }

  // reslut
  output(dist, V, flag);

  return;
}

int main (int argc, char **argv) {
  // Create a graph
  int V;// #vertices
  int E;// #edges
  
  // Input file
  FILE *fp = fopen(argv[1], "r");
  
  // Creating graph
  fscanf(fp, "%d", &V);
  fscanf(fp, "%d", &E);
  struct Graph *graph = createGraph(V, E);
  
  // adding weghted edges to graph
  for (int i = 0; i < E; i++) {
    int u, v, w;// source, destination, weight
    
    fscanf(fp,"%d",&u);
    fscanf(fp,"%d",&v);
    fscanf(fp,"%d",&w);
    
    graph->edge[i].u = u;
    graph->edge[i].v = v;
    graph->edge[i].w = w;
  }
  
  fclose(fp);
  
  // Applying BellmanFord algorithm
  int source = 0;
  Bellman_Ford(graph, source);

  return 0;
}

// Code by: Pranav Kanire