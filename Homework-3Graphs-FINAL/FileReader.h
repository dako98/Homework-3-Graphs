#ifndef _FILE_READER_
#define _FILE_READER_

#include <string>
//#include <vector>
#include <sstream>

#include "Graph.h"


bool Read(const std::string &name, Graph &graph);

void loadOneRow(std::stringstream& ss, std::string& zone1, std::string& zone2, std::string& key);

#endif // !_FILE_READER_
