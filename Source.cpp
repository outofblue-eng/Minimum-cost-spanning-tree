#include "Graph.h"
#include <iostream>
#include <fstream>
#define INFINITY 9999
using namespace std;

const int VISITED = 1;
const int UNVISITED = 0;

int minVertex(Graph* G, int* D);
Graph* Prim(Graph* G, int* D, int s);
void MST(Graph* g, int num, int vertex);
int main()
{
	cout << "Programming Assignment 5 - Samuel Tran" << endl;

	//MST 1
	cout << "MST 1" << endl;
	Graph* initGraph0 = new Graph(6);
	initGraph0->inputGraph("input.txt");
	cout << "Original Graph" << endl;
	initGraph0->displayGraph();
	cout << "Begin MST 1 starting at Vertex 0" << endl;
	int* MST1 = new int[6];
	for (int i = 0; i < 6; i++)
	{
		MST1[i] = INFINITY;
	}
	MST1[0] = 0;
	
	Graph* MSTat0 = Prim(initGraph0, MST1, 0);
	MSTat0->displayGraph();
	MSTat0->writeGraphToFile("MST1.txt");
	cout << endl;
	//MST 2
	cout << "MST 2" << endl;
	Graph* initGraph2 = new Graph(6);
	initGraph2->inputGraph("input.txt");
	cout << "Original Graph" << endl;
	initGraph2->displayGraph();
	cout << "Begin MST 2 starting at Vertex 4" << endl;
	int* MST2 = new int[6];
	for (int i = 0; i < 6; i++)
	{
		MST2[i] = INFINITY;
	}
	MST2[4] = 0;

	Graph* MSTat4 = Prim(initGraph2, MST2, 4);
	MSTat4->displayGraph();
	MSTat4->writeGraphToFile("MST2.txt");
	cout << endl;

	//MST 3
	cout << "MST 3" << endl;
	Graph* initGraph3 = new Graph(6);
	initGraph3->inputGraph("input.txt");
	cout << "Original Graph" << endl;
	initGraph3->displayGraph();
	cout << "Begin MST 2 starting at Vertex 4" << endl;
	int* MST3 = new int[6];
	for (int i = 0; i < 6; i++)
	{
		MST3[i] = INFINITY;
	}
	MST2[2] = 0;

	Graph* MSTat2 = Prim(initGraph3, MST3, 2);
	MSTat2->displayGraph();
	MSTat2->writeGraphToFile("MST3.txt");
	cout << endl;


	

	return 0;
}
//Taken from textbook on page 401
int minVertex(Graph* G, int* D) { // Find min cost vertex
	int i, v = -1;
	// Initialize v to some unvisited vertex
	for (i = 0; i < G->n(); i++)
		if (G->getMark(i) == UNVISITED) { v = i; break; }
	for (i++; i < G->n(); i++) // Now find smallest D value
		if ((G->getMark(i) == UNVISITED) && (D[i] < D[v]))
			v = i;
	return v;
}


//Taken from textbook on page 405
Graph* Prim(Graph* G, int* D, int s) { // Prim’s MST algorithm
	Graph* MST = new Graph(6);
	int* V = new int[6]; // Store closest vertex
	int i, w;
	for (int i = 0; i < G->n(); i++) // Initialize
		D[i] = INFINITY;
	D[s] = 0;
	for (int i = 0; i < G->n(); i++) { // Process the vertices
		int v = minVertex(G, D);
		G->setMark(v, VISITED);
		if (v != s)
		{
			cout << "Adding edge " << V[v] << " to " << v << endl;// Add edge to MST
			MST->setEdge(v, V[v], D[v]);
			MST->setEdge(V[v], v, D[v]);
		}

		if (D[v] == INFINITY) return G; // Unreachable vertices
		for (w = G->first(v); w < G->n(); w = G->next(v, w))
			if (D[w] > G->weight(v, w)) {
				D[w] = G->weight(v, w); // Update distance
				V[w] = v; // Where it came from
			}
	}
	return MST;
}
