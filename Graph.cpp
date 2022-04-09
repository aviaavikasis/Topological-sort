#include "Graph.h"
#include <iostream>
#include <map>
#include <string>
#include <list>

using namespace std;

//Implementation of class Graph:


Graph::~Graph() //d-ctor
{
	map<string, Vertex*>::iterator it;
	for (it = graph.begin(); it != graph.end(); it++)
		(*it).second->removeAllVertexEdges();
	for (it = graph.begin(); it != graph.end(); it++)
		delete (*it).second;
	graph.clear(); //?
}

void Graph::AddVertex(string& key) //add vertex to graph
{
	map<string, Vertex*>::iterator it;
	if (graph.empty() || graph.find(key) == graph.end()) // the vertex still not exist in graph 
		graph[key] = new Vertex(key);
	else          // already exist
	{
		cout << "ERROR\n";
		return;
	}
}


void Graph::printAll() // print all vertexes in graph and their neighbours
{
	for (map<string, Vertex*>::iterator it = graph.begin(); it != graph.end(); it++)
	{
		(*it).second->print();

		cout << endl;
	}
}



void Graph::AddEdge(string& key1, string& key2) // add edge to graph
{
	if (graph.find(key1) == graph.end() || graph.find(key2) == graph.end()) //one vertex doesn't exist
	{
		cout << "ERROR\n";
		return;
	}

	Vertex* v1  = graph[key1];
	Vertex* v2  = graph[key2];

	if (v1->destinationExists(v2)) //if the edge already exists
	{
		cout << "ERROR\n";
		return;
	}

	Edge* e1 = new Edge(v2);
	v1->AddEdge(e1);
}


void Graph::DFS_Visit(Vertex* u) // "visit" function in DFS
{
	u->color = gray;
	timeFromStart++;
	u->d = timeFromStart;
	for (list<Edge*>::iterator it = u->EdgeList.begin(); it != u->EdgeList.end(); it++) // check neighbours
	{
		Vertex* v;
		v = (*it)->destination;
		if (v->color == white)
		{
			v->pi = u;
			DFS_Visit(v);
		}
	}

	u->color = black;
	timeFromStart += 1;
	u->f = timeFromStart;
	topologicOrder.push_front(u);
}


list<Vertex*> Graph::DFS() // perform DFS on graph
{
	timeFromStart = 0;
	topologicOrder.clear();
	for (map<string, Vertex*>::iterator it = graph.begin(); it != graph.end(); it++) // reset all vertexes
	{
		(*it).second->reset();
	}
	for (map<string, Vertex*>::iterator it = graph.begin(); it != graph.end(); it++) // call to Visit
	{
		Vertex* v = (*it).second;
		if (v->color == white)
		{
			DFS_Visit(v);
		}
	}

	return topologicOrder;
}



void Graph::topologicalSort() // sort graph in topologic sort
{
	DFS();
	cout << "order: ";

	for (list<Vertex*>::iterator it = topologicOrder.begin(); it != topologicOrder.end(); it++)
	{
		cout << (*it)->Key << " ";
	}
}
