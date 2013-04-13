
#ifndef __READ_FILE__H
#define __READ_FILE__H

#include <string>
#include <string.h>
#include <vector>
#include "point.h"
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
using namespace std; 

bool tokenize(char* line, vector<string>* str); 
int getline(FILE* f, char line[], int max);
void trim(char* input, char* output);
double euc_distance(point* p1, point* p2); 
void extract_graph(map<int, vector<int> >* graph, char* file_name); 
void extract_pointed_graph(vector<point>* points, char* file_name);
void convert_points_to_graph(map<int, vector<int> >* graph, vector<point>* points, int range); 
bool is_in_range(int range, point* p1, point* p2); 

bool tokenize(char* line, vector<string>* str) { 
	if (!line) { printf("error: line"); return false; } 
	if (!str) { printf("error: str"); return false; }
	
	
	string str_pointer; 
	char* res = new char[1256];
	trim(line, res);
	//char* res = trim(line);
	char* tok = NULL; 

	tok = strtok(res, " "); 
	while (tok != NULL) { 
		//str_pointer = new string(tok); 
		str_pointer.clear();
		str_pointer.append(tok);
		// printf("pushing %s \n", tok);
		str->push_back(str_pointer);
		// delete str_pointer; 
		tok = strtok(NULL," ");
		
	}

	// delete [] res; 
	return true; 
}

int getline(FILE* f, char line[], int max) {
	int nch = 0;
	char c;
	max = max - 1;			/* leave room for '\0' */

	while((c = fgetc(f)) != EOF) {
		if(c == '\n')
			break;

		if(nch < max) {
			line[nch] = c;
			nch = nch + 1;
		}
	}

	if(c == EOF && nch == 0)
		return EOF;

	line[nch] = '\0';
	return nch;
}

void trim(char* input, char* output) { 
	if (!input) return; 
	if (!output) return; 

	int r_index = 0; 
	while (*input) { 
		if (*input == '\t' || *input == ' ') { 
			output[r_index++] = ' ';
			
		} else { 
			output[r_index++] = *input; 
			
		}
		input++;
	}	
	output[r_index] = '\0';

}

void extract_graph(map<int, vector<int> >* graph, char* file_name) { 

	FILE* f; 
	char line[5000];
	vector<string> str_tokens;
	int i = 0, line_counter = 0;	

	
	f = fopen(file_name, "r"); 	
	if (!f) { 
		printf("error: file could not be open \n");
		return;
	}

	i = 0;
	line_counter = 0;
	vector<int> neighbors;
	char* cstr;
	while(getline(f, line, 1256) != EOF) {  
		
		str_tokens.clear();
		if (! tokenize(line, &str_tokens))
			printf("tokenize did not succeed \n"); 


		for (int i = 0; i < str_tokens.size(); i++ ) {

			
			cstr = new char [str_tokens[i].size()+1];
  			strcpy (cstr, str_tokens[i].c_str());
		
			neighbors.push_back(atoi(cstr));
			delete [] cstr; 

		}
		
		sort (neighbors.begin(), neighbors.end()); 
		graph->insert(pair<int, vector<int> >(line_counter, neighbors));
		line_counter ++; 
		neighbors.clear(); 
	}	

}


void extract_pointed_graph(vector<point>* points, char* file_name) { 

	FILE* f; 
	char line[5000];
	vector<string> str_tokens;
	int i = 0, line_counter = 0;	

	
	f = fopen(file_name, "r"); 	
	if (!f) { 
		printf("error: file could not be open \n");
		return;
	}

	i = 0;
	line_counter = 0;
	char* cstr;

	while(getline(f, line, 1256) != EOF) {  
		
		str_tokens.clear();
		if (! tokenize(line, &str_tokens))
			printf("tokenize did not succeed \n"); 

		
		point p; 
		if (str_tokens.size() != 2) { 
			printf("Error: string tokens does not equal 2 \n");
			abort();
		} else { 
			cstr = new char[str_tokens[0].size() + 1];
			strcpy (cstr, str_tokens[0].c_str());
		
			p.x_axis = atof(cstr); 
			delete [] cstr; 

			cstr = new char[str_tokens[1].size() + 1];
			strcpy (cstr, str_tokens[1].c_str());
			p.y_axis = atof(cstr);
			delete [] cstr; 	
		
			points->push_back(p);
		}

		line_counter ++; 
	}	

}

void convert_points_to_graph(map<int, vector<int> >* graph, vector<point>* points, int range) { 

	vector<int> neighbors; 
	
	for (int i = 0; i < points->size(); i++) { 
		for (int j = 0; j < points->size(); j++) { 
			if (i != j) { 
				if (is_in_range(range, &points->at(i), &points->at(j))) 
					neighbors.push_back(j);
				
			}
		}


		graph->insert(pair<int, vector<int> >(i, neighbors));
		neighbors.clear(); 
	}

}

bool is_in_range(int range, point* p1, point* p2) { 
	if (!p1) { printf("p1 must be intitialized \n"); abort();} 
	if (!p2) { printf("p2 must be intitialized \n"); abort();} 
	
	return (euc_distance(p1, p2) <= range); 
}

double euc_distance(point* p1, point* p2){ 
	
	if (!p1) { printf("p1 must be intitialized \n"); abort();} 
	if (!p2) { printf("p2 must be intitialized \n"); abort();} 

	return sqrt( pow(p1->x_axis - p2->x_axis, 2) + pow(p1->y_axis - p1->y_axis, 2));  
	
}





#endif
