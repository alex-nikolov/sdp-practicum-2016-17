#ifndef _GRAPH_H
#define _GRAPH_H

#include <map>
#include <vector>
#include <stack>

class Graph {
	typedef std::map < double, std::vector<double> > myMap;
	myMap graph;
	
	void DFS_helper(double, std::map<double, bool>&, std::stack<double>&);
	std::map<double, bool> createVisited();
public:
	Graph();
	
	void addVertex(double);
	void addEdge(double, double);
	
	void removeVertex(double);
	void removeEdge(double, double);
	
	void print() const;
	
	void printBFS(double);
	void printDFS(double);
};



#endif