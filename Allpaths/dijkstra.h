#ifndef __DIJKSTRA_H
#define __DIJKSTRA_H

#include <stdio.h>
#include <map>
#include <vector>
#include <algorithm>
#include "graph.h"
using namespace std; 

#define MAX_DIST 1000

const bool d = false; 

struct pnode { 
	int id; 
	double cost; 
	int previous; 
	bool removed; 

  	bool operator==(const pnode &other) const {
    	return (this->id == other.id);
  	}

	pnode& operator=(const pnode &other) {
		this->id = other.id; 
		this->cost = other.cost;
		this->previous = other.previous; 
		this->removed = other.removed; 
	
    	return *this;  
  }

};

class Dijkstra { 

	public:
		Dijkstra() { }
		
		Dijkstra(Graph* g); 
		vector<pnode> run(Graph* g, int source); 
		int extractSmallestDistance(vector<pnode>* dist); 
		void removeNode(vector<int>*, int);

		vector<int> intersection(vector<int> n_1, vector<int> n_2);
		void initialize_graph(Graph* g);


		void set_removed(vector<pnode>*, int);
		bool get_removed(vector<pnode>*, int);
		double get_cost(vector<pnode>*, int);
		void set_cost(vector<pnode>*, int, double );	
		int get_previous(vector<pnode>*, int);
		void set_previous(vector<pnode>*, int, int );	

		void shortest_path(vector<pnode>* pnodes, int source, int destination, vector<int>* path, int* cost);
		pnode find_pnode(vector<pnode>* pnodes, int d); 

		void print_pnodes(vector<pnode>* pnodes);
	public:
		vector<pnode> pnodes;
		Graph* graph; 

};


void print_array(vector<int>* a) { 
	for (int i = 0; i < a->size(); i++) 
		printf("%d ", a->at(i));
	printf("\n");
	
}



Dijkstra::Dijkstra(Graph* g) { 
	initialize_graph(g);
}

void Dijkstra::initialize_graph(Graph* g){ 
	if (!g) return; 
	map<int, vector<int> >::iterator it = g->graph.begin();	
	while (it != g->graph.end()) { 
		pnode p; 
		p.id = it->first; 
		p.cost = MAX_DIST; 
		p.removed = false;
		p.previous = -1; 
		pnodes.push_back(p);
		it ++;
	}

	this->graph = g; 
}

void Dijkstra::set_removed(vector<pnode>* pnodes, int u ) {
	for (int i = 0; i < pnodes->size(); i++) { 
		if (pnodes->at(i).id == u) { 
			pnodes->at(i).removed = true;
			return;
		}
	}
}

bool Dijkstra::get_removed(vector<pnode>* pnodes, int u) { 
	for (int i = 0; i < pnodes->size(); i++) { 
		if (pnodes->at(i).id == u) { 
			return (pnodes->at(i).removed);
		}	
	}
}

void Dijkstra::set_cost(vector<pnode>* pnodes, int u, double cost) { 
	for (int i = 0; i < pnodes->size(); i++) { 
		if (pnodes->at(i).id == u) { 
			pnodes->at(i).cost = cost;
			return;
		}
	}
}

double Dijkstra::get_cost(vector<pnode>* pnodes, int u) { 
	for (int i = 0; i < pnodes->size(); i++) { 
		if (pnodes->at(i).id == u) { 
			return (pnodes->at(i).cost);
		}	
	}	
}

void Dijkstra::set_previous(vector<pnode>* pnodes, int u, int previous) { 
		for (int i = 0; i < pnodes->size(); i++) { 
		if (pnodes->at(i).id == u) { 
			pnodes->at(i).previous = previous;
			return;
		}
	}
}

int Dijkstra::get_previous(vector<pnode>* pnodes, int u) { 
	for (int i = 0; i < pnodes->size(); i++) { 
		if (pnodes->at(i).id == u) { 
			return (pnodes->at(i).previous);
		}	
	}	
}

void Dijkstra::print_pnodes(vector<pnode>* pnodes) { 
	for (int i = 0; i < pnodes->size();	i++) { 
		printf("(%d: %d: %3.3f) ", pnodes->at(i).id, pnodes->at(i).previous, pnodes->at(i).cost);
	}
	printf("\n");

}

vector<pnode> Dijkstra::run(Graph* g, int source) { 
	
	if (d) printf("at %s with root: %d \n", __FUNCTION__, source);

	initialize_graph(g); 
	vector<int> q = g->nodes; 


	set_previous(&pnodes, source, source);
	set_cost(&pnodes, source, 0);
	
	while (q.size() > 0) { 


		if (d) { 
			print_pnodes(&pnodes);
		}

		int u = extractSmallestDistance(&pnodes);
		if (d) printf("smallest node: %d \n", u);
		
		if (u == -1)
			break;

		removeNode(&q,  u);
		set_removed(&pnodes, u);
		
		vector<int> u_neighbors = g->neighbors(u); 		
		for (int i = 0; i < u_neighbors.size(); i++) { 
			int v = u_neighbors[i];

			if(d) printf("considering neighbor: %d \n", v);

			if (get_removed(&pnodes, v) == false)  { 
				
				double alt = get_cost(&pnodes, u) + g->dist(u,v); 

				if (d) printf("alt : %3.3f [%3.3f + %3.3f], get_cost(v): %3.3f \n", alt, 
					get_cost(&pnodes, u), g->dist(u,v), get_cost(&pnodes,v));

				if (alt < get_cost(&pnodes, v)) { 
					printf("alt < get_cost: make changement \n");
					set_cost(&pnodes, v, alt); 
					set_previous(&pnodes, v, u);
				}
			}

		}
	}

	return pnodes; 

}



int Dijkstra::extractSmallestDistance(vector<pnode>* pnodes) { 
	int f_index = -1; 
	
	for (int i = 0; i < pnodes->size(); i++) { 
		if (!pnodes->at(i).removed) f_index = i;
	}
	if (f_index == -1) 
		return -1; 	


	int min = pnodes->at(f_index).cost; 
	for (int i = 0; i < pnodes->size(); i++) { 
		if (! pnodes->at(i).removed) {
			if (min > pnodes->at(i).cost) {
				min = pnodes->at(i).cost; 
				f_index = i;
			}
		}
	}
	return pnodes->at(f_index).id;
}



void Dijkstra::removeNode(vector<int>* q, int u) {
	if (d) printf("at %s \n", __FUNCTION__);
	
	int f = -1; 
	for (int i = 0; i < q->size(); i++) { 
		if (q->at(i) == u) {f = i; break; }
	}
	if (f != -1)
	q->erase(q->begin() + f, q->begin() + f + 1); 



}

vector<int> Dijkstra::intersection(vector<int> n_1, vector<int> n_2) {
	vector<int>::iterator it; 

	int min_size = (n_1.size() > n_2.size()) ? n_2.size() : n_1.size();	
	vector<int> v(min_size, -1); 

	sort(n_1.begin(), n_1.begin() + n_1.size()); 
	sort(n_2.begin(), n_2.begin() + n_2.size());

	it = set_intersection(n_1.begin(), n_1.begin() + n_1.size(), n_2.begin(), n_2.begin() + n_2.size(), v.begin());
	
	int stop;
	for (stop = 0; stop < v.size(); stop++) { 
		if (v.at(stop) == -1) break;  
	}	
	v.erase(v.begin() + stop, v.begin() + v.size()) ;
	
	
	return v; 
}

void Dijkstra::shortest_path(vector<pnode>* pnodes, int source, int destination, vector<int>* path, int* cost) { 
	// check if destination is in graph. 
	// g->nodes
	bool found = false; 
	for (int i = 0; i < graph->nodes.size(); i++) {
		if (graph->nodes.at(i) == destination) { 
			found = true; 
			break;
		}
	} 

	if (!found) {printf("destination %d is not in graph \n", destination); return ; }

	*cost = 0; 
	path->clear();
	path->push_back(destination);
	pnode f  = find_pnode(pnodes, destination);  	
	while (f.id != source && f.id != -1) { 
		printf("f.id : %d, f.cost: %3.3f \n", f.id, f.cost);
		printf("f.id: %d, f.previous: %d, edge_cost: %3.3f\n", f.id, f.previous, graph->dist(f.id, f.previous));

		(*cost) += graph->dist(f.id, f.previous); 
		path->push_back(f.previous); 
		printf("pusing back: %d with total cost: %d \n", f.previous, *cost);
		f = find_pnode(pnodes, f.previous);
	}


	printf("printing path [%d: %d] ", source, destination);
	for (int i = 0; i < path->size(); i++) 
		printf("%d ", path->at(i));
	printf(" --- with cost: %d \n", (*cost));

}

pnode Dijkstra::find_pnode(vector<pnode>* pnodes, int d) { 
	for (int i = 0; i < pnodes->size(); i++) 
		if (pnodes->at(i).id == d) return pnodes->at(i);		

	pnode null_result; 
	null_result.id = -1; 
	return null_result; 
}



#endif 
