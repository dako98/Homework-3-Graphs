#ifndef _GRAPH_
#define _GRAPH_

#include <unordered_map>

struct Edge
{
	Edge()
	{}

	Edge(std::string name, std::string lockKey)
		:destination(name)
		, lock_key(lockKey)
	{}

	std::string lock_key;
	std::string destination;
};

struct Vertex
{
	Vertex()
		:used(false)
	{}

	Vertex(std::string name)
		:name(name)
		, used(false)
	{}

	std::string name;
	std::vector<std::string> keys;
	std::vector<Edge> edges;
	bool used;
};

using Graph = std::unordered_map<std::string, Vertex>;

#endif // !_GRAPH_
