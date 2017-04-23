#include <iostream>
#include <string.h>
#include <queue>
#include <graph.h>
#include <fstream>
#include <sstream>
using namespace std;
int nodesize = 10;
string inputfile = "input.txt";
graph g;

bool bfs(int rGraph[][nodesize], int s, int t, int parent[])
{
    bool visited[nodesize];
    memset(visited, 0, sizeof(visited));
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
 
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 0; v < nodesize; v++)
        {
            if (visited[v] == false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return (visited[t] == true);
}
 
int fordFulkerson(int graph[nodesize][nodesize], int s, int t)
{
    int u, v;
    int rGraph[nodesize][nodesize];  
    for (u = 0; u < nodesize; u++)
    {
        for (v = 0; v < nodesize; v++)
        {
            rGraph[u][v] = graph[u][v];
        }
    }
    int parent[nodesize];
    int max_flow = 0;
    while (bfs(rGraph, s, t, parent))
    {
		//use openmp to find the min rgraph(u)(v)
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
		//use openmp to update
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}
int main()
{
	g = new graph(nodesize);
	ifstream myfile;
	myfile.open(inputfile);
	string inputline;
	stringstream ss;
	while (!myfile.eof) {
		getline(myfile,inputline);
		ss << inputline;
		int i;
		for (i =0; i<3;i++){
			int a1,a2,a3;
			ss >> a1;
			ss >> a2;
			ss >> a3;
			g.addEdge(a1, a2,a3);
			g.addEdge(a2,a1,-a3);
		}
	}
	myfile.close();
  
    cout << "The maximum possible flow is " << fordFulkerson(g.adjacencyMatrix, 0, nodesize-1);
    getch();
}