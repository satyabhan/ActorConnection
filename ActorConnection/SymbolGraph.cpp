#include "stdafx.h"
#include "SymbolGraph.h"
#include "Utils.h"
#include <iostream>
#include <fstream> 
#include <sstream>
#include <queue>

int SymbolGraph::index(string node)
{
	int ret = -1;
	unordered_map<string, int>::const_iterator nodeidx = stringToIndex.find(node);
	if (nodeidx != stringToIndex.end())
		ret = nodeidx->second;
	return ret;
}

list<string> SymbolGraph::findConnection(string source, string dest)
{
	list<string> path;
	vector<bool> visited(stringToIndex.size());
	int sourceIdx = index(source), destIdx = index(dest);

	if (sourceIdx < 0 || destIdx < 0)
		return path;

	list<int> intPath = connections.findConnection(sourceIdx, destIdx);

	for (list<int>::const_iterator ipath = intPath.begin(); ipath != intPath.end(); ++ipath)
	{
		path.push_back(indexToString[*ipath]);
	}
	
	return path;
}

SymbolGraph::SymbolGraph(string fileName, char delimiter)
{
	ifstream file;
	file.open(fileName);

	string line;
	while (getline(file, line))
	{
		string node;
		stringstream linestream(line);
		while (getline(linestream, node, delimiter))
		{
			trim_inplace(node);
			if (stringToIndex.find(node) == stringToIndex.end())
			{
				stringToIndex[node] = stringToIndex.size();
			}
		}
	}

	indexToString.resize(stringToIndex.size());
	for (unordered_map<string, int>::const_iterator token = stringToIndex.begin(); token != stringToIndex.end(); ++token)
	{
		indexToString[token->second] = token->first;
	}

	connections.reserve(stringToIndex.size());

	file.clear();
	file.seekg(0, ios::beg);

	while (getline(file, line))
	{
		string root, node;
		int rootIdx, nodeIdx;
		stringstream linestream(line);
		if (getline(linestream, root, delimiter))
		{
			trim_inplace(root);
			rootIdx = stringToIndex.find(root)->second;
			while (getline(linestream, node, delimiter))
			{
				trim_inplace(node);
				nodeIdx = stringToIndex.find(node)->second;
				connections.addEdge(rootIdx, nodeIdx);
			}
		}
	}

}