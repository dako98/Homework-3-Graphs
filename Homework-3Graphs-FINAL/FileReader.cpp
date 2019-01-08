#include <iostream>
#include <fstream>

#include "FileReader.h"


bool Read(const std::string &name, Graph &graph)
{
	std::ifstream read(name);

	if (!read.good())
	{
		std::cerr << "Could not open file.\n";
		return false;
	}

	std::string begin;
	std::string destination;
	std::string keyName;

	read >> begin;

	std::string line;
	bool readingKeys = false;

	//read all zones
	while (getline(read, line, ';'))
	{
		std::stringstream ss(line);

		if (readingKeys == false &&
			line.find("[keys]") != std::string::npos)
		{
			ss >> begin;
			readingKeys = true;
		}

		if (readingKeys == false)
		{
			loadOneRow(ss, begin, destination, keyName);

			if (graph.count(begin) == 1)
			{
				graph[begin].edges.push_back(Edge(destination, keyName));
			}
			else
			{
				graph[begin] = Vertex(begin);
				graph[begin].edges.push_back(Edge(destination, keyName));
			}

			if (graph.count(destination) == 0)
			{
				graph[destination] = Vertex(destination);;
			}
		}
		else
		{
			loadOneRow(ss, keyName, begin, destination);

			graph[begin].keys.push_back(keyName);
		}
	}
	read.close();
	return true;
}


void loadOneRow(std::stringstream& ss, std::string& zone1,
	std::string& zone2, std::string& key)
{
	std::string tmp;

	char c = 0;
	ss >> c;

	if (c == '"')
	{
		getline(ss, zone1, '"');
	}
	else
	{
		tmp.push_back(c);

		ss >> zone1;
		zone1.insert(0, tmp);
		tmp = "";
	}
	ss >> zone2; // getting the arrow

	ss >> c;
	if (c == '"')
	{
		getline(ss, zone2, '"');
	}
	else
	{
		tmp.push_back(c);

		ss >> zone2;
		zone2.insert(0, tmp);
		tmp = "";
	}

	ss >> c;
	if (c == '[')
		getline(ss, key, ']');
	else
		key = "";

	if (!ss)
		ss.clear();
}