#ifndef _PATH_H__
#define _PATH_H__

#include <vector>
#include <stdio.h>
using namespace std; 


class path { 

	public: 
		vector<int> p; 
		double cost; 
	public: 
		path() {cost = 0;}
		bool remove_node(int u); 
		bool add_node(int u);
		bool remove_last_node();
		int get_last_node();
		void print_path();
		bool is_in_path(int);
}; 


bool path::remove_node(int u) { 
	int f_index = -1; 
	for (int i = 0; i < p.size(); i++) { 
		if (p[i] == u) {f_index == i; break; } 
	}

	if (f_index == -1) return false;
	p.erase(p.begin() + f_index, p.begin() + f_index + 1);
	return true;
	
}

bool path::remove_last_node() { 
	if (p.size() == 0) return false;
	p.pop_back();
	return true;
}	

int path::get_last_node() { 
	if (p.size() == 0) return -1; 
	else 
		return p[p.size() - 1];
}

bool path::add_node(int u) { 
	p.push_back(u); 
	return true; 	
}

bool path::is_in_path(int u) { 
	for (int i = 0; i < p.size(); i++) 
		if (p[i] == u) return true; 
	return false; 

}

void path::print_path(){ 
	for (int i = 0; i < p.size(); i++) 
		printf("%d ", p[i]);
	printf(" --- cost: %2.2f \n", cost);
}

#endif 
