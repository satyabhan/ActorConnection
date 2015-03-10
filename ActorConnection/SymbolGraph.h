#pragma once

#include <unordered_map>
#include <list>
#include "Graph.h"
using namespace std;

/**
*  The SymbolGraph class provides a wrapping for Graph class, mapping string vertices
*  to integers. The class maintains an unordered mapping of keys to indexs and a
*  vector of indexs to keys for fast lookup.
*/
class SymbolGraph
{
private:
	unordered_map<string, int> stringToIndex;
	vector<string> indexToString;
	Graph connections;
public:
	/**
	* Builds a SymbolGraph from a file. Format of input is as follows:
	* Node1/vertex/vertex/vertex
	* Node2/vertex/vertex
	* and so on. Delimiling character is passed as argument. Parallel edges and
	* self loops are allowed
	* eg.
	* Movie1/Actor0/Actor1/Actor2/Actor3
	* Movie2/Actor0/Actor4
	* Movie3/Actor0/Actor5/Actor6
	* Movie4/Actor4/Actor5/Actor10
	* @param source as string of source node
	* @param dest as string of destination node
	* @return shortest path between source and dest as list of vertices
	*/
	SymbolGraph(string fileName, char delimiter);
	bool contains(string node) { return stringToIndex.find(node) != stringToIndex.end(); }
	int index(string node);
	/**
	* Finds shortest connections between two nodes in graph.
	* eg. for above example Actor2 is connected to Actor10 via
	* Actor2->Movie1->Actor0->Movie3->Actor5->Movie4->Actor10
	* @param source as string of source node
	* @param dest as string of destination node
	* @return shortest path between source and dest as list of vertices
	*/
	list<string> findConnection(string source, string dest);
};

