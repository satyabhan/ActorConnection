// ActorConnection.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iterator>
#include <string>
#include "SymbolGraph.h"
using namespace std;



int _tmain(int argc, _TCHAR* argv[])
{
	string fileName = "testinp.txt";
	char delimiter = '/';
	string source = "Actor2", dest = "Actor10";
	if (argc == 4)
	{
		fileName = argv[0];
		delimiter = argv[1][0];
		source = argv[2];
		dest = argv[3];

	}

	cout << "Building graph...." <<endl;
	SymbolGraph sg(fileName, delimiter);
	cout << "Graph ready!" << endl;

	do
	{
		list<string> connectionPath = sg.findConnection(source, dest);

		if (connectionPath.size())
		{
			cout << "Source[" << source << "] -> Dest[" << dest <<"]" << endl;
			for (list<string>::iterator path = connectionPath.begin(); path != connectionPath.end(); ++path)
				cout << "  ->" << *path << endl;
		}
		else
			cout << "    No connection" << endl;

		cout << endl << "Enter new source (q to quit) : ";
		cin >> source;
		if (source != " ")
		{
			cout << "Enter new dest (q to quit) : ";
			cin >> dest;
		}
	} while (source != "q" && dest != "q");
	
	
	return 0;
}

