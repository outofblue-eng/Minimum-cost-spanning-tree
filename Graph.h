#pragma once
#include "GraphADT.h"
#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <memory>
#define INFINITY 9999
using namespace std;
//Implementation of GraphADT is taken from pages 389 and 390 in the textbook
// Implementation for the adjacency matrix representation
class Graph : public GraphADT {
private:
	int numVertex, numEdge; // Store number of vertices, edges
	int** matrix; // Pointer to adjacency matrix
	std::unique_ptr<int[]> mark;
	std::unique_ptr<int> col;
	std::unique_ptr<int> row;
	const int UNVISITED = 0;
public:
	Graph(int numVert) // Constructor
	{
		col = std::make_unique<int>(numVert);
		row = std::make_unique<int>(numVert);
		mark = std::make_unique<int[]>(numVert);
		Init(numVert);
	}
	~Graph() { // Destructor
		for (int i = 0; i < numVertex; i++)
			delete[] matrix[i];
		delete[] matrix;
	}
	void Init(int n) { // Initialize the graph
		int i;
		numVertex = n;
		numEdge = 0;
		
		for (i = 0; i < numVertex; i++)
			mark[i] = UNVISITED;
		matrix = (int**) new int* [numVertex]; // Make matrix
		for (i = 0; i < numVertex; i++)
			matrix[i] = new int[numVertex];
		for (i = 0; i < numVertex; i++) // Initialize to 0 weights
			for (int j = 0; j < numVertex; j++)
				matrix[i][j] = 0;
	}
	int n() { return numVertex; } // Number of vertices
	int e() { return numEdge; } // Number of edges
	// Return first neighbor of "v"
	int first(int v) {
		for (int i = 0; i < numVertex; i++)
			if (matrix[v][i] != 0) return i;
		return numVertex; // Return n if none
	}
	// Return v’s next neighbor after w
	int next(int v, int w) {
		for (int i = w + 1; i < numVertex; i++)
			if (matrix[v][i] != 0)
				return i;
		return numVertex; // Return n if none
	}
	// Set edge (v1, v2) to "wt"
	void setEdge(int v1, int v2, int wt) {
		if (wt < 0)
			std::cout << "Illegal weight value" << std::endl;
		if (matrix[v1][v2] == 0 ) numEdge++;
		matrix[v1][v2] = wt;
	}
	void delEdge(int v1, int v2) { // Delete edge (v1, v2)
		if (matrix[v1][v2] != 0) numEdge--;
		matrix[v1][v2] = 0;
	}
	bool isEdge(int i, int j) // Is (i, j) an edge?
	{
		return matrix[i][j] != 0;
	}
	int weight(int v1, int v2) { return matrix[v1][v2]; }
	int getMark(int v) { return mark[v]; }
	void setMark(int v, int val) { mark[v] = val; }


	void inputGraph(std::string file) {
		ifstream fin;
		fin.open(file);
		
		int** graph;
		graph= new int* [*col];
		
		for (int i = 0; i <*row; i++)
		{
			graph[i] = new int[*row];
			for (int j = 0; j < *col; j++)
			{
				int number;
				fin >> number;
				graph[i][j] = number;
				setEdge(i, j, number);
				setEdge(i, j, number);
			}
		}
	}
	void displayGraph()
	{
		cout << "Number of verticies is " << n() << endl;
		cout << "Number of edges is " << e()/2 << endl;
		cout << "Matrix is: " << endl;
		for (int i = 0; i < n(); i++)
		{
			for (int j = 0; j < n(); j++)
			{
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}


	}
	void writeGraphToFile(string file)
	{
		ofstream fout;
		fout.open(file);

		for (int i = 0; i < n(); i++)
		{
			for (int j = 0; j < n(); j++)
			{
				fout << matrix[i][j] << " ";
			}
			fout << endl;
		}
		fout << endl;
	}
}

;
