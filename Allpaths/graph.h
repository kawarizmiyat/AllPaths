#ifndef __GRAPH_H
#define __GRAPH_H

#include <stdio.h>
#include <map>
#include <vector>
#include <algorithm>
#include "point.h"
#include <math.h>
using namespace std; 

#define MAX_DIST 1000

const int RANGE = 5; 


class Graph { 
	
public: 
	map<int, vector<int> > graph; 
	vector<int> nodes; 
	vector<point> nodes_position; 
	vector< vector<int> > edges_costs; 
	bool eucilidean_graph; 
	bool graph_with_costs; 

public: 
	Graph() { eucilidean_graph = false; graph_with_costs = false;  }
	void initializeGraph(map<int, vector<int> >* g);
	void initializeGraph(map<int, vector<int> >* g, vector<point>* p);
	void initializeGraph(map<int, vector<int> >* g, vector<vector<int> >* costs);
	void set_edges_cost(vector<vector<int> >* g); 

	vector<int> neighbors(int u); 
	double dist(int,int);
	double euc_dist(int u, int v); 
	bool is_in_range(point* p1, point* p2);
	double get_euc_distance(point* p1, point* p2); 

	void printGraph();

};	


void Graph::printGraph() { 
	map<int, vector<int> >::iterator it = this->graph.begin(); 
	while (it != this->graph.end()) { 
		printf("%d ", it->first); 
		if (eucilidean_graph)
			printf("(%2.2f: %2.2f) ", nodes_position[it->first].x_axis, nodes_position[it->first].y_axis);
		
		printf(": ");
		for (int i = 0; i < it->second.size(); i++) 
			printf("%d ", it->second[i]);
		printf("\n");

		it ++;
	}

}

void Graph::initializeGraph(map<int, vector<int> >* g) {
	this->graph = *g; 
	map<int, vector<int> >::iterator it = g->begin(); 
	while (it != g->end()) { 
		nodes.push_back(it->first);
		it++; 
	} 
}

void Graph::initializeGraph(map<int, vector<int> >* g, vector<point>* p) { 
	initializeGraph(g);	
	nodes_position = *(p); 
	eucilidean_graph = true; 
}

void Graph::initializeGraph(map<int, vector<int> >* g, vector<vector<int> >* p) { 
	initializeGraph(g); 
	edges_costs = *(p);
	graph_with_costs = true;
}

void Graph::set_edges_cost(vector<vector<int> >* p) { 
	edges_costs = *p; 
	graph_with_costs = true; 
}


vector<int> Graph::neighbors(int u) { 
	return this->graph[u];
}

double Graph::dist(int u, int v) { 
	if (eucilidean_graph) return euc_dist(u,v);
	if (graph_with_costs) return edges_costs[u][v]; 

	vector<int> neighbors_u = neighbors(u); 

	for (int i =0; i < neighbors_u.size(); i++) 
		if (neighbors_u[i] == v) return 1; 
	return MAX_DIST; 
}

double Graph::euc_dist(int u, int v) { 
	if (is_in_range(&nodes_position[u], &nodes_position[v]))
		return get_euc_distance(&nodes_position[u], &nodes_position[v]);
	else 
		return MAX_DIST;
}

bool Graph::is_in_range( point* p1, point* p2) { 
	if (!p1) { printf("p1 must be intitialized \n"); abort();} 
	if (!p2) { printf("p2 must be intitialized \n"); abort();} 
	
	return (get_euc_distance(p1, p2) <= RANGE); 
}

double Graph::get_euc_distance(point* p1, point* p2){ 
	
	if (!p1) { printf("p1 must be intitialized \n"); abort();} 
	if (!p2) { printf("p2 must be intitialized \n"); abort();} 

	return sqrt( pow(p1->x_axis - p2->x_axis, 2) + pow(p1->y_axis - p1->y_axis, 2));  
	
}


#endif 

