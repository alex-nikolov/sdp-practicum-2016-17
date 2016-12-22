#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include "graph.h"
using namespace std;

int main() {
	//graph testing
	Graph g;
	g.addVertex(5);
	g.addVertex(10);
	g.addVertex(15);
	g.addVertex(1);
	g.addVertex(6);
	g.addVertex(20);
	
	g.addEdge(1, 10);
	g.addEdge(1, 15);
	g.addEdge(5, 10);
	g.addEdge(5, 20);
	g.addEdge(6, 20);
	g.addEdge(6, 5);
	g.addEdge(20, 1);
	g.addEdge(10, 6);
	g.addEdge(10, 10);

	g.print();
	g.printBFS(1);
	cout << endl;

	g.printDFS(1);
	cout << endl;

	g.removeVertex(10);
	g.print();


	g.removeEdge(1, 15);
	g.print();
}