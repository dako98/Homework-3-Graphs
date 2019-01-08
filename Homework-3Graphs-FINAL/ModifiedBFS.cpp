#include <queue>
#include <fstream>

#include "ModifiedBFS.h"

bool haveKey(const std::string &key, const std::vector<std::string> &keys)
{
	int countOfKeys = keys.size();

	for (int a = 0; a < countOfKeys; a++)
	{
		if (key == "" || keys[a] == key) return true;
	}
	return false;
}


void PrintVertex(std::ostream &output, const Vertex &vertex, bool reachable)
{
	//print edges
	for (const Edge &edge : vertex.edges)
	{
		output << vertex.name << " -> " << edge.destination;
		if (edge.lock_key != "")
		{
			output << "[label=\"" << edge.lock_key << "\"]";
		}
		output << ";\n";
	}

	//print vertex
	if (!reachable || vertex.keys.size() != 0)
	{
		output << vertex.name << "[";

		if (vertex.keys.size() != 0)
		{
			output << "label=\"" << vertex.name;

			for (const std::string &key : vertex.keys)
			{
				output << "\\l" << key;
			}
			output << "\" ";
		}

		if (!reachable)
		{
			if (vertex.keys.size() != 0)
			{
				output << " ,";
			}
			output << "color=red,style=filled,fillcolor=\"#ffefef\"";
		}

		output << "];\n";
	}
}

void CheckPassableVertixes(Graph &graph, std::string start)
{
	std::vector<std::string> keys;
	keys.push_back("");

	ModifiedRecursiveTreeBFS(graph, graph[start], keys);
}


void PrintGraph(const Graph &graph, const std::string &outputName)
{
	if (outputName != "")
	{
		std::ofstream write(outputName);
		if (!write.good())
		{
			std::cerr << "Could not open file.\n";
			return;
		}
		_PrintGraph(graph, write);	//write to file
		write.close();
	}
	else
		_PrintGraph(graph, std::cout);	//write to console

}

void _PrintGraph(const Graph &graph, std::ostream &output)
{
	output << "digraph Map {\n";
	for (const auto &vertex : graph)
	{
		PrintVertex(output, vertex.second, vertex.second.used);
	}
	output << '}';
}



void ModifiedRecursiveTreeBFS(Graph &graph, Vertex &v_start, std::vector<std::string> keys)
{
	std::unordered_map<std::string, bool> used;

	for (auto &vertex : graph)
	{
		used[vertex.second.name] = false;
	}

	std::queue<Vertex*> que;

	que.push(&v_start);

	Vertex* current;

	while (que.size())
	{
		current = que.front();
		que.pop();

		if (used[current->name]) continue;

		current->used = true;
		used[current->name] = true;


		//for each key we find
		int keysInVertexCount = current->keys.size();

		for (int a = 0; a < keysInVertexCount; a++)
		{
			if (!haveKey(current->keys[a], keys))
			{
				keys.push_back(current->keys[a]);
				ModifiedRecursiveTreeBFS(graph, *current, keys);
				keys.pop_back();
			}
		}

		//adding available edges
		int edgesInVertexCount = current->edges.size();

		for (int a = 0; a < edgesInVertexCount; a++)
		{
			if (haveKey(current->edges[a].lock_key, keys))
			{
				que.push(&graph[current->edges[a].destination]);
			}
		}
	}
}