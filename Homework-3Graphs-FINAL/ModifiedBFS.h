#ifndef _MODIFIED_BFS_
#define _MODIFIED_BFS_


#include <iostream>
#include <string>
#include <vector>
#include <ostream>

#include "Graph.h"


bool haveKey(const std::string &key, const std::vector<std::string> &keys);

void PrintVertex(std::ostream &output, const Vertex &vertex, bool reachable);

void ModifiedRecursiveTreeBFS(Graph &graph, Vertex &v_start, std::vector<std::string> keys);

void CheckPassableVertixes(Graph &graph, std::string start);

void _PrintGraph(const Graph &graph, std::ostream &output); //write to file

void PrintGraph(const Graph &graph, const std::string &outputName);

void _PrintGraph(const Graph &graph, std::ostream &output);

void ModifiedRecursiveTreeBFS(Graph &graph, Vertex &v_start, std::vector<std::string> keys);

#endif // !_MODIFIED_BFS_
