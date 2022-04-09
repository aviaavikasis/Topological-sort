#pragma once
#include <iostream>
#include <map>
#include <list>
#include <string>
using namespace std;

//class Edge:

enum Color { black = 0, gray, white }; 

class Vertex; //decleration

class Edge
{
	Vertex* destination;
public:
	Edge(Vertex* destinationVertex) { destination = destinationVertex; } //ctor
	bool operator ==(Edge& v) { return (v.destination == destination); } // operator "=="
	friend class Vertex;
	friend class Graph;
};


 //class Vertex:

class Vertex
{
	string Key;
	Vertex* pi;
	list<Edge*> EdgeList;
	int d; // distance from start of graph
	int f; // time of return and end of visit 
	Color color;

public:

	Vertex(string key) { Key = key; } //ctor
	void AddEdge(Edge* e) { EdgeList.push_back(e); } // add edge to list
	int numOfNeighbours() // return num of neighbours of vertex
	{
		int num = 0;
		for (list<Edge*>::iterator it = EdgeList.begin(); it != EdgeList.end(); it++, num++);
		return num;
	}
	bool destinationExists(Vertex* vertex2) //if two vertex connect
	{
		for (list<Edge*>::iterator it = EdgeList.begin(); it != EdgeList.end(); it++)
			if ((*it)->destination == vertex2)
				return true;

		return false;
	}
	void print() //print vertex: key , all its neighbours
	{
		cout << Key << ": ";
		for (list<Edge*>::iterator it = EdgeList.begin(); it != EdgeList.end(); it++)
		{
			cout << (*it)->destination->Key << " ";
		}
	}
	void removeAllVertexEdges() //remove All Edges of current vertex 
	{
		for (list<Edge*>::iterator it = EdgeList.begin(); it != EdgeList.end(); it++)
			delete (*it);
	}
	void reset() // reset the vertex for the DFS
	{
		pi = NULL;
		color = white;
	}

	friend class Graph;
};


//class Graph

class Graph
{
private:
	int timeFromStart;
	list<Vertex*> topologicOrder;
	map<string, Vertex*> graph; 

public:

	Graph() {} //ctor
	~Graph(); // d-ctor
	void AddEdge(string& key1, string& key2); // ad edge to the graph
	void AddVertex(string& key); // ad vertex to the graph
	void printAll(); // print all graph, vertex and their edges
	void DFS_Visit(Vertex* v); 
	list<Vertex*> DFS();
	void topologicalSort(); // print the graph in order the topological list
};
