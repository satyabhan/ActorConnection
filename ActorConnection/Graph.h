#pragma once
#include <unordered_map>

using namespace std;

/**
 *  The Graph class represents an undirected graph of vertices as an adjacency-list.
 *  It supports the following two primary operations: add an edge to the graph and
 *  find the shortest path connection between two vertices. Parallel edges and 
 *  self-loops are permitted.
 */
class Graph
{
private:
	vector<list<int>> connections;
	bool inRange(int edge) { return edge>= 0 && edge < connections.size(); }

public:
	void addEdge(int s, int d);
	void reserve(unsigned int size);
	/**
	* Finds shortest connections between two nodes in graph.
	* @param source an integer source node
	* @param dest an integer destination node
	* @return shortest path between source and dest as list of vertices
	*/
	list<int> findConnection(int source, int dest);
};

