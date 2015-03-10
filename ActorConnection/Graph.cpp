#include "stdafx.h"
#include "Graph.h"
#include <queue>


void Graph::reserve(unsigned int size)
{
	connections.resize(size);
}

void Graph::addEdge(int s, int d)
{
	if (inRange(s) && inRange(d))
	{
		connections[s].push_back(d);
		connections[d].push_back(s);
	}
}

list<int> Graph::findConnection(int source, int dest)
{
	list<int> path;
	vector<bool> visited(connections.size());
	vector<int>  edgeTo(connections.size());

	if (!inRange(source) || !inRange(dest))
		return path;

	if (source == dest)
	{
		path.push_back(source);
		return path;
	}

	bool connectionFound = false;
	queue<int> nodesToCheck;
	nodesToCheck.push(source);
 
	//BFS through graph
	while (!nodesToCheck.empty() && !connectionFound)
	{
		int currentNode = nodesToCheck.front();
		if (!visited[currentNode])
		{
			visited[currentNode] = true;
			for (list<int>::const_iterator connection = connections[currentNode].begin(); connection != connections[currentNode].end(); ++connection)
			{
				if (!visited[*connection])
				{
					edgeTo[*connection] = currentNode;
					if (*connection == dest)
					{
						connectionFound = true;
						break;
					}
					nodesToCheck.push(*connection);
				}
			}
		}
		nodesToCheck.pop();
	}

	//Create path list from dest to source
	if (connectionFound)
	{
		path.push_front(dest);
		while (edgeTo[dest] != source)
		{
			path.push_front(edgeTo[dest]);
			dest = edgeTo[dest];
		}
		path.push_front(source);
	}

	return path;
}