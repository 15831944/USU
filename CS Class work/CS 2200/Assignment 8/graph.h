// Assignment 7

//Implement the ADT Graph as a C++ class, using an adjacency list to 
//represent the graph. Allow the graph to be either weighted or 
//unweighted, and either directed or undirected. Include depth-first 
//and breadth-first traversal functions, with Visit function arguments. 
//Also include functions to print out the edges composing the 
//depth-first spanning tree and the breadth-first spanning tree found 
//by searching starting from the first node of the graph. If the graph 
//is directed and not strongly connected, the spanning tree will be 
//only of the component in which the first node lies. If the graph is 
//undirected, print out spanning trees of all the components. If the 
//graph is undirected, connected, and weighted, print out the 
//minimum-cost spanning tree.

/*
	List();      // constructor
   ~List();     // destructor
   void insertAtFront( const NODETYPE & );
   void insertAtBack( const NODETYPE & );
   bool removeFromFront( NODETYPE & );
   bool removeFromBack( NODETYPE & );
   bool isEmpty() const;
   void print() const;
   void printBackwards(ListNode< NODETYPE > *) const;
   ListNode<NODETYPE> * getFirstPtr() const;
*/

#include <iostream.h>
#include "Linked List.h"

typedef int BOOL;
class Graph;
class Vertice;

void PrintVertID(Vertice *v, Vertice *n);
void JustMark(Vertice *v, Vertice *n);
void CheckCycle(Vertice *v, Vertice *n);

class EdgeData {
	friend class Graph;
public:
	EdgeData();
	EdgeData(Vertice *node, int w = 0);
	EdgeData(const EdgeData &); // copy constructor
	void SetInfo(Vertice *node, int w = 0);
	Vertice *GetAdjacentNode();
	bool operator<(const EdgeData &right) const;
private:
	Vertice *adjacentNode;
	int weight;
};

class Vertice {
	friend class Graph;
	friend class EdgeData;
	friend void CheckCycle(Vertice *h, Vertice *n);
public:
	Vertice();
	void SetID(char ID);
	void AddAdjacentNode(Vertice *addNode, int weight);
	bool IsVisited();
	void MarkVisited();
	void ClearVisit();
	char GetID();
private:
	char id;
	bool Visited;
	OrderedList<EdgeData> AdjacentNodes;
	int nAdjacentNodes;
};

typedef void (*VisitFunctionType)(Vertice *, Vertice *);

class Graph {
public:
	Graph();
	Graph(int n, bool IsD, bool IsW);
	~Graph();
	void SetInfo(int n, bool IsD, bool IsW);
	void AssignID(int whichNode, char ID);
	void AddEdge(char Node1, char Node2, int Weight = 0);
	bool IsDirected();
	bool IsWeighted();
	bool IsConnected();
	bool LoadGraph(istream &input);
	Vertice * GetVertPointer(int index);
	void SetNumEdges(int n);
	int GetNumNodes();
	int GetNumEdges();
	void ClearAllVertices();
	void BreadthFirstTraversal(int startIndex, VisitFunctionType VisitFunction);
	void BreadthFirstTraversal(Vertice *startVertice, VisitFunctionType VisitFunction);
	void DepthFirstTraversal(Vertice *startVertice, VisitFunctionType VisitFunction);
	void DepthFirstTraversal(int startIndex, VisitFunctionType VisitFunction);
	void SpecialCycleTraversal(Vertice *whichVertice, VisitFunctionType VisitFunction);
	void FindComponents(int arrayC[], int nVert, int &nC);
	Graph* MST(int startIndex);
	bool IsStronglyConnected();
	bool IsCycle(int index);
	int FindIndex(char n);
private:
	
	void DepthFirstHelper(Vertice *whichVertice, VisitFunctionType);
	void BreadthFirstHelper(Vertice *whichVertice, VisitFunctionType VisitFuction);

	int nNodes;
	int nEdges;
	Vertice *Nodes;
	bool Directed;
	bool Weighted;
	
};




