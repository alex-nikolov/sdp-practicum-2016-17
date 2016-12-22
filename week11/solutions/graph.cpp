#include "graph.h"

#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

Graph::Graph() {
}

void Graph::addVertex(double value) {
	myMap::iterator it = graph.find(value);
	
	if (it == graph.end())
		graph[value] = std::vector<double>();
}

void Graph::addEdge(double from, double to) {
	myMap::iterator fromIt = graph.find(from);
	myMap::iterator toIt = graph.find(to);
	
	vector<double>* vec =  &fromIt->second;
	if (fromIt != graph.end() && toIt != graph.end() &&
		find(vec->begin(), vec->end(), to) == vec->end())
			vec->push_back(to);
}

void Graph::removeVertex(double value) {
	graph.erase(value);

	for (myMap::iterator it = graph.begin(); it != graph.end(); it++) {
		vector<double>* vec = &it->second;

		for (int i = 0; i < vec->size(); i++)
			vec->erase(remove(vec->begin(), vec->end(), value), vec->end()); 
	}
}

void Graph::removeEdge(double from, double to) {
	myMap::iterator fromIt = graph.find(from);

	vector<double>* vec = &fromIt->second;
	vec->erase(remove(vec->begin(), vec->end(), to), vec->end()); 
}

void Graph::print() const {
	for (myMap::const_iterator it = graph.begin(); it != graph.end(); it++) {
		cout << "Vertex: " << it->first << ", Neighbours: ";
		
		for (int i = 0; i < it->second.size(); i++)
			cout << it->second[i] << " ";
		cout << endl;
	}

	cout << endl;
}

map<double, bool> Graph::createVisited() {
	map<double, bool> visited;

	for (myMap::iterator it = graph.begin(); it != graph.end(); it++)
		visited[it->first] = false;
		
	return visited;
}

void Graph::printBFS(double start) {
	if (graph.find(start) == graph.end())
		return;
	
	map<double, bool> visited = createVisited();
	queue<double> q;
	
	q.push(start);
	visited[start] = true;
	
	while (q.size() > 0) {
		double front = q.front();
		cout << front << " ";
		q.pop();

		// За да не се търси всеки път graph[front], а само веднъж
		vector<double>* vec = &graph[front];

		for (int i = 0; i < vec->size(); i++) {
			double value = (*vec)[i];

			if (!visited[value]) {
				visited[value] = true;
				q.push(value);
			}
		}
	}
}

void Graph::printDFS(double start) {
	if (graph.find(start) == graph.end())
		return;

	map<double, bool> visited = createVisited();
	stack<double> s;
	
	DFS_helper(start, visited, s);
}

void Graph::DFS_helper(double start, map<double, bool>& visited, stack<double>& s) {
	cout << start << " ";
	s.push(start);
	visited[start] = true;
	
	vector<double>* vec = &graph[start];

	for (int i = 0; i < vec->size(); i++) {
		double value = (*vec)[i];

		if (!visited[value])
			DFS_helper(value, visited, s);
	}
	
	s.pop();
}