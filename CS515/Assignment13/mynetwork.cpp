/**   CS515 Assignment13
File: mynetwork.cpp DisjointSet.h
Name: Jonathan Hart
Section: 2
Date: 12/7/13
Collaboration Declaration: Ian D'Elia credited for use of #define edge pair<string,string>
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cfloat>
#include <queue>
#include <limits.h>
#include <set>
#include <list>
#include <stack>
#include <assert.h>
#include "DisjointSet.h"

#define _edge pair<string, string>

using namespace std;

struct connection{
	_edge edge;
	int weight;
};


bool operator<(const connection& p1, const connection& p2) {
	return p1.weight < p2.weight;
};

stack<string> startNode;
list<string> finalPath;
bool found;

void findPath(string currentNode, string endPoint, list<connection> safeEdges, list<string> path)
{
	list<string>::iterator listIt;

	for (listIt = path.begin(); listIt != path.end(); ++listIt)
	{
		if(*listIt == currentNode)
			return;
	}

	path.push_back(currentNode);

	list<connection>::iterator safeEdgesIt;

	for(safeEdgesIt = safeEdges.begin();safeEdgesIt != safeEdges.end(); ++safeEdgesIt)
	{
		connection cur = *safeEdgesIt;

		//because graph is undirected, must check both sides of safe edge
		if(cur.edge.first == currentNode)
		{															
			//found end node
			if(cur.edge.second == endPoint)
			{
				path.push_back(cur.edge.second);
				found = true;
				finalPath = path;
				break;
			}
			findPath(cur.edge.second, endPoint, safeEdges, path);

		}
		else if(cur.edge.second == currentNode)
		{
			//found end node
			if(cur.edge.first == endPoint)
			{
				path.push_back(cur.edge.first);
				found = true;
				finalPath = path;
				break;
			}


			findPath(cur.edge.first, endPoint, safeEdges, path);

		}

		if(found)
			break;
	}

	
	
}

int main(int argc, char** argv)
{
	priority_queue<connection> graph;
	DisjointSet<string> dsSet;
	set<string> nodes;
	set<string>::iterator nodesIt;
	list<connection> safeEdges;
	list<connection>::iterator safeEdgesIt;

	if(argc != 2)
	{
		cout << "Invalid number of arguments!" << endl;
		return -1;
	}

	ifstream inputFile(argv[1]);

	if(!inputFile)
	{
		cout << "Error opening input file!";
		return -1;
	}

	connection firstLink;
	string node1, node2;
	int weight;

	//get first connection
	inputFile >> node1 >> node2 >> weight;

	//first node is start node
	startNode.push(node1);

	//add nodes to set of nodes
	nodes.insert(node1);
	nodes.insert(node2);

	//create connection, make weight negative because max priority queue
	firstLink.edge.first = node1;
	firstLink.edge.second = node2;
	firstLink.weight = weight*-1;

	//add to queue
	graph.push(firstLink);

	//get remaining connections
	while(!inputFile.eof())
	{
		connection newLink;

		inputFile >> node1 >> node2 >> weight;

		nodes.insert(node1);
		nodes.insert(node2);

		newLink.edge.first = node1;
		newLink.edge.second = node2;
		newLink.weight = weight*-1;

		graph.push(newLink);		
	}

	/*while(!graph.empty())
	{			
	cout << "(" << graph.top().edge.first << "," << graph.top().edge.second << ") = " << graph.top().weight << endl;
	graph.pop();
	}

	cout << nodes.size() << endl;*/

	//Create singleton set for each node
	for (nodesIt = nodes.begin(); nodesIt != nodes.end(); ++nodesIt)
		dsSet.createSet(*nodesIt);	

	//Create MST
	//safe edges will be connections with smallest weight.
	//use disjoint set to track connected nodes
	while(!graph.empty())
	{
		node1 = graph.top().edge.first;
		node2 = graph.top().edge.second;
				
		if(dsSet.unionSets(node1,node2))
		{
			//cout << "Inserting = (" << graph.top().edge.first << "," << graph.top().edge.second << ") = " << graph.top().weight << endl;
			safeEdges.push_back(graph.top());	
		}
		
		graph.pop();
	}

	/*for (safeEdgesIt = safeEdges.begin(); safeEdgesIt != safeEdges.end(); ++safeEdgesIt)
	cout << "(" << (*safeEdgesIt).edge.first << "," << (*safeEdgesIt).edge.second << ") = " << (*safeEdgesIt).weight << endl;*/

	//MST now complete. Time for user input
	cout << "<" << startNode.top() << "># ";

	string input;

	while(getline(cin,input))
	{
		stringstream ss(input);

		//Get command and node
		string command, endPoint;
		ss >> command >> endPoint;

		//ping, ssh, and exit are only valid commands
		if(command == "ping")
		{					
			//cout << "endpoint = " << endPoint << endl;
						
			if(nodes.find(endPoint) != nodes.end())//found node, find path
			{
				if(startNode.top() == endPoint)
					cout << "Why hello there " << endPoint << "!" << endl;
				else
				{
					//create flag to tell when path is found
					found = false;

					//create queue to keep track of path
					list<string> path;
					list<string>::iterator pathIt;

					for(safeEdgesIt = safeEdges.begin();safeEdgesIt != safeEdges.end(); ++safeEdgesIt)
					{
						connection cur = *safeEdgesIt;

						//because graph is undirected, must check both sides of safe edge
						if(cur.edge.first == startNode.top())
						{															
							//found end node
							if(cur.edge.second == endPoint)
							{
								path.push_back(cur.edge.second);
								found = true;
								finalPath = path;
								break;
							}

							findPath(cur.edge.second, endPoint, safeEdges, path);

						}
						else if(cur.edge.second == startNode.top())
						{
							//found end node
							if(cur.edge.first == endPoint)
							{
								path.push_back(cur.edge.first);
								found = true;
								finalPath = path;
								break;
							}							

							findPath(cur.edge.first, endPoint, safeEdges, path);

						}

						if(found)
							break;
					}

					cout << " From: " << startNode.top() << endl;

					for (pathIt = finalPath.begin(); pathIt != finalPath.end(); ++pathIt)
						cout << " To: " << *pathIt << endl;		

					finalPath.clear();					
				}
			}
			else//Node doesn't exist
			{
				cout << "Cannot find Node. Available nodes are:" << endl;
				for (nodesIt = nodes.begin(); nodesIt != nodes.end(); ++nodesIt)
					cout << *nodesIt << endl;
			}

		}
		else if(command == "ssh")
		{
			if(nodes.find(endPoint) != nodes.end())//found node
			{
				startNode.push(endPoint);
			}
			else//Node doesn't exist
			{
				cout << "Cannot find Node. Available nodes are:" << endl;
				for (nodesIt = nodes.begin(); nodesIt != nodes.end(); ++nodesIt)
					cout << *nodesIt << endl;
			}
		}
		else if(command == "exit")
		{
			startNode.pop();
			if(startNode.empty())
				return 0;
		}
		else
		{
			cout << "Unrecognized command." << endl;
		}

		cout << "<" << startNode.top() << "># ";
	}


	return 0;
}