#include <vector>
#include <map> 

#include "graph.h"
#include "point.h"
#include "read_file.h" 
#include "dijkstra.h"
#include "path.h"
using namespace std; 

void all_paths(Graph* graph, vector<path>* results, path* shortest_path);
void backtrack(vector<path>* solutions, path* sol,  int s, int d, Graph* graph);
bool accepted_solution(path* p, int s, int d, Graph* graph);



void all_paths(Graph* graph, int s, int d, vector<path>* results, path* shortest_path) {
	// we solve this problem by backtracking: 
	// Given graph G(V,E), s: source, d: destination

	
	vector<path> solutions; 
	path sol; 
	sol.add_node(s);
	
	
	backtrack(&solutions, &sol, s, d, graph); 

	for (int i = 0; i < 4; i++) 
	printf("*****************************\n"); 

	Dijkstra dij; 
	vector<pnode> pnodes = dij.run(graph, s);
	int cost = 0; 

	vector<int> shortest_p; 
	dij.shortest_path(&pnodes, s, d, &shortest_p, &cost);

	for (int i = 0; i < 4; i++) 
	printf("*****************************\n"); 

}

void backtrack(vector<path>* solutions, path* sol,  int s, int d, Graph* graph) { 
	
	printf("path is : ");
	sol->print_path();

	if (accepted_solution(sol, s, d, graph)) { 
		sol->cost = sol->p.size() - 1; 
		solutions->push_back(*sol); 

		printf("*** adding solution: "); 
		sol->print_path();

		// this is a cut of a branch
		// sol->remove_last_node(); 
		return; 
	}
	
	 
	vector<int> possible = graph->neighbors(sol->get_last_node()); 
	
	printf("possible neighbors: ");
	for (int i = 0; i < possible.size(); i++) 
		printf("%d ", possible[i]);
	printf("\n");	

	for (int i = 0; i < possible.size(); i++) { 
		
		if (! sol->is_in_path(possible[i]) ) {
			sol->add_node(possible[i]); 
			printf("at node: %d ,adding node: %d \n", sol->get_last_node(), possible[i]);
			backtrack(solutions, sol, s, d, graph); 
			sol->remove_last_node();
		}
	}
	
	return; 

}

bool accepted_solution(path* sol, int s, int d, Graph* graph) { 
	return (sol->p[0] == s && sol->p[sol->p.size()-1] == d);
}
