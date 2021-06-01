#include <bits/stdc++.h>
using namespace std;

// Graph edge
struct Edge {
	int src, dest;
};

// Graph object
class Graph
{
public:
	// Adjacency list
	vector<vector<int>> adjList;

	// Graph Constructor
	Graph(vector<Edge> const &edges, int N)
	{
		adjList.resize(N);

		// add edges to the Directed graph
		for (auto & edge: edges)
			adjList[edge.src].push_back(edge.dest);
	}
};

// Algorithm
void DFS (Graph const & graph, int v, vector<bool> & discovered, vector<int> & departure, int & time)
{
	discovered[v] = true;

	time++;

	// performing for all edges
	for (int u : graph.adjList[v])
	{
		if (!discovered[u])
			DFS(graph, u, discovered, departure, time);
	}
	
	// Backtrack
	departure[time] = v;
	time++;
}

// performs Topological Sort on a given DAG
void topologicalSort (Graph const & graph, int N, FILE *fp)
{
	vector<int> departure(2*N, -1);
	
	vector<bool> discovered(N);
	int time = 0;

	// perform DFS on all undiscovered vertices
	for (int i = 0; i < N; i++)
		if (!discovered[i])
			DFS(graph, i, discovered, departure, time);

	// Output
	for (int i = 2*N - 1; i >= 0; i--)
		if (departure[i] != -1)
			fprintf(fp,"%d\n",departure[i]);
}

int main (int argc, char **argv)
{
	// #vertices and #edges
	int N,M;
	
	// vector of graph edges
	vector<Edge> edges;
	
	// Input through file
	FILE *fp = fopen(argv[1], "r");
	
	// Read #vertices and #edges
	int c, n = 2, i = 0;
    while (n--) {
        
        c=fgetc(fp);
        while (c >= '0' && c <= '9') {
            i = i*10 + c-48;
            c = fgetc(fp);
        }
        
        if (n > 0)
            N = i;
        else
            M = i;
        
        i = 0;
    }
    
    // Read directed edges
    int ed1, ed2;
    for (int k = 0; k < M; k++) {
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
        // Adding edges
        edges.push_back({ed1, ed2});
    }
    
    fclose(fp);

	// create a graph from edges
	Graph graph(edges, N);

	//  Outputting Topological Sort
	fp = fopen("ts.txt", "w");
	topologicalSort(graph, N, fp);
	fclose(fp);

	return 0;
}

// Code by: Pranav Kanire