#include <iostream>
#include <string>

#include "Graph.h"
#include "ModifiedBFS.h"
#include "FileReader.h"



int main()
{
	Graph graph;

	std::string fileName;

	std::cout << "File name: ";
	std::cin >> fileName;

	if (!Read(fileName, graph))
	{
		return -1;
	}


	std::string startingVertex;
	std::cout << "Starting vertex name: ";
	std::cin >> startingVertex;

	CheckPassableVertixes(graph, startingVertex);


	std::string output(fileName + ".dot");
	PrintGraph(graph, output);


	return 0;
}
