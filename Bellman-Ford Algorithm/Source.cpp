#include <iostream>
#include <vector>
using namespace std;

// data structure to store graph edges
struct Edge {
	int src, dest, weight;
};

typedef pair<int, int> Pair;

// class to represent a graph object
class Graph
{
public:
	// construct a vector of vectors of Pairs to represent an adjacency list
	vector<vector<Pair>> adjList;

	// Graph Constructor
	Graph(vector<Edge> const &edges, int N)
	{
		// resize the vector to N elements of type vector<Pair>
		adjList.resize(N);

		// add edges to the directed graph
		for (auto &edge : edges)
		{
			int src = edge.src;
			int dest = edge.dest;
			int weight = edge.weight;

			// insert at the end
			adjList[src].push_back(make_pair(dest, weight));

			// Uncomment below line for undirected graph
			// adjList[dest].push_back(make_pair(src, weight));
		}
	}
};

// print adjacency list representation of graph
void printGraph(Graph const &graph, int N)
{
	for (int i = 0; i < N; i++)
	{
		// print all neighboring vertices of given vertex
		for (Pair v : graph.adjList[i])
			cout << "(" << i << ", " << v.first <<
			", " << v.second << ") ";
		cout << endl;
	}
}

void InitDistance(vector<int> &dist, int size)
{
	for (int i = 0; i < size; i++) {
		dist.push_back(INT32_MAX);
	}
}
void InitEdgePaths(vector<Edge> &EdgeTo, int size)
{
	for (int i = 0; i < size; i++) {
		Edge edge;
		edge.src = -1;
		edge.dest = -1;
		EdgeTo.push_back(edge);
	}
}
int GetNumVertices(vector<Edge> edges)
{
	vector<int> UniqueNodes;
	UniqueNodes.push_back(edges[0].src);
	for (int i = 1; i < edges.size(); i++) {
		if (find(UniqueNodes.begin(), UniqueNodes.end(), edges[i].src) == UniqueNodes.end()) {
			UniqueNodes.push_back(edges[i].src);
		}
	}
	return UniqueNodes.size() + 1;
}

void BellmanFord(vector<int> &dist, vector<Edge> &edges, vector<Edge> &EdgeTo)
{
	dist[0] = 0; //source to source always 0
	for (int i = 0; i < edges.size() - 1; i++)
	{
		for (Edge edge : edges)
		{
			if (dist[edge.dest] > dist[edge.src] + edge.weight)
			{
				dist[edge.dest] = dist[edge.src] + edge.weight;
				EdgeTo[edge.dest] = edge;
			}
		}
	}
}

void PrintShortestPath(vector<Edge> EdgeTo)
{
	vector<int> path;
	int finder = 0;
	for (int i = 1; i < EdgeTo.size(); i++) {
		path.clear();
		finder = i;
		if (EdgeTo[finder].src != 0) {
			path.push_back(EdgeTo[finder].dest);
			while (EdgeTo[finder].src != 0) {
				path.push_back(EdgeTo[finder].src);
				finder = EdgeTo[finder].src;
			}
			path.push_back(EdgeTo[finder].src);

			std::reverse(path.begin(), path.end());		//reverse order 
			cout << "Path to " << i << ": ";
			for (int j = 0; j < path.size() - 1; j++) {
				cout << path[j] << " -> ";
			}
			cout << path[path.size() - 1] << endl;
		}
		else {
			cout << "Path to " << i << ": " << EdgeTo[i].src << " -> " << EdgeTo[i].dest << endl;
		}
	}
}

// Graph Implementation using STL
int main()
{
	vector<Edge> edges =
	{
		// (x, y, w) -> edge from x to y having weight w
		{ 0, 1, 5 }, { 0,4,9 }, { 0,7,8 }, { 1,2,12 },
		{ 1,3,15 }, { 1,7,4 }, { 2,3,3 }, {2,6,11},
		{3,6,9}, {4,5,4}, {4,6,20}, {4,7,5},
		{5,2,1}, {5,6,13}, {7,5,6}, {7,2,7},
	};

	int VerticeCount = GetNumVertices(edges);

	// construct graph
	Graph graph(edges, edges.size());

	//Create distance vector
	vector<int> dist;
	InitDistance(dist, VerticeCount);

	//Keep track of best path
	vector<Edge> EdgeTo;
	InitEdgePaths(EdgeTo, VerticeCount);

	BellmanFord(dist, edges, EdgeTo);	//Perform algorithm

	PrintShortestPath(EdgeTo); //Print shortest paths

	// uncomment to print graph in (source, destination, weight) form
	//printGraph(graph, edges.size());

	system("pause");
	return 0;
}