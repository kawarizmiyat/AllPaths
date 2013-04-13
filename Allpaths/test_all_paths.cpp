#include "all_paths.h"
#include "path.h" 
#include "read_file.h"

#include <vector>
#include <map>

using namespace std; 



int main() { 

// void all_paths(Graph* graph, vector<path>* results, path* shortest_path)

	Graph graph; 
	path s_path;
	vector<path> results; 
	map<int, vector<int> > m_graph; 
	char file_name[50];

	int experiment_num = 4; 
	sprintf(file_name, "graphs/graph.out", experiment_num);
	printf("reading file %s \n", file_name);
	extract_graph(&m_graph, file_name);

	graph.initializeGraph(&m_graph);


	int s = 0; 
	int d = 1; 
	all_paths(&graph, s, d, &results, &s_path); 
	
	return 0; 
}

